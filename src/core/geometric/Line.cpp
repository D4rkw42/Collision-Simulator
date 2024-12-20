// Definição básica de linha

#include "Line.hpp"

#include <iostream>
#include <limits>

#include <SDL2/SDL.h>
#include <effolkronium/random.hpp>

using random = effolkronium::random_static;

Line::Line(Coord coord, double velX, double velY, double length, double angle, RGBA color) {
    this->coord = coord;

    this->velX = velX;
    this->velY = velY;

    this->length = length;
    this->angle = angle;

    this->color = color;
}

//

void Line::Update(int deltatime) {
    this->coord.x += this->velX;
    this->coord.y += this->velY;

    //this->angle += this->velAng;

    if (this->angle > rad(360)) {
        this->angle -= rad(360);
    }

    if (this->angle < 0) {
        this->angle += rad(360);
    }
}

void Line::Render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    // Obtendo pontos para desenho
    std::shared_ptr<Line> line = std::make_shared<Line>(*this);

    double x, y, size;

    camera->Viewport(window, ObjectInfo { this->length, this->coord.x, this->coord.y }, x, y, size);
    auto Points = Line::FindLineLimits(x, y, this->angle, size);

    SDL_SetRenderDrawColor(window->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderDrawLine(window->renderer, Points[0].x, Points[0].y, Points[1].x, Points[1].y);
}

// utilities

// Retorna os pontos limites de uma semireta
std::vector<Coord> Line::FindLineLimits(double x, double y, double angle, double length) {
    // Encontrando os pontos
    length /= 2;

    double x1 = x + length * cos(angle);
    double y1 = y + length * sin(angle);

    double x2 = x + length * -cos(angle);
    double y2 = y + length * -sin(angle);

    // A ordem dos dados deve ser a mesma
    if (x1 > x2) {
        return std::vector<Coord> {
            Coord { x1, y1 },
            Coord { x2, y2 }
        };
    }

    // A ordem dos dados deve ser a mesma
    return std::vector<Coord> {
        Coord { x2, y2 },
        Coord { x1, y1 }
    };
}

// Encontra a interseção entre duas semiretas
Coord* Line::FindLineIntersection(std::shared_ptr<Line> origin, std::shared_ptr<Line> target) {
    auto OriginPoints = FindLineLimits(origin->coord.x, origin->coord.y, origin->angle, origin->length);
    auto TargetPoints = FindLineLimits(target->coord.x, target->coord.y, target->angle, target->length);

    // Obtendo a lei que rege as retas (y = ax + b)

    std::vector<double> originCoeficients = Line::GetLineLawCoeficients(origin);
    std::vector<double> targetCoeficients = Line::GetLineLawCoeficients(target);

    // Coeficientes
    double aCoefOrigin = originCoeficients[0];
    double bCoefOrigin = originCoeficients[1];

    double aCoefTarget = targetCoeficients[0];
    double bCoefTarget = targetCoeficients[1];

    // Obtendo ponto de interseção
    double x, y;

    double dA = aCoefOrigin - aCoefTarget;
    double dB = bCoefTarget - bCoefOrigin;
    
    x = dB / dA;
    y = aCoefOrigin * x + bCoefOrigin;

    return new Coord { x, y };
}

std::vector<double> Line::GetLineLawCoeficients(std::shared_ptr<Line> line) {
    auto points = FindLineLimits(line->coord.x, line->coord.y, line->angle, line->length);

    // Encontrando os coeficientes da reta
    double aCoef = (points[0].y - points[1].y) / (points[0].x - points[1].x);
    double bCoef = points[0].y - aCoef * points[0].x;

    return std::vector { aCoef, bCoef };
}

bool Line::IsPointAtLine(Coord coord, std::shared_ptr<Line> line) {
    std::vector<double> lineCoeficients = Line::GetLineLawCoeficients(line);

    double
        a = lineCoeficients[0],
        b = lineCoeficients[1];

    // Obtendo valor teórico do ponto na reta
    double yTest = coord.x * a + b;

    // Se o valor teórico for igual ao valor real, o ponto pertence à reta
    return abs(yTest - coord.y) < 0.001f;
}

// Verifica se duas semiretas estão colidindo
bool Line::LineCollision(std::shared_ptr<Line> origin, std::shared_ptr<Line> target) {
    // Obtendo a interseção das linhas
    auto Intersection = FindLineIntersection(origin, target);

    // Colisões especiais

    // Semiretas iguais totalmente sobrepostas
    if (isnan(Intersection->x) && isnan(Intersection->y)) {
        return true;
    }

    // Semiretas sobrepostas parcialmente
    auto originLimits = Line::FindLineLimits(origin->coord.x, origin->coord.y, origin->angle, origin->length);

    // Verifica cada ponto principal da reta origin, se está sobre a reta target
    //if (Line::IsPointAtLine(origin->coord, target) || Line::IsPointAtLine(originLimits[0], target) || Line::IsPointAtLine(originLimits[1], target)) {
    //    return true;
    //}

    auto OriginPoints = FindLineLimits(origin->coord.x, origin->coord.y, origin->angle, origin->length);
    auto TargetPoints = FindLineLimits(target->coord.x, target->coord.y, target->angle, target->length);

    double x = Intersection->x;
    double y = Intersection->y;

    // Caso o ponto de interseção estiver dentro dos limites de uma das linhas, as semiretas se tocam
    return ( // para semireta origin
        (x >= OriginPoints[0].x && x <= OriginPoints[1].x) || (x >= OriginPoints[1].x && x <= OriginPoints[0].x) // for x
    ) && (
        (y >= OriginPoints[0].y && y <= OriginPoints[1].y) || (y >= OriginPoints[1].y && y <= OriginPoints[0].y) // for y
    ) && ( // para semireta target
        (x >= TargetPoints[0].x && x <= TargetPoints[1].x) || (x >= TargetPoints[1].x && x <= TargetPoints[0].x) // for x
    ) && (
        (y >= TargetPoints[0].y && y <= TargetPoints[1].y) || (y >= TargetPoints[1].y && y <= TargetPoints[0].y) // for y
    );
}
