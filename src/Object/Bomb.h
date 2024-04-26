#pragma once

#ifndef _BOMB_H
#define _BOMB_H

#include <SDL.h>
#include <SDL_image.h>
// #include "Pacman.h"
#include "Ghost.h"
#include "../Map/Map.h"
#include "../Manage/GameItemManage.h"

class Bomb{
    private:
        SDL_Texture* bombTexture = nullptr;
        SDL_Texture* explodeRowTexture;
        SDL_Texture* explodeColTexture;
        SDL_Rect dsRect;
        Map* map;
        GameItemManage* itemManage;

        Ghost* ghost[4];
        int tileX, tileY;
        int posX, posY;
    public:
        Bomb(SDL_Renderer* &renderer, Ghost* &g0 , Ghost* &g1 , Ghost* &g2 , Ghost* &g3 , GameItemManage* &gameManage);

        ~Bomb();

        void makingEvent(SDL_Event &e);

        void setPosX(int x);

        void setPosY(int y);

        void renderBomb(SDL_Renderer* &renderer);
};
#endif