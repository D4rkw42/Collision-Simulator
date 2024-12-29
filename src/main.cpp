#include <iostream>
#include <cstdlib>
#include <chrono>

#include <SDL2/SDL.h>

#include "system/global.hpp"
#include "config/config.hpp"

#include "app/application.hpp"
#include "system/event-handler.hpp"

#define SDL_MAIN_HANDLED

using namespace std::chrono;

// pre-definitions
#define EpochTime duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

SDL_Event Event;

unsigned long LastEpoch = EpochTime;

int main(int argc, char* argv[]) {
    // Initialização
    bool SDL2InitSuccess = SDL2_Initialize();

    if (!SDL2InitSuccess) {
        return EXIT_FAILURE;
    }

    ApplicationInitialize();

    // App
    while (!SDL_QuitRequested()) {
        // definição do tempo decorrido
        static double deltatimeMilliseconds = 0;
        int currEpoch = EpochTime;

        deltatimeMilliseconds += currEpoch - LastEpoch;
        LastEpoch = currEpoch;

        SDL_PollEvent(&Event);
        HandleEvents(Event);

        if (deltatimeMilliseconds >= 1000.f / FRAME_RATE) {
            double deltatimeSeconds = deltatimeMilliseconds / 1000;

            ApplicationUpdate(deltatimeMilliseconds);
            ApplicationRender();

            deltatimeMilliseconds = 0;
        }
        
        // For convinience
        SDL_Delay(1);
    }

    // Quit
    ApplicationQuit();
    SDL2_Quit();

    return EXIT_SUCCESS;
}
