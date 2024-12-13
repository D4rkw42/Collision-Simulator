// Definição básica de linha

#pragma once

#include <memory>
#include <vector>

#include "config/SDL2/graphics/Window.hpp"

#include "core/geometric/basic.hpp"
#include "core/geometric/RGBAColor.hpp"

class Line {
    public:
        // length = [px]; angle = [rad]
        double length, angle;

        double velX, velY; // center of line
        Coord coord; // coordenadas

        RGBA color; // color of line

        Line(Coord coord, double velX, double velY, double length, double angle, RGBA color);

        void Update(int deltatime);
        void Render(std::shared_ptr<Window> window);


        // utilities

        static std::vector<Coord> FindLineLimits(Line line); // retorna os pontos limite de uma semireta
        static Coord* FindLineIntersection(Line origin, Line target); // encontra a interseção entre duas semiretas

        static std::vector<double> GetLineLawCoeficients(Line line); // obtém os coeficientes da lei da reta
        static bool IsPointAtLine(Coord coord, Line line); // verifica se um ponto pertence a uma reta

        static bool LineCollision(Line origin, Line target); // verifica se duas semiretas estão colidindo
        
};

// Definições de tipagem
typedef std::vector<std::shared_ptr<Line>> LineList;

// Criação dinâmica de linhas
inline std::shared_ptr<Line> CreateLine(Coord coord, double velX, double velY, double length, double angle = 0, RGBA color = RGBA_RED) {
    return std::make_shared<Line>(coord, velX, velY, length, angle, color);
}

inline std::shared_ptr<Line> CreateLine(Coord from, Coord to, double velX, double velY, RGBA color = RGBA_RED) {
    double dist = distance(from, to);
    double angle = angleBetweenPoints(from, to);

    double x = from.x + (dist/2) * cos(angle);
    double y = from.y + (dist/2) * sin(angle);

    return CreateLine(Coord { x, y }, velX, velY, dist, angle, color);
}
