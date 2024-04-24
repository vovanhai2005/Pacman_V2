#include "Ghost.h"
#include <random>
#include <iostream>

Ghost::Ghost(int tileX, int tileY, bool lock) : Object(tileX, tileY) {
    frighten = 0;
    accelerate = 1;
    velocity = 2;
    scattering = false;
    nextTileX = tileX, nextTileY = tileY;
    this->lock = lock;
    if (lock == false) ghostDir = RIGHT;
    else ghostDir = UP;
}

int Ghost::getNextTileX() {
    return nextTileX;
}

int Ghost::getNextTileY() {
    return nextTileY;
}

int Ghost::getGhostDir() {
    return ghostDir;
}

void Ghost::setDir(int dir) {
    ghostDir = dir;
}

void Ghost::makeFrighten(bool status) {
    if (Lock()) return; 
    if (frighten != status) getPosFromTile();
    frighten = status;
    if (status) {
        ghostDir = (ghostDir + 2) % 4;
        accelerate = 1;
    }
}

void Ghost::makeScattering(bool status) {
    scattering = status;
}

bool Ghost::isScattering() {
    return scattering;
}

bool Ghost::isFrighten() {
    return frighten;
}

void Ghost::markDestination(int tileX , int tileY , int accelerate) {
    this -> accelerate = accelerate;
    nextTileX = tileX;
    nextTileY = tileY;
}

void Ghost::moving() {
    int velX, velY, dir;
    velX = velY = 0; dir = -1;

    if (accelerate == 1) {
        if (frighten) velocity = 1;
        else if (isDead()) velocity = 4;
        else velocity = 2;
    }
    else velocity = 4;

    switch (ghostDir) {
        case UP:    velY -= velocity; dir = UP;    break;
        case DOWN:  velY += velocity; dir = DOWN;  break;
        case LEFT:  velX -= velocity; dir = LEFT;  break;
        case RIGHT: velX += velocity; dir = RIGHT; break;
    }
    changeDir(velX, velY, dir);
    move();
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

bool Ghost::Lock() {
    return lock;
}
