/*
    Wrapper para manipulação de eventos
*/

#include "event-handler.hpp"

// eventos separador por tipo

void EventMouseClick(SDL_Event event) {
    // atualizando definições de mouse
    
}

void EventMouseMove(SDL_Event event) {
    // atualizando definições de mouse
    
}

void EventMouseScrolling(SDL_Event event) {
    // alterando o zoom da câmera
    
}

void EventKeyUp(SDL_Event event) {

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
