// Definições para formas geométricas regulares

#include "Shape.hpp"

#include <iostream>

Shape::Shape(int vertex, int size, const Coord& coord, double angle, double velX, double velY, double velAng, const RGBA& color) {
    if (vertex < 3) {
        std::cout << "Can't create a shape with less 3 vertices." << "\n";
        throw new std::exception();
    }

    this->Vertex = vertex;
    this->Size = size;

    this->coord = coord;

    this->VelY = velY;
    this->VelX = velX;

    this->accX = 0;
    this->accY = 0;

    this->Angle = angle;
    this->VelAng = velAng;

    this->color = color;

    // criando linhas da forma
    this->shapeLines = std::vector<RawLine>();
    this->shapeLines.reserve(this->Vertex);

    std::vector<Coord> vertices = GetShapeVertices();

    // Encontrando todas as arestas
    for (int i = 0; i < this->Vertex; ++i) {
        int k = i;
        int l = i + 1;

        if (l == this->Vertex) {
            l = 0;
        }

        // atualizando linhas
        this->shapeLines.emplace_back(CreateRawLine(vertices[k], vertices[l]));
    }

    this->isColliding = false;
}

//

void Shape::Update(int deltatime) {
    // Primeira atualização de velocidade
    this->VelX += this->accX * 0.5f;
    this->VelY += this->accY * 0.5f;

    this->coord.x += this->VelX;
    this->coord.y += this->VelY;

    // Segunda atualização de velocidade
    this->VelX += this->accX * 0.5f;
    this->VelY += this->accY * 0.5f;

    this->Angle += this->VelAng;

    if (this->Angle > rad(360)) {
        this->Angle -= rad(360);
    }

    if (this->Angle < 0) {
        this->Angle += rad(360);
    }

    UpdateShapeLines();

    this->isColliding = false;
}

void Shape::Render(const std::shared_ptr<Window>& window, const std::shared_ptr<Camera>& camera) {
    for (auto line : this->shapeLines) {
        Line::RenderLine(window, camera, line.coord, line.length, line.angle, this->color);
    }
}

void Shape::UpdateShapeLines(void) {
    std::vector<Coord> vertices = GetShapeVertices();

    // Encontrando todas as arestas
    for (int i = 0; i < this->Vertex; ++i) {
        int k = i;
        int l = i + 1;

        if (l == this->Vertex) {
            l = 0;
        }

        // atualizando linhas
        RawLine::UpdatePosition(this->shapeLines[i], vertices[k], vertices[l]);
    }
}

std::vector<RawLine> Shape::GetShapeLines(void) {
    return this->shapeLines;
}

std::vector<Coord> Shape::GetShapeVertices(void) {
    // Encontrando todos os vértices
    std::vector<Coord> vertices(this->Vertex);

    double angle = this->Angle;

    double step = rad(360) / this->Vertex;

    for (int i = 0; i < this->Vertex; ++i) {
        double x = this->coord.x + this->Size * cos(angle);
        double y = this->coord.y + this->Size * sin(angle);

        vertices[i] = Coord { x, y };

        // Passando para o próximo ângulo
        angle += step;

        if (angle > rad(360)) {
            angle -= rad(360);
        }
    }

    return vertices;
}
