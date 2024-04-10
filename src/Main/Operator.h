#pragma once

#ifndef _OPERATOR_H
#define _OPERATOR_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include "../Map/Map.h"
#include "../Object/Pacman.h"
#include "../Object/Ghost.h"
#include "../Object/Item.h"
#include "../Object/Texture.h"

class Operator {
    private:
        Map* map;
        Pacman* pacman;
        Ghost* blinky;
        Ghost* pinky;
        Ghost* inky;
        Ghost* clyde;
        Item* apple;
        Texture* objectTexture;
        SDL_Texture* nextLevel;
        SDL_Texture* ready;


    public:
        Operator();

        ~Operator() {
            delete map;
            map = NULL;
            delete pacman;
            pacman = NULL;
            delete blinky;
            blinky = NULL;
            delete pinky;
            pinky = NULL;
            delete inky;
            inky = NULL;
            delete clyde;
            clyde = NULL;
            delete apple;
            apple = NULL;
            SDL_DestroyTexture(nextLevel);
            nextLevel = NULL;
            SDL_DestroyTexture(ready);
            ready = NULL;
            delete objectTexture;
            objectTexture = NULL;
        }

        void init(SDL_Renderer* &renderer);

        void newGame();
        
};
#endif