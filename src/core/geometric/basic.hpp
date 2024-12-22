// Basic concepts of geometric

#pragma once

#include <cmath>

#define PI 3.14159265359f

// Coordinate definition
struct Coord {
    double x, y;
};

// Operações

inline double rad(double angle) {
    return angle * PI / 180;
}

inline double distance(Coord from, Coord to) {
    double dX = from.x - to.x;
    double dY = from.y - to.y;

    return sqrt(dX * dX + dY * dY);
}

inline double angleBetweenPoints(Coord point1, Coord point2) {
    return atan2(point2.y - point1.y, point2.x - point1.x);
}

inline Coord FindMediumPoint(Coord point1, Coord point2) {
    double x = (point1.x + point2.x) / 2;
    double y = (point1.y + point2.y) / 2;

    return Coord { x, y };
}
