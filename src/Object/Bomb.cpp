#include "Bomb.h"

Bomb::Bomb(){
    bombTexture = nullptr;
}

Bomb::~Bomb(){
    SDL_DestroyTexture(bombTexture);
    bombTexture = nullptr;
}

void Bomb::renderBomb(SDL_Renderer* &renderer , int posX , int posY){
    SDL_Surface* image = IMG_Load("assets/All Image/bomb.png");
    if (image == nullptr){
        std::cout << "Bomb error!" << std::endl;
    }
    SDL_Texture* bombTexture = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
    dsRect = {posX , posY , 16 , 16};
    SDL_RenderCopy(renderer , bombTexture , NULL , &dsRect);
}