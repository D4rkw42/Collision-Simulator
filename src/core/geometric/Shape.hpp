// Definições para formas geométricas regulares

#pragma once

#include <memory>
#include <vector>

#include "config/SDL2/graphics/Window.hpp"

#include "core/geometric/basic.hpp"
#include "core/geometric/Line.hpp"
#include "core/geometric/RGBAColor.hpp"

#include "utils/world/camera.hpp"

class Shape {
    public:
        Coord coord;
        double VelX, VelY, accX, accY;
        double Angle, VelAng;

        int Size, Vertex; // tamanho/número de vértices

        double isColliding;

        RGBA color;

        Shape(int vertex, int size, Coord coord, double angle, double velX, double velY, double velAng, RGBA color);

        void Update(int deltatime);
        void Render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera);

        LineList GetShapeLines(void);

};

// Definições
typedef std::vector<std::shared_ptr<Shape>> ShapeList;

// Criação dinâmica de formas
inline std::shared_ptr<Shape> CreateShape(int vertex, int size, Coord coord, double angle, double velX, double velY, double velAng, RGBA color = RGBA_RED) {
    return std::make_shared<Shape>(vertex, size, coord, angle, velX, velY, velAng, color);
}

// Criação dinâmica para listas
inline void CreateShapeToList(ShapeList& list, int vertex, int size, Coord coord, double angle, double velX, double velY, double velAng, RGBA color = RGBA_RED) {
    auto shape = CreateShape(vertex, size, coord, angle, velX, velY, velAng, color);
    list.push_back(shape);
}
