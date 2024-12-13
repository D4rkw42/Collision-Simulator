// Funções para verificar a colisão entre objetos

#include "colliders.hpp"

bool LineToLineCollision(std::shared_ptr<Line> origin, std::shared_ptr<Line> target) {
    return Line::LineCollision(origin, target);
}

bool ShapeToShapeCollision(std::shared_ptr<Shape> origin, std::shared_ptr<Shape> target) {
    LineList originLines = origin->GetShapeLines();

    // Verificando linha a linha
    for (auto line : originLines) {
        if (ShapeToLineCollision(target, line)) {
            return true;
        }
    }

    return false;
}

bool ShapeToLineCollision(std::shared_ptr<Shape> shape, std::shared_ptr<Line> line) {
    LineList shapeLines = shape->GetShapeLines();

    // Verificando linha a linha
    for (auto sLine : shapeLines) {
        if (LineToLineCollision(sLine, line)) {
            return true;
        }
    }

    return false;
}
