#include "GameItemManage.h"

GameItemManage::GameItemManage(){
    life = 3;
    level = 1;
    CoinsEat = 0;
    GhostEat = 0;
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

