#include "Texture.h"

Texture::Texture() {
    tileTexture = nullptr;
    characterTexture = nullptr;
    scoreTexture = nullptr;
    pacmanFrame = 0;
    for (int i = 0; i < 7; ++i) ghostFrame[i] = 0;
}

Texture::~Texture() {
    SDL_DestroyTexture(tileTexture);
    tileTexture = nullptr;

    SDL_DestroyTexture(characterTexture);
    characterTexture = nullptr;

    SDL_DestroyTexture(scoreTexture);
    scoreTexture = nullptr;

    for (int i = 0; i < 7; ++i) ghostFrame[i] = 0;
}

bool Texture::pacmanIsDead() {
    if (pacmanFrame == 109) {
        pacmanFrame = 0; return true;
    }
    return false;
}

void Texture::loadImageToTileTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("assets/All Image/Pacman Tile Labyrinth.png");

    if (Image == nullptr) {
        Console->Status( IMG_GetError() );
    }
    else {
        tileTexture = SDL_CreateTextureFromSurface(renderer, Image);

        int x = 0, y = 0;
        for (int i = 0; i < 32; ++i) {
            tile[i] = {x, y, 16, 16};
            y += 17;
            if (i % 4 == 3) x += 17, y = 0;
        }

        Console->Status("Tile Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void Texture::renderTileTexture(SDL_Renderer* &renderer, int tileID, SDL_Rect* dsRect) {
    SDL_RenderCopy(renderer, tileTexture, &tile[ tileID ], dsRect);
}

void Texture::loadCharacterTexture(SDL_Renderer* &renderer) {
    SDL_Surface* Image = IMG_Load("assets/All Image/Pacman and Ghost Texture.png");

    if (Image == nullptr) {
        Console->Status( IMG_GetError() );
    }
    else {
        characterTexture = SDL_CreateTextureFromSurface(renderer, Image);

        int posTexX = 0, posTexY = 0;

        /// Pacman goes up
        for (int i = 0; i < 3; ++i)  PacmanUp[i] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman goes down
        for (int i = 3; i < 6; ++i)  PacmanDown[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman goes left
        for (int i = 6; i < 9; ++i)  PacmanLeft[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman goes right
        for (int i = 9; i < 12; ++i) PacmanRight[i % 3] = {posTexX, posTexY, 30, 30}, posTexX += 31;
        /// Pacman dead
        posTexX = 0;
        for (int i = 0; i < 11; ++i) PacmanDead[i] = {posTexX, 155, 30, 30}, posTexX += 31;

        Console->Status("Pacman Texture got successfully!");

        /// Ghost setup
        posTexX = 0; posTexY = 31;
        for (int i = 0; i < TOTAL_GHOST - 1; ++i) {
            ghost[i][UP   ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][UP   ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][DOWN ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][DOWN ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][LEFT ][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][LEFT ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][RIGHT][0] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][RIGHT][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
            ghost[i][BLUE_SCARED][0] = {posTexX, 31, 30, 30}; posTexX += 31;
            ghost[i][BLUE_SCARED][1] = {posTexX, 31, 30, 30}; posTexX += 31;
            ghost[i][WHITE_SCARED][0] = {posTexX, 31, 30, 30}; posTexX += 31;
            ghost[i][WHITE_SCARED][1] = {posTexX, 31, 30, 30}; posTexX = 0;
            posTexY += 31;
            if (i == 3) posTexY += 31;
        }
        posTexX = 248; posTexY = 62;
        ghost[GHOST_DEAD][UP   ][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_DEAD][UP   ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
        ghost[GHOST_DEAD][DOWN ][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_DEAD][DOWN ][1] = {posTexX, posTexY, 30, 30}; posTexX = 248; posTexY += 31;
        ghost[GHOST_DEAD][LEFT ][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_DEAD][LEFT ][1] = {posTexX, posTexY, 30, 30}; posTexX += 31;
        ghost[GHOST_DEAD][RIGHT][0] = {posTexX, posTexY, 30, 30};
        ghost[GHOST_DEAD][RIGHT][1] = {posTexX, posTexY, 30, 30}; posTexX = posTexY = 0;

        SDL_FreeSurface(Image);
        Image = IMG_Load("Source/Assets/Entity Image/scoreTexture.png");
        scoreTexture = SDL_CreateTextureFromSurface(renderer, Image);

        Console->Status("Ghost Texture got successfully!");
    }

    SDL_FreeSurface(Image);
    Image = nullptr;
}

void Texture::renderPacmanTexture(SDL_Renderer* &renderer, int posX, int posY, int status) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7 + 217, posY - 7, 30, 30};
    ++pacmanFrame;

    if (status != PACMAN_DEAD && pacmanFrame == 30) pacmanFrame = 0;

    switch (status) {
        case -1: srcRect = PacmanUp[0]; break;
        case UP:    srcRect = PacmanUp   [ pacmanFrame / 10 ]; break;
        case RIGHT: srcRect = PacmanRight[ pacmanFrame / 10 ]; break;
        case DOWN:  srcRect = PacmanDown [ pacmanFrame / 10 ]; break;
        case LEFT:  srcRect = PacmanLeft [ pacmanFrame / 10 ]; break;
        case PACMAN_DEAD: srcRect = PacmanDead[pacmanFrame / 10]; break;
    }

    SDL_RenderCopy(renderer, characterTexture, &srcRect, &dsRect);
}

void Texture::renderGhostTexture(SDL_Renderer* &renderer, int posX, int posY, int ghostID, int status) {
    SDL_Rect srcRect, dsRect;
    dsRect = {posX - 7 + 217, posY - 7, 30, 30};
    ++ghostFrame[ghostID];

    if (ghostFrame[ghostID] == 14) ghostFrame[ghostID] = 0;

    switch (status) {
        case UP:    srcRect = ghost[ ghostID ][UP   ][ ghostFrame[ghostID] / 7 ]; break;
        case RIGHT: srcRect = ghost[ ghostID ][RIGHT][ ghostFrame[ghostID] / 7 ]; break;
        case DOWN:  srcRect = ghost[ ghostID ][DOWN ][ ghostFrame[ghostID] / 7 ]; break;
        case LEFT:  srcRect = ghost[ ghostID ][LEFT ][ ghostFrame[ghostID] / 7 ]; break;
        case BLUE_SCARED: srcRect = ghost[ghostID][BLUE_SCARED][ghostFrame[ghostID] / 7]; break;
        case WHITE_SCARED:
            if (ghostFrame[ghostID] / 7 == 0) srcRect = ghost[ghostID][BLUE_SCARED][ghostFrame[ghostID] / 7];
            else srcRect = ghost[ghostID][WHITE_SCARED][ghostFrame[ghostID] / 7];
            break;
    }

    SDL_RenderCopy(renderer, characterTexture, &srcRect, &dsRect);
}

void Texture::renderGhostScore(SDL_Renderer* &renderer, int eatenGhostPosX, int eatenGhostPosY, int eatenGhostStreak) {
    SDL_Rect srcRect, dsRect;
    switch (eatenGhostStreak) {
        case 0: srcRect = { 0,  0, 50, 50}; break;
        case 1: srcRect = {50,  0, 50, 50}; break;
        case 2: srcRect = { 0, 50, 50, 50}; break;
        case 3: srcRect = {50, 50, 50, 50}; break;
    }
    dsRect = {eatenGhostPosX + 210, eatenGhostPosY - 7, 30, 30};
    SDL_RenderCopy(renderer, scoreTexture, &srcRect, &dsRect);
}
