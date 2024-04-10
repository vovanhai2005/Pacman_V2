#pragma once

#ifndef _ITEM_H
#define _ITEM_h

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Item{
    private:
        int tileX;
        int tileY;
        bool dead = 0;
        SDL_Texture *itemTexture = NULL;
    public:
        Item(SDL_Renderer* &renderer , const std::string imgPath);

        ~Item();

        int getPosX();

        int getPosY();

        bool isDestroyed();

        void spawnAt(int tileX , int tileY);

        void destroyItem();

        void renderItem(SDL_Renderer *renderer);
        
};
#endif