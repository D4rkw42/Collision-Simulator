// Definição básica de linha

#pragma once

#include <memory>
#include <vector>

#include "config/SDL2/graphics/Window.hpp"

#include "core/geometric/basic.hpp"
#include "core/geometric/RGBAColor.hpp"

#include "utils/world/camera.hpp"

class Line {
    public:
        // length = [px]; angle = [rad]
        double length, angle;

        double velX, velY, accX, accY, velAng; // center of line
        Coord coord; // coordenadas

        double isColliding;

        RGBA color; // color of line

        Line(Coord coord, double velX, double velY, double velAng, double length, double angle, RGBA color);

        void Update(int deltatime);
        void Render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera);

        // utilities

        static std::vector<Coord> FindLineLimits(double x, double y, double angle, double length); // retorna os pontos limite de uma semireta
        static Coord FindLineIntersection(std::shared_ptr<Line> origin, std::shared_ptr<Line> target); // encontra a interseção entre duas semiretas

        static std::vector<double> GetLineLawCoeficients(std::shared_ptr<Line> line); // obtém os coeficientes da lei da reta
        static bool IsPointAtLine(Coord coord, std::shared_ptr<Line> line); // verifica se um ponto pertence a uma reta

        static bool LineCollision(std::shared_ptr<Line> origin, std::shared_ptr<Line> target); // verifica se duas semiretas estão colidindo
        
};

// Definições de tipagem
typedef std::vector<std::shared_ptr<Line>> LineList;

// Criação dinâmica de linhas
inline std::shared_ptr<Line> CreateLine(Coord coord, double velX, double velY, double velAng, double length, double angle = 0, RGBA color = RGBA_RED) {
    return std::make_shared<Line>(coord, velX, velY, velAng, length, angle, color);
}

inline std::shared_ptr<Line> CreateLine(Coord from, Coord to, double velX, double velY, double velAng, RGBA color = RGBA_RED) {
    double dist = distance(from, to);
    double angle = angleBetweenPoints(from, to);

    double x = from.x + (dist/2) * cos(angle);
    double y = from.y + (dist/2) * sin(angle);

    return CreateLine(Coord { x, y }, velX, velY, velAng, dist, angle, color);
}

// Criação dinâmica para listas
inline void CreateLineToList(LineList& list, Coord coord, double velX, double velY, double velAng, double length, double angle = 0, RGBA color = RGBA_RED) {
    auto line = CreateLine(coord, velX, velY, velAng, length, angle, color);
    list.push_back(line);
}

inline void CreateLineToList(LineList& list, Coord from, Coord to, double velX, double velY, double velAng, RGBA color = RGBA_RED) {
    auto line = CreateLine(from, to, velX, velY, velAng, color);
    list.push_back(line);
}
