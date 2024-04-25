#pragma once

#ifndef _BOMB_H
#define _BOMB_H

#include <SDL.h>
#include <SDL_image.h>
#include "Pacman.h"

class Bomb{
    private:
        SDL_Texture* bombTexture = nullptr;
        SDL_Rect dsRect;
        const int Row[4] = {0 , 0 , -1 , 1};
        const int Col[4] = {1 , -1 , 0 , 0};
        static const int time = 15;
    public:
        Bomb();

        ~Bomb();

        void makingEvent(SDL_Event &e);

        void renderBomb(SDL_Renderer* &renderer , int tileX , int tileY);
};
#endif