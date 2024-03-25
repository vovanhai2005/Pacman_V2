#include <Texture.h>

Texture::Texture()
{
    characterTexture = NULL;
    tileTexture = NULL;
    pacmanFrame = 0;
    memset(ghostFrame , 0 , sizeof ghostFrame);
}

Texture::~Texture()
{
    SDL_DestroyTexture(characterTexture);
    characterTexture = NULL;

    SDL_DestroyTexture(tileTexture);
    tileTexture = NULL; 

    pacmanFrame = 0;
    memset(ghostFrame , 0 , sizeof ghostFrame);
}

//Cut Texture to make Pacman Map
void Texture::loadImageToTileTexture()
{
    SDL_Surface* image = IMG_LOAD("assets/All Image/Pacman Tile Labyrinth.png");

    if (image == NULL){
        Console -> Status(IMG_GetError());
    }
    else 
    {
        tileTexture = SDL_CreateTextureFromSurface(renderer , image);
        
        int posX = 0 , posY = 0;
        for (int i = 0 ; i < 32 ; ++i){
            // tile[i] represents for a 17x17 pixel at position i of the original Pacman Tile Labyrinth
            tile[i] = {posX , posY , 17 , 17};
            posY += 17;
            if (i % 4 == 3){
                posX += 17;
                posY = 0;
            }
        }
    }

    SDL_FreeSurface(image);
    image = NULL;
}

void Texture::renderTileTexture(SDL_Renderer* &renderer , SDL_Surface* &tileTexture , int tilePos , SDL_Rect &dstRect)
{
    SDL_RenderCopy(renderer , tileTexture , &tile[tilePos] , dstRect);
}

// Cut Texture to make Pacman and Ghost

void Texture::loadCharacterTexture(SDL_Renderer* &renderer)
{
    SDL_Surface* image = IMG_Load("assets/All Image/Pacman and Ghost Texture.png")
    
    if (image == NULL){
        Console -> Status(IMG_GetError());
    }

    else {
        characterTexture = SDL_CreateTextureFromSurface(renderer , image);

        int posX = 0 , posY = 0;
        // Pacman_Status[i] represents a 31x31 pixel at position i of a pacman status
        // Pacman Up
        for (int i = 0 ; i < 3 ; ++i){
            PacmanUp[i % 3] = {posX , posY , 31 , 31};
            posX += 31;
        }
        // Pacman Down
        for (int i = 0 ; i < 3 ; ++i){
            PacmanDown[i % 3] = {posX , posY , 31 , 31};
            posX += 31;
        }
        // Pacman Left
        for (int i = 0 ; i < 3 ; ++i){
            PacmanLeft[i % 3] = {posX , posY , 31 , 31};
            posX += 31;
        }
        // Pacman Right
        for (int i = 0 ; i < 3 ; ++i){
            PacmanRight[i % 3] = {posX , posY , 31 , 31};
            posX += 31;
        }
        // Pacman Dead
        posX = 0;
        posY = 155;
        for (int i = 0 ; i < 11 ; ++i){
            PacmanDead[i] = {posX , posY , 31 , 31};
            posX += 31;
        }


        //Ghost
        posX = 0;
        posY = 31;
        for (int i = 0 ; i <= TOTAL_GHOST - 1 ; ++i){
            // Up Status
            ghost[i][UP][0] = {posX , posY , 31 , 31} , posX += 31;
            ghost[i][UP][1] = {posX , posY , 31 , 31} , posX += 31;
            // Down Status
            ghost[i][DOWN][0] = {posX , posY , 31 , 31} , posX += 31;
            ghost[i][DOWN][1] = {posX , posY , 31 , 31} , posX += 31;
            // Left Status
            ghost[i][LEFT][0] = {posX , posY , 31 , 31} , posX += 31;
            ghost[i][LEFT][1] = {posX , posY , 31 , 31} , posX += 31;
            // Right Status
            ghost[i][RIGHT][0] = {posX , posY , 31 , 31} , posX += 31;
            ghost[i][RIGHT][1] = {posX , posY , 31 , 31} , posX += 31;
            // Scared Status
            ghost[i][BLUE_SCARED][0] = {posX , 31 , 31 , 31} , posX += 31;
            ghost[i][BLUE_SCARED][1] = {posX , 31 , 31 , 31} , posX += 31;
            ghost[i][WHITE_SCARED][0] = {posX , 31 , 31 , 31} , posX += 31;
            ghost[i][WHITE_SCARED][1] = {posX , 31 , 31 , 31};

            // Reset position
            posX = 0;
            posY += 31;
            if (i == 3) posY += 31;
        }
        // Dead Status
        posX = 248 , posY = 62;
        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31};
        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31} , posX += 31;

        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31};
        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31} , posX = 248 , posY += 31;
        
        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31};
        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31} , posX += 31;

        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31};
        ghost[GHOST_DEAD][UP][0] = {posX , posY , 31 , 31};

        // Reset position
        posX = posY = 0;

        SDL_FreeSurface(image) 
        image = IMG_LOAD("assets/All Image/ghostscore.png")
        if (image != NULL) scoreTexture = SDL_CreateTextureFromSurface(renderer , image);
    }

    SDL_FreeSurface(image);
    image = NULL;
}

void Texture::renderPacmanTexture(SDL_Renderer* &renderer , int posX , int posY , int stat);
{
    pacmanFrame++;
    SDL_Rect srcRect , dsRect;
    dsRect = {posX + 210 , posY - 7 , 30 , 30};

    if (stat != PACMAN_DEAD && pacmanFrame / 10 > 2) pacmanFrame = 0;
    switch(stat){
        case -1:
            srcRect = PacmanUp[0];
            break;
        case UP: 
            srcRect = PacmanUp[pacmanFrame / 10];
            break;
        case DOWN:
            srcRect = PacmanDown[pacmanFrame / 10];
            break;
        case LEFT: 
            srcRect = PacmanLEFT[pacmanFrame / 10];
            break;
        case RIGHT: 
            srcRect = PacmanRight[pacmanFrame / 10];
            break;
    }

    SDL_RenderCopy(renderer , characterTexture , &srcRect , &dsRect);
}

void Texture::renderGhostTexture(SDL_Renderer* &renderer , int posX , int posY , int ghostType , int stat)
{
    ghostFrame[ghostType]++;
    SDL_Rect srcRect , dsRect;
    dsRect = {posX + 210 , posY - 7 , 30 , 30};

    if (ghostFrame[ghostType] / 7 > 1) ghostFrame[ghostType] = 0;

    switch(stat){
        case UP: 
            srcRect = ghost[ghostType][UP][ghostFrame[ghostType] / 7];
            break;
        case DOWN: 
            srcRect = ghost[ghostType][DOWN][ghostFrame[ghostType] / 7];
            break;
        case LEFT: 
            srcRect = ghost[ghostType][LEFT][ghostFrame[ghostType] / 7];
            break;
        case RIGHT: 
            srcRect = ghost[ghostType][RIGHT][ghostFrame[ghostType] / 7];
            break;
        case BLUE_SCARED: 
            srcRect = ghost[ghostType][BLUE_SCARED][ghostFrame[ghostType] / 7];
            break;    
        case FRIGHTEN_GHOST_2:
            srcRect = ghost[ghostID][((ghostFrame[ghostType] / 7 < 1) ? BLUE_SCARED : WHITE_SCARED][ghostFrame[ghostID] / 7];
            break;
    }

    SDL_RenderCopy(renderer , characterTexture , &srcRect , &dsRect);
}

void Texture::renderGhostScore(SDL_Renderer* &renderer , int posX , int posY , int ghostStreak)
{
    SDL_Rect srcRect , dsRect;

    switch(ghostStreak){
        case 0:
            srcRect = {0 , 0 , 50 , 50};
            break;
        case 1:
            srcRect = {50 , 0 , 50 , 50};
            break;
        case 2:
            srcRect = {0 , 50 , 50 , 50};
            break;
        case 3:
            srcRect = {50 , 50 , 50 , 50};
            break;
    }

    SDL_RenderCopy(renderer , scoreTexture , &srcRect , &dsRect);
}