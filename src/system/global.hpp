// Variáveis globais do sistema

#pragma once

#include <memory>

#include "config/SDL2/graphics/Window.hpp"

#include "utils/world/mouse.hpp"

inline std::shared_ptr<Window> window;

inline Mouse mouse = {
    0, 0, 0, 0,
    MouseInfo {false, 0, 0}, // right
    MouseInfo {false, 0, 0} // left
};
