#include "application.hpp"

#include <iostream>
#include <chrono>
#include <future>

#include "system/global.hpp"
#include "config/config.hpp"

#include "config/SDL2/graphics/Window.hpp"

#include "app/global.hpp"

#include "core/geometric/colliders.hpp"
#include "core/physics/physics.hpp"

void ApplicationInitialize(void) {
    window = CreateWindow(PROJECT_NAME);

    // Registrando keys
    RegisterNewKey(keyList, SDL_SCANCODE_LSHIFT, "LEFT_SHIFT");
}

void ApplicationQuit(void) {

}

//

void ApplicationUpdate(int deltatime) {
    // Atualizando informações de sistema

    // Atualizando câmera
    camera->UpdateCameraPosition(mouse);

    // Atualizando velocidade do mouse
    static int lastMouseX = mouse.x;
    static int lastMouseY = mouse.y;

    double instantMouseVelY = (mouse.y - lastMouseY) / deltatime;
    double instantMouseVelX = (mouse.x - lastMouseX) / deltatime;

    mouse.velX = (mouse.velX + instantMouseVelX) / 2;
    mouse.velY = (mouse.velY + instantMouseVelY) / 2;

    if (abs(mouse.velX) < pow(10, -10)) {
        mouse.velX = 0;
    }

    if (abs(mouse.velY) < pow(10, -10)) {
        mouse.velY = 0;
    }

    lastMouseX = mouse.x;
    lastMouseY = mouse.y;

    // Obtendo dados importantes

    // Posição absoluta do mouse na tela
    double absoluteMouseX, absoluteMouseY;
    camera->GetAbsolutePosition(window, mouse.x, mouse.y, absoluteMouseX, absoluteMouseY);

    // Reset de cor
    for (auto shape : shapeList) {
        shape->color = RGBA_RED;
    }

    // Reset de cor
    for (auto line : lineList) {
        line->color = RGBA_RED;
    }

    // Verificação de colisão

    // Linha a linha
    for (int i = 0; i < lineList.size(); ++i) {
        for (int j = i + 1; j < lineList.size(); ++j) {
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
        for (int j = i + 1; j < shapeList.size(); ++j) {
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

    // Atualizando todas as formas
    for (auto shape : shapeList) {
        shape->Update(deltatime);
    }

    // atualizando todas as linhas
    for (auto line : lineList) {
        line->Update(deltatime);
    }

    // Colorindo linhas/formas selecionadas
    if (lineSelected != nullptr) {
        lineSelected->color = RGBA_WHITE;
    }

    if (shapeSelected != nullptr) {
        shapeSelected->color = RGBA_WHITE;
    }

    // Atualiza a velocidade dos objetos selecionados com base no movimento do mouse (grabbing)

    const double OBJECT_SELECTED_VELOCITY_COEFFICIENT = 1.15f;
    const double OBJECT_SELECTED_MAX_VELOCITY = 3.f;
    const double OBJECT_SELECTED_MIN_VELOCITY = 0.8f;

    double objectSelectedVelX = mouse.velX * OBJECT_SELECTED_VELOCITY_COEFFICIENT;
    double objectSelectedVelY = mouse.velY * OBJECT_SELECTED_VELOCITY_COEFFICIENT;

    if (mouse.velX != 0) {
        if (abs(objectSelectedVelX) < OBJECT_SELECTED_MIN_VELOCITY) {
            objectSelectedVelX = objectSelectedVelX > 0 ? OBJECT_SELECTED_MIN_VELOCITY : -OBJECT_SELECTED_MIN_VELOCITY;
        } else if (abs(objectSelectedVelX) > OBJECT_SELECTED_MAX_VELOCITY) {
            objectSelectedVelX = objectSelectedVelX > 0 ? OBJECT_SELECTED_MAX_VELOCITY : -OBJECT_SELECTED_MAX_VELOCITY;
        }
    }

    if (mouse.velY != 0) {
        if (abs(objectSelectedVelY) < OBJECT_SELECTED_MIN_VELOCITY) {
            objectSelectedVelY = objectSelectedVelY > 0 ? OBJECT_SELECTED_MIN_VELOCITY : -OBJECT_SELECTED_MIN_VELOCITY;
        } else if (abs(objectSelectedVelY) > OBJECT_SELECTED_MAX_VELOCITY) {
            objectSelectedVelY = objectSelectedVelY > 0 ? OBJECT_SELECTED_MAX_VELOCITY : -OBJECT_SELECTED_MAX_VELOCITY;
        }
    }

    if (mouse.right.hold && isElementSelected) { 
        if (lineSelected != nullptr) {
            // Mantém o elemento na mesma posição
            lineSelected->coord.x = absoluteMouseX;
            lineSelected->coord.y = absoluteMouseY;

            // Atualização de velocidade
            lineSelected->velX = objectSelectedVelX;
            lineSelected->velY = objectSelectedVelY;
        } else if (shapeSelected != nullptr) {
            // Mantém o elemento na mesma posição
            shapeSelected->coord.x = absoluteMouseX;
            shapeSelected->coord.y = absoluteMouseY;

            // Atualização de velocidade
            shapeSelected->VelX = objectSelectedVelX;
            shapeSelected->VelY = objectSelectedVelY;
        }
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
