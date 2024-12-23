// Basic concepts of geometric

#pragma once

#include <cmath>
#include <array>

constexpr double PI = 3.14159265359f;

// Vector 2D definitions
typedef std::array<double, 2> Vec2D;

// Coordinate definition
struct Coord {
    double x, y;
};

// Operações

constexpr double rad(double angle) {
    return angle * PI / 180;
}

constexpr double distance(const Coord& from, const Coord& to) {
    double dX = from.x - to.x;
    double dY = from.y - to.y;

    return sqrt(dX * dX + dY * dY);
}

constexpr double angleBetweenPoints(const Coord& point1, const Coord& point2) {
    return atan2(point2.y - point1.y, point2.x - point1.x);
}

inline Coord FindMediumPoint(const Coord& point1, const Coord& point2) {
    double x = (point1.x + point2.x) / 2;
    double y = (point1.y + point2.y) / 2;

    return Coord { x, y };
}
