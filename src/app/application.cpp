#include "application.hpp"

#include <iostream>
#include <chrono>
#include <future>
#include <cmath>

#include "system/global.hpp"
#include "config/config.hpp"

#include "config/SDL2/graphics/Window.hpp"

#include "app/global.hpp"

#include "core/geometric/colliders.hpp"
#include "core/physics/physics.hpp"

void ApplicationInitialize(void) {
    window = CreateWindow(PROJECT_NAME);

    // Inicializando variáveis
    lineList.fill(nullptr);
    shapeList.fill(nullptr);

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
        if (shape == nullptr) {
            continue;
        }

        shape->color = RGBA_RED;
    }

    // Reset de cor
    for (auto line : lineList) {
        if (line == nullptr) {
            continue;
        }

        line->color = RGBA_RED;
    }

    // Verificação de colisão

    // Linha a linha
    for (int i = 0; i < lineList.size(); ++i) {
        if (lineList[i] == nullptr) {
            continue;
        }

        for (int j = i + 1; j < lineList.size(); ++j) {
            if (lineList[j] == nullptr) {
                continue;
            }

            if (LineToLineCollision(lineList[i], lineList[j])) {

                // Colisão detectada
                lineList[i]->isColliding = true;
                lineList[j]->isColliding = true;

                // Operações físicas
                BodyElasticCollision(lineList[i]->velX, lineList[i]->velY, lineList[j]->velX, lineList[j]->velY, lineList[i]->accX, lineList[i]->accY, lineList[j]->accX, lineList[j]->accY);
                ApplyTorqueByCollision(lineList[i]->velAng, lineList[j]->velAng, lineList[i]->coord.x, lineList[i]->coord.y, lineList[j]->coord.x, lineList[j]->coord.y, lineList[i]->length / 2, lineList[j]->length / 2);

                // Visualização
                lineList[i]->color = RGBA_GREEN;
                lineList[j]->color = RGBA_GREEN;

                // Prevenção para formas geométricas que se invadem
                double angle = angleBetweenPoints(lineList[i]->coord, lineList[j]->coord);

                lineList[i]->coord.x -= 1.5f * cos(angle);
                lineList[i]->coord.y -= 1.5f * sin(angle);

                lineList[j]->coord.x += 1.5f * cos(angle);
                lineList[j]->coord.y += 1.5f * sin(angle);

            }
        }
    }

    // Forma a forma
    for (int i = 0; i < shapeList.size(); ++i) {
        if (shapeList[i] == nullptr) {
            continue;
        }

        for (int j = i + 1; j < shapeList.size(); ++j) {
            if (shapeList[j] == nullptr) {
                continue;
            }

            if (ShapeToShapeCollision(shapeList[i], shapeList[j])) {

                // Colisão detectada
                shapeList[i]->isColliding = true;
                shapeList[j]->isColliding = true;

                // Operações físicas
                BodyElasticCollision(shapeList[i]->VelX, shapeList[i]->VelY, shapeList[j]->VelX, shapeList[j]->VelY, shapeList[i]->accX, shapeList[i]->accY, shapeList[j]->accX, shapeList[j]->accY);
                ApplyTorqueByCollision(shapeList[i]->VelAng, shapeList[j]->VelAng, shapeList[i]->coord.x, shapeList[i]->coord.y, shapeList[j]->coord.x, shapeList[j]->coord.y, shapeList[i]->Size, shapeList[j]->Size);

                // Visualzação
                shapeList[i]->color = RGBA_GREEN;
                shapeList[j]->color = RGBA_GREEN;

                // Prevenção para formas geométricas que se invadem
                double angle = angleBetweenPoints(shapeList[i]->coord, shapeList[j]->coord);

                shapeList[i]->coord.x -= 1.5f * cos(angle);
                shapeList[i]->coord.y -= 1.5f * sin(angle);

                shapeList[j]->coord.x += 1.5f * cos(angle);
                shapeList[j]->coord.y += 1.5f * sin(angle);
            }
        }
    }

    // Forma a linha
    for (int i = 0; i < shapeList.size(); ++i) {
        if (shapeList[i] == nullptr) {
            continue;
        }

        for (int j = 0; j < lineList.size(); ++j) {
            if (lineList[j] == nullptr) {
                continue;
            }

            if (ShapeToLineCollision(shapeList[i], lineList[j])) {

                // Colisão detectada
                shapeList[i]->isColliding = true;
                lineList[j]->isColliding = true;
                
                // Operações físicas
                BodyElasticCollision(shapeList[i]->VelX, shapeList[i]->VelY, lineList[j]->velX, lineList[j]->velY, shapeList[i]->accX, shapeList[i]->accY, lineList[j]->accX, lineList[j]->accY);
                ApplyTorqueByCollision(shapeList[i]->VelAng, lineList[j]->velAng, shapeList[i]->coord.x, shapeList[i]->coord.y, lineList[j]->coord.x, lineList[j]->coord.y, shapeList[i]->Size, lineList[j]->length / 2);

                // Visualização
                shapeList[i]->color = RGBA_GREEN;
                lineList[j]->color = RGBA_GREEN;

                // Prevenção para formas geométricas que se invadem
                double angle = angleBetweenPoints(shapeList[i]->coord, lineList[j]->coord);

                shapeList[i]->coord.x -= 1.5f * cos(angle);
                shapeList[i]->coord.y -= 1.5f * sin(angle);

                lineList[j]->coord.x += 1.5f * cos(angle);
                lineList[j]->coord.y += 1.5f * sin(angle);

            }
        }
    }

    // Atualizando todas as formas
    for (auto shape : shapeList) {
        if (shape == nullptr) {
            continue;
        }

        // reset de aceleração
        if (!shape->isColliding) {
            shape->accX = 0;
            shape->accY = 0;
        }

        shape->Update(deltatime);
    }

    // atualizando todas as linhas
    for (auto line : lineList) {
        if (line == nullptr) {
            continue;
        }

        // reset de aceleração
        if (!line->isColliding) {
            line->accX = 0;
            line->accY = 0;
        }

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
    const double OBJECT_SELECTED_MIN_VELOCITY = 1.f;

    double mouseVelAngle = atan2(mouse.velY, mouse.velX);

    double objectSelectedVelX = mouse.velX * OBJECT_SELECTED_VELOCITY_COEFFICIENT * cos(mouseVelAngle);
    double objectSelectedVelY = mouse.velY * OBJECT_SELECTED_VELOCITY_COEFFICIENT * sin(mouseVelAngle);

    

    if (mouse.velX != 0) {
        if (abs(objectSelectedVelX) < OBJECT_SELECTED_MIN_VELOCITY) {
            objectSelectedVelX = objectSelectedVelX > 0 ? OBJECT_SELECTED_MIN_VELOCITY : -OBJECT_SELECTED_MIN_VELOCITY;
        } else if (abs(objectSelectedVelX) > OBJECT_SELECTED_MAX_VELOCITY) {
            objectSelectedVelX = objectSelectedVelX > 0 ? OBJECT_SELECTED_MAX_VELOCITY : -OBJECT_SELECTED_MAX_VELOCITY;
        }

        objectSelectedVelX *= cos(mouseVelAngle);
    }

    if (mouse.velY != 0) {
        if (abs(objectSelectedVelY) < OBJECT_SELECTED_MIN_VELOCITY) {
            objectSelectedVelY = objectSelectedVelY > 0 ? OBJECT_SELECTED_MIN_VELOCITY : -OBJECT_SELECTED_MIN_VELOCITY;
        } else if (abs(objectSelectedVelY) > OBJECT_SELECTED_MAX_VELOCITY) {
            objectSelectedVelY = objectSelectedVelY > 0 ? OBJECT_SELECTED_MAX_VELOCITY : -OBJECT_SELECTED_MAX_VELOCITY;
        }

        objectSelectedVelY *= sin(mouseVelAngle);
    }

    if (mouse.right.hold && isElementSelected) { 
        if (lineSelected != nullptr) {
            if (distance(lineSelected->coord, Coord { absoluteMouseX, absoluteMouseY }) <= (lineSelected->length / 2) * 1.3f) {
                // Mantém o elemento na mesma posição
                lineSelected->coord.x = absoluteMouseX;
                lineSelected->coord.y = absoluteMouseY;

                // Atualização de velocidade
                lineSelected->velX = objectSelectedVelX;
                lineSelected->velY = objectSelectedVelY;
            }
        } else if (shapeSelected != nullptr) {
            if (distance(shapeSelected->coord, Coord { absoluteMouseX, absoluteMouseY }) <= shapeSelected->Size * 1.3f) {
                // Mantém o elemento na mesma posição
                shapeSelected->coord.x = absoluteMouseX;
                shapeSelected->coord.y = absoluteMouseY;

                // Atualização de velocidade
                shapeSelected->VelX = objectSelectedVelX;
                shapeSelected->VelY = objectSelectedVelY;
            }
        }
    }

}

void ApplicationRender(int deltatime) {
    // Limpeza de Janela
    window->Clear();

    // Render
    
    // Informações

    // Render distance
    double renderDistanceX, renderDistanceY;
    camera->GetRenderDistance(window, renderDistanceX, renderDistanceY);

    renderDistanceX += renderDistanceX * 1.1f + 50;
    renderDistanceY += renderDistanceY * 1.1f + 50;

    // Renderizando todas as formas
    for (auto shape : shapeList) {
        if (shape == nullptr) {
            continue;
        }
        
        if (abs(camera->x - shape->coord.x) > renderDistanceX || abs(camera->y - shape->coord.y) > renderDistanceY) {
            continue;
        }

        shape->Render(window, camera);
    }

    // Renderizando todas as linhas
    for (auto line : lineList) {
        if (line == nullptr) {
            continue;
        }

        if (abs(camera->x - line->coord.x) > renderDistanceX || abs(camera->y - line->coord.y) > renderDistanceY) {
            continue;
        }

        line->Render(window, camera);
    }

    // Renderiza os gráficos
    window->Render();
}
