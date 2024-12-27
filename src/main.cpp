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

unsigned long CurrEpoch = 0;
unsigned long LastEpoch = EpochTime;

int FrameRateCount = 0;
int FPSCountTime = 0;
int FPSCount = 0;

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
        CurrEpoch = EpochTime;
        int deltatime = CurrEpoch - LastEpoch;

        LastEpoch = CurrEpoch;

        // renderização e atualização
        SDL_PollEvent(&Event);
        HandleEvents(Event);

        ApplicationUpdate(deltatime);

        FrameRateCount += deltatime;

        if (FrameRateCount >= 1000 / FRAME_RATE) {
            FrameRateCount = 0;
            FPSCount++;

            ApplicationRender(deltatime);
        }

        // contagem de fps

        FPSCountTime += deltatime;

        if (FPSCountTime >= 1000) {
            FPSCountTime = 0;
            FPS = FPSCount;
            FPSCount = 0;
        }

        // For convinience
        SDL_Delay(1);
    }

    // Quit
    ApplicationQuit();
    SDL2_Quit();

    return EXIT_SUCCESS;
}
