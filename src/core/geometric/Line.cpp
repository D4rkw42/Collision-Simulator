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
}

void Line::Render(std::shared_ptr<Window> window) {
    // Obtendo pontos para desenho
    std::shared_ptr<Line> line = std::make_shared<Line>(*this);
    auto Points = Line::FindLineLimits(line);

    SDL_SetRenderDrawColor(window->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    SDL_RenderDrawLine(window->renderer, Points[0].x, Points[0].y, Points[1].x, Points[1].y);
}

// utilities

// Retorna os pontos limites de uma semireta
std::vector<Coord> Line::FindLineLimits(std::shared_ptr<Line> line) {
    // Encontrando ângulos
    double angle = line->angle;

    // Encontrando os pontos
    double Length = line->length / 2;

    double x1 = line->coord.x + Length * cos(angle);
    double y1 = line->coord.y + Length * sin(angle);

    double x2 = line->coord.x + Length * -cos(angle);
    double y2 = line->coord.y + Length * -sin(angle);

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
    auto OriginPoints = FindLineLimits(origin);
    auto TargetPoints = FindLineLimits(target);

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
    auto points = FindLineLimits(line);

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
    auto originLimits = Line::FindLineLimits(origin);

    // Verifica cada ponto principal da reta origin, se está sobre a reta target
    //if (Line::IsPointAtLine(origin->coord, target) || Line::IsPointAtLine(originLimits[0], target) || Line::IsPointAtLine(originLimits[1], target)) {
    //    return true;
    //}

    auto OriginPoints = FindLineLimits(origin);
    auto TargetPoints = FindLineLimits(target);

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
