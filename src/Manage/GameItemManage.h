#pragma once

#ifndef _GAMEITEMMANAGE_H
#define _GAMEITEMMANAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include "../Object/Ghost.h"    

class GameItemManage {
    private:
        int level;
        int life;
        int eatenCoins;
        int eatenGhost;
        int scores;
        int pos = -1;
        std::string playername = "";
        int playerDecision;
        int currentBut;
        bool newRecord = false;
        int ghostEatenPosX;
        int ghostEatenPosY;

        int PINKY_COIN_LIMIT;
        int INKY_COIN_LIMIT;
        int CLYDE_COIN_LIMIT;

        TextManager *levelText;
        TextManager *liveText;
        TextManager *scoreText;
        TextManager *playerName;

        SDL_Texture *egBoard;
        SDL_Texture *hsBoard;
        Button *yesBut;
        Button *noBut;
        Mix_Chunk *navigationSound = Mix_LoadWAV("Source/Assets/Sound/button.wav");

    protected:
        SDL_Texture *loadImage(SDL_Renderer *&renderer, const std::string imagePath);

    public:
        const int TOTAL_COINS = 244;
        static const int normalCoin = 26;
        static const int superCoin = 27;
        static const int notCoin = 0;
        static const int pauseGame = 1;
        static const int AGAIN = 2;
        static const int QUIT = 3;
        static const int WAITING = 4;

        GameItemManage(SDL_Renderer* &renderer);

        ~GameItemManage();

        void resetGameItem();

        int getLife();

        void dead();

        int getGhostEatPosX();

        int getGhostEatPosY();

        void eatCoins(int coinType);

        int remainCoins();

        bool coinClear();

        int ghostStreak();

        void eatGhost(int ghostAtTileX , int ghostAtTileY);

        int getLevel();

        void nextLevel();

        void ghostStart(Ghost* &pinky , Ghost* &inky , Ghost* &clyde);
};
#endif 