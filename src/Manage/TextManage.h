#pragma once

#ifndef _TEXTMAMANGE_H
#define _TEXTMAMANGE_H

#include <SDL_ttf.h>
#include <string>

class TextManage{
    private:
        SDL_Rect dsRect;

        TTF_Font* font;
        SDL_Texture* textTexture;
        SDL_Surface* textSurface;

    public:
        TextManage();

        ~TextManage();
}