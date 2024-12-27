/*
    Wrapper para manipulação de eventos
*/

#include "event-handler.hpp"

#include <iostream>

#include <effolkronium/random.hpp>

#include "global.hpp"
#include "app/global.hpp"

#include "core/geometric/basic.hpp"

using random = effolkronium::random_static;

// eventos separador por tipo

void EventMouseClick(const SDL_Event& event) {
    // for utility
    // Posições absolutas do mouse
    double mouseAbsoluteX, mouseAbsoluteY;
    camera->GetAbsolutePosition(window, mouse.x, mouse.y, mouseAbsoluteX, mouseAbsoluteY);

    // atualizando definições de mouse
    if (event.button.button == SDL_BUTTON_RIGHT) { // atualizando dados para bnt right
        mouse.right.hold = false;

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouse.right.hold = true;
            mouse.right.hold_x = mouse.x;
            mouse.right.hold_y = mouse.y;
        }
    } else { // atualizando dados para bnt left
        mouse.left.hold = false;

        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mouse.left.hold = true;
            mouse.left.hold_x = mouse.x;
            mouse.left.hold_y = mouse.y;
        }
    }

    // App

    // Buscando novas peças para serem selecionadas
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT) {
        for (auto line : lineList) {
            if (line == nullptr) {
                continue;
            }

            if (distance(line->coord, Coord { mouseAbsoluteX, mouseAbsoluteY }) <= line->length / 2) {
                lineSelected = line;
                shapeSelected = nullptr;

                // Eliminando velocidade ao ser selecionado
                lineSelected->velX = 0;
                lineSelected->velY = 0;

                isElementSelected = true;
                break;
            }
        }

        // Seleção de forma terá prioridade
        for (auto shape : shapeList) {
            if (shape == nullptr) {
                continue;
            }

            if (distance(shape->coord, Coord { mouseAbsoluteX, mouseAbsoluteY }) <= shape->Size) {
                shapeSelected = shape;
                lineSelected = nullptr;

                // Eliminando velocidade ao ser selecionado
                shapeSelected->VelX = 0;
                shapeSelected->VelY = 0;

                isElementSelected = true;
                break;
            }
        }
    }

    // Fazendo a invocação de peças e elementos aleatórios
    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT && GetKeyState(keyList, "LEFT_SHIFT").hold) {
        bool objectFound = false;

        // deselecionando elementos por segurança e funcionalidade
        lineSelected = nullptr;
        shapeSelected = nullptr;

        // deletando objetos caso sejam encontradosconst SDL_Event&

        for (int i = 0; i < lineList.size(); ++i) {
            if (lineList[i] == nullptr) {
                continue;
            }

            if (distance(lineList[i]->coord, Coord { mouseAbsoluteX, mouseAbsoluteY }) <= (lineList[i]->length / 2) * 1.2f) {
                // lineList.erase(lineList.begin() + i);
                lineList[i] = nullptr;
                objectFound = true;
                break;
            }
        }

        if (!objectFound) {
            for (int i = 0; i < shapeList.size(); ++i) {
                if (shapeList[i] == nullptr) {
                    continue;
                }

                if (distance(shapeList[i]->coord, Coord { mouseAbsoluteX, mouseAbsoluteY }) <= shapeList[i]->Size * 1.2f) {
                    // shapeList.erase(shapeList.begin() + i);
                    shapeList[i] = nullptr;
                    objectFound = true;
                    break;
                }
            }
        }

        // cria um novo elemento
        const int numberOfVertices = random::get<int>(1, 8);
        
        const double invokedElementVelX = random::get<double>(-0.2f, 0.2f);
        const double invokedElementVelY = random::get<double>(-0.2f, 0.2f);

        const double invokedElementAngle = random::get<double>(rad(0), rad(360));
        const double invokedElementAngleVel = random::get<double>(-0.005f, 0.005f);

        const double invokedElementSize = random::get<double>(20, 130);

        if (!objectFound) {
            if (numberOfVertices == 1 || numberOfVertices == 2) {
                CreateLineToList(lineList, Coord { mouseAbsoluteX, mouseAbsoluteY }, invokedElementVelX, invokedElementVelY, invokedElementAngleVel, invokedElementSize * 6, invokedElementAngle);
                std::cout << "[Collision Simulator] You have spanwed a segment at (" << int(mouseAbsoluteX) << ", " << int(mouseAbsoluteY) << ")." << "\n";
            } else {
                CreateShapeToList(shapeList, numberOfVertices, invokedElementSize, Coord { mouseAbsoluteX, mouseAbsoluteY }, invokedElementAngle, invokedElementVelX, invokedElementVelY, invokedElementAngleVel);
                std::cout << "[Collision Simulator] You have spanwed a shape at (" << int(mouseAbsoluteX) << ", " << int(mouseAbsoluteY) << ")." << "\n";
            }
        }
    }
}

void EventMouseMove(const SDL_Event& event) {
    // atualizando definições de mouse
    mouse.x = event.motion.x;
    mouse.y = event.motion.y;
}

void EventMouseScrolling(const SDL_Event& event) {
    // alterando o zoom da câmera
    if (event.wheel.y < 0) {
        camera->ZoomOut();
    } else {
        camera->ZoomIn();
    }
}

void EventKeyUp(const SDL_Event& event) {
    // Atualizando o estado de todas as teclas
    std::shared_ptr<Key> keyTarget = GetKey(keyList, event.key.keysym.scancode);

    if (keyTarget != nullptr) {
        keyTarget->state.clickDown = false;
        keyTarget->state.clickUp = true;
        keyTarget->state.hold = false;
    }

    // Deselecionando formas/linhas
    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        lineSelected = nullptr;
        shapeSelected = nullptr;

        isElementSelected = false;
    }

    // deletando todas as formas
    if (event.key.keysym.scancode == SDL_SCANCODE_Q && GetKeyState(keyList, "LEFT_SHIFT").hold) {
        lineSelected = nullptr;
        shapeSelected = nullptr;

        lineList.fill(nullptr);
        shapeList.fill(nullptr);

        std::cout << "[Collision Simulator] All elements have been cleared." << "\n";
    }

    // ativando e desativando gravidade
    if (event.key.keysym.scancode == SDL_SCANCODE_G && GetKeyState(keyList, "LEFT_SHIFT").hold) {
        gravity = !gravity;
        
        if (gravity) {
            std::cout << "[Collision Simulator] You have toggled gravity to on."  << "\n";
        } else {
            std::cout << "[Collision Simulator] You have toggled gravity to off." << "\n";
        }
    }
}

void EventKeyDown(const SDL_Event& event) {
    // Atualizando o estado de todas as teclas
    std::shared_ptr<Key> keyTarget = GetKey(keyList, event.key.keysym.scancode);

    if (keyTarget != nullptr) {
        keyTarget->state.clickDown = true;
        keyTarget->state.clickUp = false;
        keyTarget->state.hold = true;
    }
}

// gerenciar todos os eventos
void HandleEvents(const SDL_Event& event) {
    switch (event.type) {
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEBUTTONDOWN:
            EventMouseClick(event);
            break;

        case SDL_KEYDOWN:
            EventKeyDown(event);
            break;

        case SDL_KEYUP:
            EventKeyUp(event);
            break;

        case SDL_MOUSEMOTION:
            EventMouseMove(event);
            break;

        case SDL_MOUSEWHEEL:
            EventMouseScrolling(event);
            break;
    }
}
