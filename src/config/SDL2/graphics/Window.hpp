/*
    Definições gerais de manipulação de janelas SDL2
*/

#pragma once

#include <memory>
#include <string>
#include <SDL2/SDL.h>

// config

constexpr short WINDOW_WIDTH = 800;
constexpr short WINDOW_HEIGHT = 600;

// definição geral de janela
class Window {
    public:
        SDL_Renderer* renderer;

        bool windowCreateFailure;
        
        Window(const std::string& name);
        ~Window();

        void Render(void); // renderiza os gráficos
        void Clear(void); // limpa a janela

        // dimensões da janela
        void GetDimensions(int& width, int& height);

    private:
        SDL_Window* window;
};

// criação dinâmica de janelas
std::shared_ptr<Window> CreateWindow(const std::string& name);
