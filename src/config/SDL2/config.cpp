#include "config.hpp"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

bool SDL2_Initialize(void) {
    bool SDLInitSuccess = SDL_Init(SDL_INIT_VIDEO) == 0;
    bool SDLTTFInitSuccess = TTF_Init() == 0;

    if (!SDLInitSuccess || !SDLTTFInitSuccess) {
        std::cout << "Failed to init SDL subsystems." << "\n";
        return false;
    }

    return true;
}

void SDL2_Quit(void) {
    TTF_Quit();
    SDL_Quit();
}
