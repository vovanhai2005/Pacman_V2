#pragma once

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>
#include <SDL_image.h>
#include <../Manage/LogStat.h>

class Texture 
{
    public: 

        const int PIXELS = 31;
        // PACMAN
        const static int UP = 0;
        const static int DOWN = 1;
        const static int LEFT = 2;
        const static int RIGHT = 3;
        const static int PACMAN_DEAD = 4;

        const static int BLUE_SCARED = 4;
        const static int WHITE_SCARED = 5;
        const static int TOTAL_GHOST = 6;

        const static BLINKY = 0;
        const static PINKY = 1;
        const static INKY = 2;
        const static CLYDE = 3;
        const static GREENDY = 4;
        const static FRIENDY = 5; 
        const static GHOST_DEAD = 6;

        Texture();

        ~Texture();

        void loadImageToTileTexture(SDL_Renderer* &renderer);

        void loadTileTexture(SDL_Renderer* &renderer , SDL_Surface* &tileTexture , int tilePos , SDL_Rect &dstrect);

        void loadCharacterTexture(SDL_Renderer* &renderer);

        void renderPacmanTexture(SDL_Renderer* &renderer , int posX , int posY , int stat);

        void renderGhostTexture(SDL_Renderer* &renderer , int posX , int posY , int ghostType , int stat);
        
        void renderGhostScore(SDL_Renderer* &renderer , int posX , int posY , int ghostStreak);
    private:
        const string FILE_NAME = "Texture";
        LogStat* Console = new LogStat(FILE_NAME);

        //Texture
        SDL_Texture* tileTexture = NULL;
        SDL_Texture* characterTexture = NULL;
        SDL_Texture* scoreTexture = NULL;

        //Tile to make Map
        SDL_Rect tilePixel[PIXELS + 1];

        //Pacman pixels
        SDL_Rect PacmanUp[4];
        SDL_Rect PacmanDown[4];
        SDL_Rect PacmanLeft[4];
        SDL_Rect PacmanRight[4];
        SDL_Rect PacmanDead[11];
        
        int pacmanFrame = 0;
        int ghostFrame[7];

}