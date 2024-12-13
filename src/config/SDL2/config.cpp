#include "config.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool SDL2_Initialize(void) {
    bool SDLInitSuccess = SDL_Init(SDL_INIT_VIDEO);
    bool SDLImageInitSuccess = IMG_Init(IMG_INIT_PNG);

    if (SDLInitSuccess || !SDLImageInitSuccess) {
        return false;
    }

    return true;
}

void SDL2_Quit(void) {
    IMG_Quit();
    SDL_Quit();
}
