#pragma once

#ifndef _TEXTMAMANGE_H
#define _TEXTMAMANGE_H

#include <SDL_ttf.h>
#include <string>
#include <iostream>

class TextManage{
    private:
        SDL_Rect dsRect;

        TTF_Font* font;
        SDL_Texture* textTexture;
        SDL_Surface* textSurface;

    public:
        const std::string FONT_NAME = "assets/Font/Sans-Bold.ttf";
        static const int CENTER = 0;
        static const int LEFT = 1;

        TextManage(int size);

        ~TextManage();

        void loadRenderText(SDL_Renderer* &renderer, std::string text, SDL_Color textColor);

        void renderText(SDL_Renderer* &renderer, int x, int y, const int type);
};
#endif