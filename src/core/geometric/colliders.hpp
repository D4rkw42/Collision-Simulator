// Funções para verificar a colisão entre objetos

#pragma once

#include <memory>

#include "core/geometric/Line.hpp"
#include "core/geometric/Shape.hpp"

bool LineToLineCollision(const std::shared_ptr<Line>& origin, const std::shared_ptr<Line>& target); // colisão linha a linha
bool ShapeToShapeCollision(const std::shared_ptr<Shape>& origin, const std::shared_ptr<Shape>& target); // colisão forma a forma
bool ShapeToLineCollision(const std::shared_ptr<Shape>& shape, const std::shared_ptr<Line>& line); // colisão forma a linha
