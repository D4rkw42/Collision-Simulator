/*
    Definições gerais de manipulação de janelas SDL2
*/

#include "Window.hpp"

// definição geral de janela
Window::Window(std::string name) {
    SDL_Window* _window = SDL_CreateWindow(
                                    name.c_str(),
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
                                );

    // window não criada
    this->windowCreateFailure = _window == nullptr;

    // atribuição
    this->window = _window; 
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    // configuração da janela
    SDL_SetWindowMinimumSize(this->window, WINDOW_WIDTH, WINDOW_HEIGHT);
}

Window::~Window() {
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
}

void Window::Render(void) {
    SDL_RenderPresent(this->renderer);
}

void Window::Clear(void) {
    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->renderer);
}

void Window::GetDimensions(int& width, int& height) {
    SDL_GetWindowSize(this->window, &width, &height);
}

//

std::shared_ptr<Window> CreateWindow(std::string name) {
    return std::make_shared<Window>(name);
}
