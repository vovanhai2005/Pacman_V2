#include "Item.h"

Item::Item(SDL_Renderer* &renderer , const std::string imgPath){
    tileX = 0;
    tileY = 0;
    dead = true;
    SDL_Surface* image = IMG_Load(imgPath.c_str());
    itemTexture = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
}

Item::~Item(){
    SDL_DestroyTexture(itemTexture);
    itemTexture = NULL;
}

int Item::getPosX(){
    return tileX;
}

int Item::getPosY(){
    return tileY;
}

bool Item::isDestroyed(){
    return dead;
}

void Item::spawnAt(int tileX , int tileY){
    this -> tileX = tileX;
    this -> tileY = tileY;
    dead = false;
}

void Item::destroyItem(){
    dead = true;
}

void Item::renderItem(SDL_Renderer *renderer){
    SDL_Rect dsRect = {tileX * 16 - 7 + 210 , tileY * 16 - 7 , 30 , 30};
    SDL_RenderCopy(renderer , itemTexture , NULL , &dsRect);
}

