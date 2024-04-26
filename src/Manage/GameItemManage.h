#pragma once

#ifndef _GAMEITEMMANAGE_H
#define _GAMEITEMMANAGE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include "../Object/Ghost.h"
#include "TextManage.h"
#include "Button.h"

class GameItemManage {
    private:
        int level;
        int life;
        int coinsEat;
        int ghostEat;
        int score;
        int pos = -1;
        std::string player = "";
        int playerDecision;
        int currentBut;
        bool newRecord = false;
        int ghostEatPosX;
        int ghostEatPosY;

        int PINKY_COIN_OUT;
        int INKY_COIN_OUT;
        int CLYDE_COIN_OUT;

        TextManage *levelText;
        TextManage *livesText;
        TextManage *scoreText;

        TextManage *playerName;

        SDL_Texture *egBoard;
        SDL_Texture *hsBoard;
        Button *yesButton;
        Button *noButton;
        Mix_Chunk *navigationSound = Mix_LoadWAV("Source/Assets/Sound/button.wav");

    protected:
        SDL_Texture *loadImage(SDL_Renderer *&renderer, const std::string imagePath);

    public:
        const int TOTAL_COINS = 244;
        static const int smallCoin = 26;
        static const int bigCoin = 27;
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

        bool coinClear();

        int ghostStreak();

        void eatGhost(int ghostAtTileX , int ghostAtTileY);

        int getLevel();

        void nextLevel();

        void ghostStart(Ghost* &pinky , Ghost* &inky , Ghost* &clyde);

        int remainCoins();

        void renderInfoInGame(SDL_Renderer* &renderer);

        void handleEGBoard(SDL_Event &e);

        void runEGBoard(SDL_Renderer* &renderer);

        void checkScoreData(const std::vector<std::string> &scoreData);

        int getPlayerDecision();
};
#endif 