/*
    Wrapper para manipulação de eventos
*/

#pragma once

#include <SDL2/SDL.h>

// eventos separador por tipo

void EventMouseClick(const SDL_Event& event);
void EventMouseMove(const SDL_Event& event);
void EventMouseScrolling(const SDL_Event& event);

void EventKeyUp(const SDL_Event& event);
void EventKeyDown(const SDL_Event& event);

// gerenciar todos os eventos
void HandleEvents(const SDL_Event& event);
