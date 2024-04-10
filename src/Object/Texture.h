#pragma once

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "SDL.h"
#include "SDL_image.h"
#include "../Manage/LogStat.h"

class Texture 
{
    public: 

        const int PIXELS = 31;
        // PACMAN
        const static int UP = 0;
        const static int DOWN = 1;
        const static int LEFT = 2;
        const static int RIGHT = 3;
        const static int PACMAN_DEAD = 5;
        //GHOST
        const static int BLUE_SCARED = 4;
        const static int WHITE_SCARED = 5;
        const static int TOTAL_GHOST = 6;

        const static int BLINKY = 0;
        const static int PINKY = 1;
        const static int INKY = 2;
        const static int CLYDE = 3;
        const static int GREENDY = 4;
        const static int FRIENDY = 5; 
        const static int GHOST_DEAD = 6;

        Texture();

        ~Texture(); 

        void loadImageToTileTexture(SDL_Renderer* &renderer);

        void renderTileTexture(SDL_Renderer* &renderer , int tilePos , SDL_Rect* dstrect);

        void loadCharacterTexture(SDL_Renderer* &renderer);

        void renderPacmanTexture(SDL_Renderer* &renderer , int posX , int posY , int stat);

        void renderGhostTexture(SDL_Renderer* &renderer , int posX , int posY , int ghostType , int stat);
        
        void renderGhostScore(SDL_Renderer* &renderer , int posX , int posY , int ghostStreak);
    private:
        const std::string FILE_NAME = "Texture";
        LogStatus* Console = new LogStatus(FILE_NAME);

        //Texture
        SDL_Texture* tileTexture = NULL;
        SDL_Texture* characterTexture = NULL;
        SDL_Texture* scoreTexture = NULL;

        //Tile to make Map
        SDL_Rect tile[32];

        //Pacman pixels
        SDL_Rect PacmanUp[4];
        SDL_Rect PacmanDown[4];
        SDL_Rect PacmanLeft[4];
        SDL_Rect PacmanRight[4];
        SDL_Rect PacmanDead[11];

        SDL_Rect ghost[6][5][2];
        
        int pacmanFrame = 0;
        int ghostFrame[7];

};
#endif