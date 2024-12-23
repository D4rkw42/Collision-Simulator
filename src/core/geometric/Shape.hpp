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
        std::vector<RawLine> shapeLines;
        Coord coord;

        double VelX, VelY, accX, accY;
        double Angle, VelAng;

        int Size, Vertex; // tamanho/número de vértices

        double isColliding;

        RGBA color;

        Shape(int vertex, int size, const Coord& coord, double angle, double velX, double velY, double velAng, const RGBA& color);

        void Update(int deltatime);
        void Render(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera);

        void UpdateShapeLines(void);

        std::vector<RawLine> GetShapeLines(void);
        std::vector<Coord> GetShapeVertices(void);

};

// Definições
typedef std::array<std::shared_ptr<Shape>, 30> ShapeList;

// Criação dinâmica de formas
inline std::shared_ptr<Shape> CreateShape(int vertex, int size, const Coord& coord, double angle, double velX, double velY, double velAng, const RGBA& color = RGBA_RED) {
    return std::make_shared<Shape>(vertex, size, coord, angle, velX, velY, velAng, color);
}

// Criação dinâmica para listas
inline bool CreateShapeToList(ShapeList& list, int vertex, int size, const Coord& coord, double angle, double velX, double velY, double velAng, const RGBA& color = RGBA_RED) {
    auto shape = CreateShape(vertex, size, coord, angle, velX, velY, velAng, color);

    for (int i = 0; i < list.size(); ++i) {
        if (list[i] == nullptr) {
            list[i] = shape;
            // retorna true se bem sucedido
            return true;
        }
    }

    return false;
}
