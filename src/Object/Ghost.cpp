#include "Ghost.h"
#include <random>
#include <iostream>

Ghost::Ghost(int tileX , int tileY , bool lock) : Object(tileX , tileY) {
    frighten = false;
    scattering = false;
    accelerate = 1;
    velocity = 2;
    nextTileX = tileX;
    nextTileY = tileY;
    this -> lock = lock;
    if (lock) ghostDir = UP;
    else ghostDir = RIGHT;
}


int Ghost::getNextTileX(){
    return nextTileX;
}

int Ghost::getNextTileY(){
    return nextTileY;
}

int Ghost::getGhostDir(){
    return ghostDir;
}

void Ghost::setDir(int dir){
    ghostDir = dir;
}

bool Ghost::Lock(){
    return lock;
}

bool Ghost::isFrighten(){
    return frighten;
}

bool Ghost::isScattering(){
    return scattering;
}

void Ghost::makeFrighten(bool stat){
    if (Lock()) return; 
    if (frighten != stat) getPosFromTile();
    frighten = stat;
    if (stat) {
        ghostDir = (ghostDir + 2) % 4;
        accelerate = 1;
    }
}

void Ghost::makeScattering(bool stat){
    scattering = stat;
}

void Ghost::moving(){
    int velX , velY , dir;
    velX = velY = 0;
    dir = -1;
    if (accelerate == 1){
        if (frighten) velocity = 1;
        else if (isDead()) velocity = 4;
        else velocity = 2;
    }
    else velocity = 4;

    switch(ghostDir){
        case UP: velY -= velocity; break;
        case DOWN: velY += velocity; break;
        case LEFT: velX -= velocity; break;
        case RIGHT: velX += velocity; break;
    }
    dir = ghostDir;
    changeDir(velX , velY , dir);
    move();
}

void Ghost::markDestination(int tileX , int tileY , int acce){
    this -> accelerate = acce;
    nextTileX = tileX;
    nextTileY = tileY;
}

void Ghost::ghostRespawn(const int tileX, const int tileY, const bool lock) {
    resetTile(tileX , tileY);
    this->lock = lock;
    if (lock == false) {
        if (rand() % 2 == 0) ghostDir = LEFT;
        else ghostDir = RIGHT;
    }
    else ghostDir = UP;
}