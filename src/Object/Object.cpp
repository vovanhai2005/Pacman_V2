#include "Object.h"

Object::Object(int tileX , int tileY , int velX , int velY)
{
    this -> tileX = tileX;
    this -> tileY = tileY;

    this -> velX = (velX) ? velX : 0;
    this -> velY = (velY) ? velY : 0;
    
    this -> srcPosX = tileX * 16 + 8;
    this -> srcPosY = tileY * 16;
    srcPosY = 0;
    dead = false;
}

int Object::getPosX(){
    return srcPosX;
}

int Object::getPosY(){
    return srcPosY;
}

int Object::getTileX(){
    return tileX;
}

int Object::getTileY(){
    return tileY;
}

void Object::getPosFromTile(){
    srcPosX = tileX * 16;
    srcPosX = tileX * 16;
}

void Object::resetTile(const int tileX , const int tileY){
    this -> tileX = tileX;
    this -> tileY = tileY;
    velX = 0;
    velY = 0;
    dead = false;
    srcPosX = tileX * 16;
    srcPosY = tileY * 16;
}

void Object::move(){
    srcPosX += velX;
    srcPosY += velY;

    tileX = srcPosX / 16 + !(srcPosX % 16);
    tileY = srcPosY / 16 + !(srcPosY % 16);
}

bool Object::isDead(){
    return dead;
}

void Object::changeDir(int velX , int velY , int dir){
    this -> velX = velX;
    this -> velY = velY;
    this -> dir = dir;
}

void Object::becomeDead(bool stat , int idx){
    dead = stat;
    if (idx == 1) return;
    srcPosX = tileX * 16;
    srcPosY = tileY * 16;
}

void Object::goIntoTunnel(){
    if (srcPosY == 224){
        if (dir == LEFT && srcPosX == 0){
            tileX = 27;
        }
        else if (dir == RIGHT && srcPosX == 432){
            tileX = 0;
        }
        srcPosX = tileX * 16;
    }
}

void Object::resetTile(){
    this -> tileX = tileX;
    this -> tileY = tileY;

    dead = false;
    velX = velY = 0;
    srcPosX = tileX * 16;
    srcPosY = tileY * 16;
}
