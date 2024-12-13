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

        Line(Coord coord, double velX, double velY, double length, double angle = 0, RGBA color = RGBA_RED);

        void Update(int deltatime);
        void Render(std::shared_ptr<Window> window);


        // utilities

        static std::vector<Coord> FindLineLimits(Line line); // retorna os pontos limite de uma semireta
        static Coord* FindLineIntersection(Line origin, Line target); // encontra a interseção entre duas semiretas

        static std::vector<double> GetLineLawCoeficients(Line line); // obtém os coeficientes da lei da reta
        static bool IsPointAtLine(Coord coord, Line line); // verifica se um ponto pertence a uma reta

        static bool LineCollision(Line origin, Line target); // verifica se duas semiretas estão colidindo
        
};
