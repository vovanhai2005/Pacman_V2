#pragma once

#ifndef _TEXTURESRC_H_
#define _TEXTURESRC_H_

#include <SDL.h>
#include <SDL_image.h>
#include "../Manage/LogStat.h"

class Texture {
    private:
        LogStatus* Console = new LogStatus("Texture");

        SDL_Texture* tileTexture;
        SDL_Rect tile[32];

        SDL_Texture* characterTexture;
        SDL_Texture* scoreTexture;
        SDL_Rect PacmanUp[3];
        SDL_Rect PacmanDown[3];
        SDL_Rect PacmanLeft[3];
        SDL_Rect PacmanRight[3];
        SDL_Rect PacmanDead[11];
        SDL_Rect ghost[7][6][2];

        int pacmanFrame;
        int ghostFrame[7];
    public:
        static const int UP = 0;
        static const int RIGHT = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;

        static const int WHITE_SCARED = 5;
        static const int BLUE_SCARED = 4;
        static const int PACMAN_DEAD = 5;

        static const int BLINKY = 0;
        static const int PINKY  = 1;
        static const int INKY   = 2;
        static const int CLYDE  = 3;
        static const int GREENDY = 4;
        static const int FRIENDY = 5;
        static const int GHOST_DEAD = 6;
        static const int TOTAL_GHOST = 7;

        Texture();

        ~Texture();

        bool pacmanIsDead();

        void loadImageToTileTexture(SDL_Renderer* &renderer);

        void renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect);

        void loadCharacterTexture(SDL_Renderer* &renderer);

        void renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int status);

        void renderGhostTexture(SDL_Renderer* &renderer, int posX, int posY, int ghostID, int status);

        void renderGhostScore(SDL_Renderer* &renderer, const int eatenGhostPosX, const int eantenGhostPosY, const int eatenGhostStreak);
};

#endif // _TEXTURESRC_H_
