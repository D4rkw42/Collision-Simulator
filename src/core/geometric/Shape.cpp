// Definições para formas geométricas regulares

#include "Shape.hpp"

#include <iostream>

Shape::Shape(int vertex, int size, Coord coord, double angle, double velX, double velY, double velAng, RGBA color) {
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

    this->isColliding = false;
}

void Shape::Render(std::shared_ptr<Window> window, std::shared_ptr<Camera> camera) {
    LineList shapeLines = GetShapeLines();

    for (auto line : shapeLines) {
        line->Render(window, camera);
    }
}

LineList Shape::GetShapeLines(void) {
    LineList shapeLines;

    // Encontrando todos os vértices
    std::vector<Coord> vertices;
    double angle = this->Angle;

    double step = rad(360) / this->Vertex;

    for (int i = 0; i < this->Vertex; ++i) {
        double x = this->coord.x + this->Size * cos(angle);
        double y = this->coord.y + this->Size * sin(angle);

        vertices.push_back(Coord { x, y });

        // Passando para o próximo ângulo
        angle += step;

        if (angle > rad(360)) {
            angle -= rad(360);
        }
    }

    // Encontrando todas as arestas
    for (int i = 0; i < this->Vertex; ++i) {
        int k = i;
        int l = i + 1;

        if (l == this->Vertex) {
            l = 0;
        }

        // Criando linhas
        auto line = CreateLine(vertices[k], vertices[l], 0, 0, 0, this->color);
        shapeLines.push_back(line);
    }

    return shapeLines;
}
