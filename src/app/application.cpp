#include "application.hpp"

#include <iostream>

#include "global.hpp"
#include "config/config.hpp"

#include "config/SDL2/graphics/Window.hpp"
#include "core/geometric/Shape.hpp"

auto shape = CreateShape(20, 200, Coord { 200, 200 }, 0, 0.05f, 0, 0.005f);

void ApplicationInitialize(void) {
    window = CreateWindow(PROJECT_NAME);
}

void ApplicationQuit(void) {

}

//

void ApplicationUpdate(int deltatime) {
    shape->Update(deltatime);
}

void ApplicationRender(int deltatime) {
    // Limpeza de Janela
    window->Clear();

    // Render
    shape->Render(window);

    // Renderiza os gráficos
    window->Render();
}
