// Variáveis globais do sistema

#pragma once

#include <memory>

#include "config/SDL2/graphics/Window.hpp"

#include "utils/system/keyboard.hpp"
#include "utils/system/mouse.hpp"

inline std::shared_ptr<Window> window;

// definições para input

inline KeyList keyList;
inline Mouse mouse = CreateMouseInput();
