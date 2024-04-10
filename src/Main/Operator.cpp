#include "Operator.h"
#include <limits>
#include <random>
#include <time.h>

using namespace std;

Operator::Operator(){
    map = NULL;
    pacman = NULL;
    blinky = NULL;
    pinky = NULL;
    inky = NULL;
    clyde = NULL;
    apple = NULL;
    objectTexture = NULL;
}

void Operator::init(SDL_Renderer* &renderer){
    /// initialize map
    // map = new Map();
    // objectTexture = new Texture();
    // objectTexture->loadImageToTileTexture(renderer);
    // objectTexture->loadCharacterTexture(renderer);
    
}



