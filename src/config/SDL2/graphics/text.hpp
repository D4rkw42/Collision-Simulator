// definições gerais para renderização de texto

#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "config/SDL2/graphics/Window.hpp"

const std::string FONT_DIRECTORY = "assets/fonts/";

//

struct TextColor {
    int r, g, b;
    double a;
};

// colors
const TextColor TEXT_WHITE = TextColor { 255, 255, 255, 1.f };

// styles
#define TEXT_NORMAL TTF_STYLE_NORMAL // normal
#define TEXT_BOLD TTF_STYLE_BOLD // bold
#define TEXT_ITALIC TTF_STYLE_ITALIC // italic

//

class Text {
    public:
        TTF_Font* font;
        SDL_Surface* textSurface;

        Text(const std::string& content, int size, const TextColor& color, unsigned style, const std::string& fontName);
        ~Text();

        void Render(const std::shared_ptr<Window>& window, int x, int y);

        // utility
        static TTF_Font* FindTTFFont(const std::string& name, int size);

};

inline Text CreateText(const std::string& content, int size, const TextColor& color, unsigned style, const std::string& fontName) {
    return Text(content, size, color, style, fontName);
}
