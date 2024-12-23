// Funções para verificar a colisão entre objetos

#include "colliders.hpp"

#include <vector>

bool LineToLineCollision(const std::shared_ptr<Line>& origin, const std::shared_ptr<Line>& target) {
    RawLine originRawLine(origin->coord, origin->length, origin->angle);
    RawLine targetRawLine(target->coord, target->length, target->angle);

    return RawLine::LineCollision(originRawLine, targetRawLine);
}

bool ShapeToShapeCollision(const std::shared_ptr<Shape>& origin, const std::shared_ptr<Shape>& target) {
    std::vector<RawLine> originLines = origin->GetShapeLines();
    std::vector<RawLine> targetLines = target->GetShapeLines();

    for (auto oLine : originLines) {
        for (auto tLine : targetLines) {
            if (RawLine::LineCollision(oLine, tLine)) {
                return true;
            }
        }
    }

    return false;
}

bool ShapeToLineCollision(const std::shared_ptr<Shape>& shape, const std::shared_ptr<Line>& line) {
    std::vector<RawLine> shapeLines = shape->GetShapeLines();
    RawLine rawLine = CreateRawLine(line->coord, line->length, line->angle);

    for (auto sLine : shapeLines) {
        if (RawLine::LineCollision(sLine, rawLine)) {
            return true;
        }
    }

    return false;
}
