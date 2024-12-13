// Definições para formas geométricas regulares

#pragma once

#include <memory>
#include <vector>

#include "config/SDL2/graphics/Window.hpp"

#include "core/geometric/basic.hpp"
#include "core/geometric/Line.hpp"
#include "core/geometric/RGBAColor.hpp"

class Shape {
    public:
        Coord coord;
        double VelX, VelY;
        double Angle, VelAng;

        int Size, Vertex; // tamanho/número de vértices

        RGBA color;

        Shape(int vertex, int size, Coord coord, double angle, double velX, double velY, double velAng, RGBA color);

        void Update(int deltatime);
        void Render(std::shared_ptr<Window> window);

        LineList GetShapeLines(void);

};

// Criação dinâmica de formas
inline std::shared_ptr<Shape> CreateShape(int vertex, int size, Coord coord, double angle, double velX, double velY, double velAng, RGBA color = RGBA_RED) {
    return std::make_shared<Shape>(vertex, size, coord, angle, velX, velY, velAng, color);
}
