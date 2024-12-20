/*
    Wrapper para manipulação de eventos
*/

#include "event-handler.hpp"

#include <iostream>

#include "global.hpp"
#include "app/app-global.hpp"

#include "core/geometric/basic.hpp"

// eventos separador por tipo

void EventMouseClick(SDL_Event event) {
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
    if (event.type == SDL_MOUSEBUTTONUP) {
        for (auto line : lineList) {
            if (distance(line->coord, Coord { mouseAbsoluteX, mouseAbsoluteY }) <= line->length / 2) {
                lineSelected = line;
                shapeSelected = nullptr;

                break;
            }
        }

        // Seleção de forma terá prioridade
        for (auto shape : shapeList) {
            if (distance(shape->coord, Coord { mouseAbsoluteX, mouseAbsoluteY }) <= shape->Size) {
                shapeSelected = shape;
                lineSelected = nullptr;

                break;
            }
        }
    }
}

void EventMouseMove(SDL_Event event) {
    // atualizando definições de mouse
    mouse.x = event.motion.x;
    mouse.y = event.motion.y;
}

void EventMouseScrolling(SDL_Event event) {
    // alterando o zoom da câmera
    if (event.wheel.y < 0) {
        camera->ZoomOut();
    } else {
        camera->ZoomIn();
    }
}

void EventKeyUp(SDL_Event event) {
    // Deselecionando formas/linhas
    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
        lineSelected = nullptr;
        shapeSelected = nullptr;
    }
}

void EventKeyDown(SDL_Event event) {

}

// gerenciar todos os eventos
void HandleEvents(SDL_Event event) {
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
