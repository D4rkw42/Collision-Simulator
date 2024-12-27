// Variáveis globais do sistema

#pragma once

#include <memory>

#include "config/config.hpp"
#include "config/SDL2/graphics/Window.hpp"

#include "utils/system/keyboard.hpp"
#include "utils/system/mouse.hpp"

// Dados do sistema
inline int FPS = FRAME_RATE;

// Janela
inline std::shared_ptr<Window> window;

// definições para input

inline KeyList keyList;
inline Mouse mouse = CreateMouseInput();
