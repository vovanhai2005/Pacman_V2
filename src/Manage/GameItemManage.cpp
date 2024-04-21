#include "GameItemManage.h"
#include <iostream>

GameItemManage::GameItemManage(){
    life = 3;
    level = 1;
    coinsEat = 0;
    ghostEat = 0;
    score = 0;
}

GameItemManage::~GameItemManage(){
    
}

SDL_Texture* GameItemManage::loadImage(SDL_Renderer* &renderer , std::string imagePath){
    SDL_Surface* image = IMG_Load(imagePath.c_str());
    SDL_Texture* res = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
    return res;
} 

void GameItemManage::resetGameItem(){
    life = 3;
    level = 1;
    coinsEat = 0;
    ghostEat = 0;
    score = 0;
}

int GameItemManage::getLife(){
    return life;
}

void GameItemManage::dead(){
    life--;
}

int GameItemManage::getGhostEatPosX(){
    return ghostEatPosX;
}

int GameItemManage::getGhostEatPosY(){
    return ghostEatPosY;
}

void GameItemManage::eatCoins(int coinType){
    coinsEat++;
    if (coinType == smallCoin) score += 50;
    else if (coinType == bigCoin){
        ghostEat = 0;
        score += 150;
    }
    std::cout << score << std::endl;
}

bool GameItemManage::coinClear(){
    return (coinsEat == 244);
}

int GameItemManage::ghostStreak(){
    return ghostEat;
}

void GameItemManage::eatGhost(int ghostAtTileX , int ghostAtTileY){
    int streak = ghostStreak();
    if (streak == 1) score += 200;
    else if (streak == 2) score += 400;
    else if (streak == 3) score += 800;
    else if (streak == 4) score += 1600;

    ghostEatPosX = ghostAtTileX;
    ghostEatPosY = ghostAtTileY;
}

int GameItemManage::getLevel(){
    return level;
}

void GameItemManage::nextLevel(){
    ++level;
    coinsEat = 0;
    ghostEat = 0;
    if (level >= 2 && level <= 4){
        PINKY_COIN_OUT = 0;
        INKY_COIN_OUT = 15;
        CLYDE_COIN_OUT = 35;
    }
    else {
        PINKY_COIN_OUT = 0;
        INKY_COIN_OUT = 0;
        CLYDE_COIN_OUT = 20;
    }
}

void GameItemManage::ghostStart(Ghost* pinky , Ghost* inky , Ghost* clyde){
    if (pinky -> Lock() && coinsEat >= PINKY_COIN_OUT) pinky -> ghostRespawn(Ghost::GHOST_COMMON_TILE_X , Ghost::GHOST_COMMON_TILE_Y , false);
    if (inky -> Lock() && coinsEat >= INKY_COIN_OUT) inky -> ghostRespawn(Ghost::GHOST_COMMON_TILE_X , Ghost::GHOST_COMMON_TILE_Y , false);
    if (clyde -> Lock() && coinsEat >= CLYDE_COIN_OUT) clyde -> ghostRespawn(Ghost::GHOST_COMMON_TILE_X , Ghost::GHOST_COMMON_TILE_Y , false);
}