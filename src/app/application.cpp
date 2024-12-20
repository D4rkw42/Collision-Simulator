#include "application.hpp"

#include <iostream>

#include "global.hpp"
#include "config/config.hpp"

#include "config/SDL2/graphics/Window.hpp"

#include "app/app-global.hpp"

#include "core/geometric/colliders.hpp"
#include "core/physics/physics.hpp"

void ApplicationInitialize(void) {
    window = CreateWindow(PROJECT_NAME);

    // for development
    CreateShape(shapeList, 4, 50, Coord { 0, 200 }, rad(45), 0.1f, 0, -0.01f);
    CreateLine(lineList, Coord { 200, 200}, Coord { 600, 600}, 0, 0);
}

void ApplicationQuit(void) {

}

//

void ApplicationUpdate(int deltatime) {
    // Atualizando informações de sistema

    // Atualizando câmera
    camera->UpdateCameraPosition(mouse);

    // Atualizando todas as formas
    for (auto shape : shapeList) {
        shape->Update(deltatime);
    }

    // atualizando todas as linhas
    for (auto line : lineList) {
        line->Update(deltatime);
    }

    // Verificação de colisão

    // Linha a linha
    for (int i = 0; i < lineList.size(); ++i) {
        for (int j = 0; j < lineList.size(); ++j) {
            if (j < i || j == i) {
                continue; // colisão já detectada ou colisão na mesma entidade
            }

            // visualização
            lineList[i]->color = RGBA_RED;
            lineList[j]->color = RGBA_RED;

            if (LineToLineCollision(lineList[i], lineList[j])) {

                // Colisão detectada

                // Operações físicas
                BodyElasticCollision(lineList[i]->velX, lineList[i]->velY, lineList[j]->velX, lineList[j]->velY);
                ApplyTorqueByCollision(lineList[i]->velAng, lineList[j]->velAng, lineList[i]->coord.x, lineList[i]->coord.y, lineList[j]->coord.x, lineList[j]->coord.y, lineList[i]->length / 2, lineList[j]->length / 2);

                // Visualização
                lineList[i]->color = RGBA_GREEN;
                lineList[j]->color = RGBA_GREEN;

            }
        }
    }

    // Forma a forma
    for (int i = 0; i < shapeList.size(); ++i) {
        for (int j = 0; j < shapeList.size(); ++j) {
            if (j < i || j == i) {
                continue; // colisão já detectada ou colisão entre a mesma entidade
            }

            // Visualização
            shapeList[i]->color = RGBA_RED;
            shapeList[j]->color = RGBA_RED;

            if (ShapeToShapeCollision(shapeList[i], shapeList[j])) {

                // Colisão detectada

                // Operações físicas
                BodyElasticCollision(shapeList[i]->VelX, shapeList[i]->VelY, shapeList[j]->VelX, shapeList[j]->VelY);
                ApplyTorqueByCollision(shapeList[i]->VelAng, shapeList[j]->VelAng, shapeList[i]->coord.x, shapeList[i]->coord.y, shapeList[j]->coord.x, shapeList[j]->coord.y, shapeList[i]->Size, shapeList[j]->Size);

                // Visualzação
                shapeList[i]->color = RGBA_GREEN;
                shapeList[j]->color = RGBA_GREEN;

            }
        }
    }

    // Forma a linha
    for (int i = 0; i < shapeList.size(); ++i) {
        for (int j = 0; j < lineList.size(); ++j) {
            // Visualização
            shapeList[i]->color = RGBA_RED;
            lineList[j]->color = RGBA_RED;

            if (ShapeToLineCollision(shapeList[i], lineList[j])) {

                // Colisão detectada
                
                // Operações físicas
                BodyElasticCollision(shapeList[i]->VelX, shapeList[i]->VelY, lineList[j]->velX, lineList[j]->velY);
                ApplyTorqueByCollision(shapeList[i]->VelAng, lineList[j]->velAng, shapeList[i]->coord.x, shapeList[i]->coord.y, lineList[j]->coord.x, lineList[j]->coord.y, shapeList[i]->Size, lineList[j]->length / 2);

                // Visualização
                shapeList[i]->color = RGBA_GREEN;
                lineList[j]->color = RGBA_GREEN;

            }
        }
    }

    // Colorindo linhas/formas selecionadas
    if (lineSelected != nullptr) {
        lineSelected->color = RGBA_WHITE;
    }

    if (shapeSelected != nullptr) {
        shapeSelected->color = RGBA_WHITE;
    }

}

void ApplicationRender(int deltatime) {
    // Limpeza de Janela
    window->Clear();

    // Render

    // Renderizando todas as formas
    for (auto shape : shapeList) {
        shape->Render(window, camera);
    }

    // Renderizando todas as linhas
    for (auto line : lineList) {
        line->Render(window, camera);
    }

    // Renderiza os gráficos
    window->Render();
}
