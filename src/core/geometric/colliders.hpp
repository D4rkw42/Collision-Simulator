// Funções para verificar a colisão entre objetos

#pragma once

#include <memory>

#include "core/geometric/Line.hpp"
#include "core/geometric/Shape.hpp"

bool LineToLineCollision(std::shared_ptr<Line> origin, std::shared_ptr<Line> target); // colisão linha a linha
bool ShapeToShapeCollision(std::shared_ptr<Shape> origin, std::shared_ptr<Shape> target); // colisão forma a forma
bool ShapeToLineCollision(std::shared_ptr<Shape> shape, std::shared_ptr<Line> line); // colisão forma a linha
