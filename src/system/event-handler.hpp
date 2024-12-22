/*
    Wrapper para manipulação de eventos
*/

#pragma once

#include <SDL2/SDL.h>

// eventos separador por tipo

void EventMouseClick(SDL_Event event);
void EventMouseMove(SDL_Event event);
void EventMouseScrolling(SDL_Event event);

void EventKeyUp(SDL_Event event);
void EventKeyDown(SDL_Event event);

// gerenciar todos os eventos
void HandleEvents(SDL_Event event);
