// definições gerais para renderização de texto

#include "text.hpp"

#include <iostream>

Text::Text(const std::string &content, int size, const TextColor &color, unsigned style, const std::string &fontName) {
    SDL_Color textColor;

    textColor.r = color.r;
    textColor.g = color.g;
    textColor.b = color.b;
    textColor.a = color.a * 255;

    this->font = Text::FindTTFFont(fontName, size);
    TTF_SetFontStyle(this->font, style);
    
    this->textSurface = TTF_RenderText_Solid(this->font, content.c_str(), textColor);
}

Text::~Text() {
    SDL_FreeSurface(this->textSurface);
    TTF_CloseFont(this->font);
}

void Text::Render(const std::shared_ptr<Window>& window, int x, int y) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->renderer, this->textSurface);

    SDL_Rect rect;

    rect.w = this->textSurface->w;
    rect.h = this->textSurface->h;

    rect.x = x - rect.w / 2;
    rect.y = y - rect.h / 2;

    SDL_RenderCopy(window->renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
}

TTF_Font *Text::FindTTFFont(const std::string &name, int size) {
    std::string ttfFileName = FONT_DIRECTORY + name + std::string(".ttf");
    TTF_Font* font = TTF_OpenFont(ttfFileName.c_str(), size);

    return font;
}
