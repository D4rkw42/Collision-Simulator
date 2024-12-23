// Definição básica de linha

#pragma once

#include <memory>
#include <vector>
#include <array>

#include "config/SDL2/graphics/Window.hpp"

#include "core/geometric/basic.hpp"
#include "core/geometric/RGBAColor.hpp"

#include "utils/world/camera.hpp"

// Estrutura de linha simples, só para calcular as colisões e não queimar minha RAM com alocação de memória :P
class RawLine {
    public:
        Coord coord;
        double length, angle;

        RawLine(const Coord& coord, double length, double angle) : coord(coord), length(length), angle(angle) {};

        // Utilidades

        static std::array<Coord, 2> FindLineLimits(double x, double y, double angle, double length); // retorna os pontos limite de uma semireta
        static Coord FindLineIntersection(const RawLine& origin, const RawLine& target); // encontra a interseção entre duas semiretas

        static Vec2D GetLineLawCoeficients(const RawLine& line); // obtém os coeficientes da lei da reta
        static bool IsPointAtLine(const Coord& coord, const RawLine& line); // verifica se um ponto pertence a uma reta

        static bool LineCollision(const RawLine& origin, const RawLine& target); // verifica se duas semiretas estão colidindo

        // Atualiza a posição de uma raw line
        static void UpdatePosition(RawLine& line, const Coord& from, const Coord& to);
        
};

// Criação dinâmica de raw lines
inline RawLine CreateRawLine(const Coord& coord, double length, double angle) {
    return RawLine(coord, length, angle);
}

inline RawLine CreateRawLine(const Coord& from, const Coord& to) {
    double dist = distance(from, to);
    double angle = angleBetweenPoints(from, to);

    double x = from.x + (dist/2) * cos(angle);
    double y = from.y + (dist/2) * sin(angle);

    return CreateRawLine(Coord { x, y }, dist, angle);
}

class Line {
    public:
        // length = [px]; angle = [rad]
        double length, angle;

        double velX, velY, accX, accY, velAng; // center of line
        Coord coord; // coordenadas

        double isColliding;

        RGBA color; // color of line

        Line(const Coord& coord, double velX, double velY, double velAng, double length, double angle, const RGBA& color);

        void Update(int deltatime);
        void Render(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera);

        // utilities

        // Faz a renderização de uma linha genérica
        static void RenderLine(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera, const Coord& coord, double length, double angle, const RGBA& color);

        // static std::array<Coord, 2> FindLineLimits(double x, double y, double angle, double length); // retorna os pontos limite de uma semireta
        // static Coord FindLineIntersection(const std::shared_ptr<Line>& origin, const std::shared_ptr<Line>& target); // encontra a interseção entre duas semiretas

        // static Vec2D GetLineLawCoeficients(const std::shared_ptr<Line>& line); // obtém os coeficientes da lei da reta
        // static bool IsPointAtLine(const Coord& coord, const std::shared_ptr<Line>& line); // verifica se um ponto pertence a uma reta

        // static bool LineCollision(const std::shared_ptr<Line>& origin, const std::shared_ptr<Line>& target); // verifica se duas semiretas estão colidindo
        
};

// Definições de tipagem
typedef std::array<std::shared_ptr<Line>, 50> LineList;

// Criação dinâmica de linhas
inline std::shared_ptr<Line> CreateLine(const Coord& coord, double velX, double velY, double velAng, double length, double angle = 0, const RGBA& color = RGBA_RED) {
    return std::make_shared<Line>(coord, velX, velY, velAng, length, angle, color);
}

inline std::shared_ptr<Line> CreateLine(const Coord& from, const Coord& to, double velX, double velY, double velAng, const RGBA& color = RGBA_RED) {
    double dist = distance(from, to);
    double angle = angleBetweenPoints(from, to);

    double x = from.x + (dist/2) * cos(angle);
    double y = from.y + (dist/2) * sin(angle);

    return CreateLine(Coord { x, y }, velX, velY, velAng, dist, angle, color);
}

// Criação dinâmica para listas
inline bool CreateLineToList(LineList& list, const Coord& coord, double velX, double velY, double velAng, double length, double angle = 0, const RGBA& color = RGBA_RED) {
    auto line = CreateLine(coord, velX, velY, velAng, length, angle, color);
    
    for (int i = 0; i < list.size(); ++i) {
        if (list[i] == nullptr) {
            list[i] = line;
            // retora true se bem sucedido
            return true;
        }
    }

    return false;
}

inline bool CreateLineToList(LineList& list, const Coord& from, const Coord& to, double velX, double velY, double velAng, const RGBA& color = RGBA_RED) {
    auto line = CreateLine(from, to, velX, velY, velAng, color);
    
    for (int i = 0; i < list.size(); ++i) {
        if (list[i] == nullptr) {
            list[i] = line;
            // retorna true se bem sucedido
            return true;
        }
    }

    return false;
}
