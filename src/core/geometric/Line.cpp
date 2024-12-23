// Definição básica de linha

#include "Line.hpp"

#include <iostream>
#include <limits>

#include <SDL2/SDL.h>
#include <effolkronium/random.hpp>

using random = effolkronium::random_static;

Line::Line(const Coord& coord, double velX, double velY, double velAng, double length, double angle, const RGBA& color) {
    this->coord = coord;

    this->velX = velX;
    this->velY = velY;

    this->accX = 0;
    this->accY = 0;

    this->velAng = velAng;

    this->length = length;
    this->angle = angle;

    this->isColliding = false;

    this->color = color;
}

//

void Line::Update(int deltatime) {
    // Primeira atualização de velocidade
    this->velX += this->accX * 0.5f;
    this->velY += this->accY * 0.5f;

    this->coord.x += this->velX;
    this->coord.y += this->velY;

    // Segunda atualização de velocidade
    this->velX += this->accX * 0.5f;
    this->velY += this->accY * 0.5f;

    this->angle += this->velAng;

    if (this->angle > rad(360)) {
        this->angle -= rad(360);
    }

    if (this->angle < 0) {
        this->angle += rad(360);
    }

    this->isColliding = false;
}

void Line::Render(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera) {
    // Obtendo pontos para desenho
    // double x, y, size;

    // camera->Viewport(window, ObjectInfo { this->length, this->coord.x, this->coord.y }, x, y, size);
    // auto Points = Line::FindLineLimits(x, y, this->angle, size);

    // SDL_SetRenderDrawColor(window->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
    // SDL_RenderDrawLine(window->renderer, Points[0].x, Points[0].y, Points[1].x, Points[1].y);

    Line::RenderLine(window, camera, this->coord, this->length, this->angle, this->color);
}

// utilities

void Line::RenderLine(const std::shared_ptr<Window> &window, const std::shared_ptr<Camera> &camera, const Coord& coord, double length, double angle, const RGBA& color) {
    // Obtendo pontos para desenho
    double screenX, screenY, screenSize;

    camera->Viewport(window, ObjectInfo { length, coord.x, coord.y }, screenX, screenY, screenSize);
    auto Points = RawLine::FindLineLimits(screenX, screenY, angle, screenSize);

    SDL_SetRenderDrawColor(window->renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(window->renderer, Points[0].x, Points[0].y, Points[1].x, Points[1].y);
}

// // Retorna os pontos limites de uma semireta
// std::array<Coord, 2> Line::FindLineLimits(double x, double y, double angle, double length) {
//     // Encontrando os pontos
//     length /= 2;

//     double x1 = x + length * cos(angle);
//     double y1 = y + length * sin(angle);

//     double x2 = x + length * -cos(angle);
//     double y2 = y + length * -sin(angle);

//     // A ordem dos dados deve ser a mesma
//     std::array<Coord, 2> limits;

//     if (x1 > x2) {
//         limits[0] = Coord { x1, y1 };
//         limits[1] = Coord { x2, y2 };

//         // return std::array<Coord, 2> {
//         //     Coord { x1, y1 },
//         //     Coord { x2, y2 }
//         // };
//     } else {
//         limits[0] = Coord { x2, y2 };
//         limits[1] = Coord { x1, y1 };
//     }

//     return limits;

//     // A ordem dos dados deve ser a mesma
//     // return std::array<Coord, 2> {
//     //     Coord { x2, y2 },
//     //     Coord { x1, y1 }
//     // };
// }

// // Encontra a interseção entre duas semiretas
// Coord Line::FindLineIntersection(const std::shared_ptr<Line>& origin, const std::shared_ptr<Line>& target) {
//     auto OriginPoints = FindLineLimits(origin->coord.x, origin->coord.y, origin->angle, origin->length);
//     auto TargetPoints = FindLineLimits(target->coord.x, target->coord.y, target->angle, target->length);

//     // Obtendo a lei que rege as retas (y = ax + b)

//     Vec2D originCoeficients = Line::GetLineLawCoeficients(origin);
//     Vec2D targetCoeficients = Line::GetLineLawCoeficients(target);

//     // Coeficientes
//     double aCoefOrigin = originCoeficients[0];
//     double bCoefOrigin = originCoeficients[1];

//     double aCoefTarget = targetCoeficients[0];
//     double bCoefTarget = targetCoeficients[1];

//     // Obtendo ponto de interseção
//     double x, y;

//     double dA = aCoefOrigin - aCoefTarget;
//     double dB = bCoefTarget - bCoefOrigin;
    
//     x = dB / dA;
//     y = aCoefOrigin * x + bCoefOrigin;

//     return Coord { x, y };
// }

// Vec2D Line::GetLineLawCoeficients(const std::shared_ptr<Line>& line) {
//     auto points = FindLineLimits(line->coord.x, line->coord.y, line->angle, line->length);

//     // Encontrando os coeficientes da reta
//     double aCoef = (points[0].y - points[1].y) / (points[0].x - points[1].x);
//     double bCoef = points[0].y - aCoef * points[0].x;

//     return Vec2D { aCoef, bCoef };
// }

// bool Line::IsPointAtLine(const Coord& coord, const std::shared_ptr<Line>& line) {
//     Vec2D lineCoeficients = Line::GetLineLawCoeficients(line);

//     double
//         a = lineCoeficients[0],
//         b = lineCoeficients[1];

//     // Obtendo valor teórico do ponto na reta
//     double yTest = coord.x * a + b;

//     // Se o valor teórico for igual ao valor real, o ponto pertence à reta
//     return abs(yTest - coord.y) < 0.001f;
// }

// // Verifica se duas semiretas estão colidindo
// bool Line::LineCollision(const std::shared_ptr<Line>& origin, const std::shared_ptr<Line>& target) {
//     // Obtendo a interseção das linhas
//     auto Intersection = FindLineIntersection(origin, target);

//     // Colisões especiais

//     // Semiretas iguais totalmente sobrepostas
//     if (isnan(Intersection.x) && isnan(Intersection.y)) {
//         return true;
//     }

//     // Semiretas sobrepostas parcialmente
//     auto originLimits = Line::FindLineLimits(origin->coord.x, origin->coord.y, origin->angle, origin->length);

//     // Verifica cada ponto principal da reta origin, se está sobre a reta target
//     //if (Line::IsPointAtLine(origin->coord, target) || Line::IsPointAtLine(originLimits[0], target) || Line::IsPointAtLine(originLimits[1], target)) {
//     //    return true;
//     //}

//     auto OriginPoints = FindLineLimits(origin->coord.x, origin->coord.y, origin->angle, origin->length);
//     auto TargetPoints = FindLineLimits(target->coord.x, target->coord.y, target->angle, target->length);

//     double x = Intersection.x;
//     double y = Intersection.y;

//     // Caso o ponto de interseção estiver dentro dos limites de uma das linhas, as semiretas se tocam
//     return ( // para semireta origin
//         (x >= OriginPoints[0].x && x <= OriginPoints[1].x) || (x >= OriginPoints[1].x && x <= OriginPoints[0].x) // for x
//     ) && (
//         (y >= OriginPoints[0].y && y <= OriginPoints[1].y) || (y >= OriginPoints[1].y && y <= OriginPoints[0].y) // for y
//     ) && ( // para semireta target
//         (x >= TargetPoints[0].x && x <= TargetPoints[1].x) || (x >= TargetPoints[1].x && x <= TargetPoints[0].x) // for x
//     ) && (
//         (y >= TargetPoints[0].y && y <= TargetPoints[1].y) || (y >= TargetPoints[1].y && y <= TargetPoints[0].y) // for y
//     );
// }

// Utilidades de Raw Line

// Retorna os pontos limites de uma semireta
std::array<Coord, 2> RawLine::FindLineLimits(double x, double y, double angle, double length) {
    // Encontrando os pontos
    length /= 2;

    double x1 = x + length * cos(angle);
    double y1 = y + length * sin(angle);

    double x2 = x + length * -cos(angle);
    double y2 = y + length * -sin(angle);

    // A ordem dos dados deve ser a mesma
    std::array<Coord, 2> limits;

    if (x1 > x2) {
        limits[0] = Coord { x1, y1 };
        limits[1] = Coord { x2, y2 };

        // return std::array<Coord, 2> {
        //     Coord { x1, y1 },
        //     Coord { x2, y2 }
        // };
    } else {
        limits[0] = Coord { x2, y2 };
        limits[1] = Coord { x1, y1 };
    }

    return limits;

    // A ordem dos dados deve ser a mesma
    // return std::array<Coord, 2> {
    //     Coord { x2, y2 },
    //     Coord { x1, y1 }
    // };
}

// Encontra a interseção entre duas semiretas
Coord RawLine::FindLineIntersection(const RawLine& origin, const RawLine& target) {
    auto OriginPoints = FindLineLimits(origin.coord.x, origin.coord.y, origin.angle, origin.length);
    auto TargetPoints = FindLineLimits(target.coord.x, target.coord.y, target.angle, target.length);

    // Obtendo a lei que rege as retas (y = ax + b)

    Vec2D originCoeficients = RawLine::GetLineLawCoeficients(origin);
    Vec2D targetCoeficients = RawLine::GetLineLawCoeficients(target);

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

    return Coord { x, y };
}

Vec2D RawLine::GetLineLawCoeficients(const RawLine& line) {
    auto points = FindLineLimits(line.coord.x, line.coord.y, line.angle, line.length);

    // Encontrando os coeficientes da reta
    double aCoef = (points[0].y - points[1].y) / (points[0].x - points[1].x);
    double bCoef = points[0].y - aCoef * points[0].x;

    return Vec2D { aCoef, bCoef };
}

bool RawLine::IsPointAtLine(const Coord& coord, const RawLine& line) {
    Vec2D lineCoeficients = RawLine::GetLineLawCoeficients(line);

    double
        a = lineCoeficients[0],
        b = lineCoeficients[1];

    // Obtendo valor teórico do ponto na reta
    double yTest = coord.x * a + b;

    // Se o valor teórico for igual ao valor real, o ponto pertence à reta
    return abs(yTest - coord.y) < 0.001f;
}

// Verifica se duas semiretas estão colidindo
bool RawLine::LineCollision(const RawLine& origin, const RawLine& target) {
    // Obtendo a interseção das linhas
    auto Intersection = FindLineIntersection(origin, target);

    // Colisões especiais

    // Semiretas iguais totalmente sobrepostas
    if (isnan(Intersection.x) && isnan(Intersection.y)) {
        return true;
    }

    // Semiretas sobrepostas parcialmente
    auto originLimits = RawLine::FindLineLimits(origin.coord.x, origin.coord.y, origin.angle, origin.length);

    // Verifica cada ponto principal da reta origin, se está sobre a reta target
    //if (Line::IsPointAtLine(origin->coord, target) || Line::IsPointAtLine(originLimits[0], target) || Line::IsPointAtLine(originLimits[1], target)) {
    //    return true;
    //}

    auto OriginPoints = FindLineLimits(origin.coord.x, origin.coord.y, origin.angle, origin.length);
    auto TargetPoints = FindLineLimits(target.coord.x, target.coord.y, target.angle, target.length);

    double x = Intersection.x;
    double y = Intersection.y;

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

void RawLine::UpdatePosition(RawLine &line, const Coord &from, const Coord &to) {
    double dist = distance(from, to);
    double angle = angleBetweenPoints(from, to);

    double x = from.x + (dist/2) * cos(angle);
    double y = from.y + (dist/2) * sin(angle);

    line.coord.x = x;
    line.coord.y = y;
    line.angle = angle;
    line.length = dist;
}
