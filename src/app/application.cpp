#include "application.hpp"

#include <iostream>

#include "global.hpp"
#include "config/config.hpp"

#include "config/SDL2/graphics/Window.hpp"
#include "core/geometric/Line.hpp"

Line line1 = Line(Coord { 100, 100 }, 0, 0, 100, PI/2);
Line line2 = Line(Coord { 150, 100 }, 0, 0, 100, PI/2);

void ApplicationInitialize(void) {
    window = CreateWindow(PROJECT_NAME);
}

void ApplicationQuit(void) {

}

//

void ApplicationUpdate(int deltatime) {
    line1.Update(deltatime);
    line2.Update(deltatime);

    line1.color = RGBA_RED;
    line2.color = RGBA_RED;

    if (Line::LineCollision(line1, line2)) {
        line1.color = RGBA_GREEN;
        line2.color = RGBA_GREEN;
    }
}

void ApplicationRender(int deltatime) {
    // Limpeza de Janela
    window->Clear();

    // Render
    line1.Render(window);
    line2.Render(window);

    // Renderiza os gráficos
    window->Render();
}
