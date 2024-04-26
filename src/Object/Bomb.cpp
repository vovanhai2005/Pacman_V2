#include "Bomb.h"

Bomb::Bomb(SDL_Renderer* &renderer , Ghost* &g0 , Ghost* &g1 , Ghost* &g2 , Ghost* &g3 , GameItemManage* &gameManage){
    map = new Map();
    bombTexture = nullptr;
    SDL_Surface* image = IMG_Load("assets/All Image/bomb.png");
    bombTexture = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
    
    image = IMG_Load("assets/All Image/bom_no_ngang.png");
    explodeRowTexture = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);

    image = IMG_Load("assets/All Image/bom_no_doc.png");
    explodeColTexture = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
    
    ghost[0] = g0;
    ghost[1] = g1;
    ghost[2] = g2;
    ghost[3] = g3;
    itemManage = gameManage;

    bombSound = Mix_LoadWAV("assets/Sound/Bomb_Exploding-Sound_Explorer-68256487.wav");
}

Bomb::~Bomb(){
    SDL_DestroyTexture(bombTexture);
    bombTexture = nullptr;
}

void Bomb::setPosX(int x)
{
    posX = x;
    tileX = posX/16;
}


void Bomb::setPosY(int y)
{
    posY = y;
    tileY = posY/16;
}

void Bomb::renderBomb(SDL_Renderer* &renderer){
    dsRect = {posX + 210 , posY - 7 , 32 , 32};
    SDL_RenderCopy(renderer , bombTexture , NULL , &dsRect);

      //row
    int x = tileX;
    while(x >= 0) // left
    {
        if (map -> getID(x, tileY) == 26 || map -> getID(x, tileY) == 27 || map -> getID(x, tileY) == 30)
        {
            dsRect = {x * 16 + 217, tileY * 16, 16, 16};
            SDL_RenderCopy(renderer, explodeRowTexture , NULL , &dsRect);
            for (int i = 0 ; i < 4 ; ++i){
                int ghostTileX = ghost[i] -> getTileX() , ghostTileY = ghost[i] -> getTileY();
                if (ghostTileX == x && ghostTileY == tileY && !ghost[i] -> isDead()){
                    ghost[i] -> ghostRespawn(Ghost::GHOST_START_TILE_X , Ghost::GHOST_START_TILE_Y , false);
                    itemManage -> eatGhost(ghostTileX , ghostTileY);
                }
            }
            x--;
        }
        else break;
    }

    x = tileX;
    while(x <= 27) // right
    {
        if (map -> getID(x, tileY) == 26 || map -> getID(x, tileY) == 27 || map -> getID(x, tileY) == 30)
        {
            dsRect = {x * 16 + 217, tileY * 16, 16, 16};
            SDL_RenderCopy(renderer, explodeRowTexture , NULL , &dsRect);
            for (int i = 0 ; i < 4 ; ++i){
                int ghostTileX = ghost[i] -> getTileX() , ghostTileY = ghost[i] -> getTileY();
                if (ghostTileX == x && ghostTileY == tileY && !ghost[i] -> isDead()){
                    ghost[i] -> ghostRespawn(Ghost::GHOST_START_TILE_X , Ghost::GHOST_START_TILE_Y , false);
                    itemManage -> eatGhost(ghostTileX , ghostTileY);
                }
            }
            x++;
        }
        else break;
    }

    int y = tileY;
    while(y >= 0) // up
    {
        if (map -> getID(tileX, y) == 26 || map -> getID(tileX, y) == 27 || map -> getID(tileX, y) == 30)
        {
            dsRect = {tileX * 16 + 217, y * 16, 16, 16};
            SDL_RenderCopy(renderer, explodeColTexture , NULL , &dsRect);
            for (int i = 0 ; i < 4 ; ++i){
                int ghostTileX = ghost[i] -> getTileX() , ghostTileY = ghost[i] -> getTileY();
                if (ghostTileX == tileX && ghostTileY == y && !ghost[i] -> isDead()){
                    ghost[i] -> ghostRespawn(Ghost::GHOST_START_TILE_X , Ghost::GHOST_START_TILE_Y , false);
                    itemManage -> eatGhost(ghostTileX , ghostTileY);
                }
            }
            y--;
        }
        else break;
    }

    y = tileY;
    while(y <= 30) // down
    {
        if (map -> getID(tileX, y) == 26 || map -> getID(tileX, y) == 27 || map -> getID(tileX, y) == 30)
        {
            dsRect = {tileX * 16 + 217, y * 16, 16, 16};
            SDL_RenderCopy(renderer, explodeColTexture , NULL , &dsRect);
            for (int i = 0 ; i < 4 ; ++i){
                int ghostTileX = ghost[i] -> getTileX() , ghostTileY = ghost[i] -> getTileY();
                if (ghostTileX == tileX && ghostTileY == y && !ghost[i] -> isDead()){
                    ghost[i] -> ghostRespawn(Ghost::GHOST_START_TILE_X , Ghost::GHOST_START_TILE_Y , false);
                itemManage -> eatGhost(ghostTileX , ghostTileY);
                }
            }
            y++;
        }
        else break;
    }
}