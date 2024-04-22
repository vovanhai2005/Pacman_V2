#pragma once

#ifndef _GAMEITEMMANAGE_H
#define _GAMEITEMMANAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include "../Object/Ghost.h"    

class GameItemManage {
    private:
        int life;
        int level;
        int score;
        int coinsEat;
        int ghostEat;
        bool newRecord = false;
        int ghostEatPosX , ghostEatPosY;
    protected:
        SDL_Texture* loadImage(SDL_Renderer* &renderer , std::string imagePath);
    public:
        const int smallCoin = 26;
        const int bigCoin = 27;
        int PINKY_COIN_OUT = 240;
        int INKY_COIN_OUT = 240;
        int CLYDE_COIN_OUT = 240;

        GameItemManage();

        ~GameItemManage();

        void resetGameItem();

        int getLife();

        void dead();

        int getGhostEatPosX();

        int getGhostEatPosY();

        void eatCoins(int coinType);

        bool coinClear();

        int ghostStreak();

        void eatGhost(int ghostAtTileX , int ghostAtTileY);

        int getLevel();

        void nextLevel();

        void ghostStart(Ghost* pinky , Ghost* inky , Ghost* clyde);
};
#endif 