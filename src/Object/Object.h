#pragma once

#ifndef _OBJECT_H
#define _OBJECT_H

class Object {

    private: 
        int srcPosX , srcPosY;
        int velX = 0 , velY = 0;
        int tileX , tileY;
        int dir;
        bool dead;
    public:
        const static int UP = 0;
        const static int DOWN = 1;
        const static int LEFT = 2;
        const static int RIGHT = 3;

        const int OBJECT_WIDTH = 30;
        const int OBJECT_HEIGHT = 30;
        const int SCREEN_WIDTH = 476;
        const int SCREEN_HEIGHT = 527;

        Object(int tileX , int tileY , int velX = 0 , int velY = 0);

        ~Object() {
            
        }

        int getPosX();

        int getPosY();

        int getTileX();

        int getTileY();
        
        void getPosFromTile();

        void resetTile(const int tilex , const int tileY);

        void move();

        bool isDead();

        void changeDir(int velX , int velY , int dir);

        void becomeDead(bool stat , int idx);

        void goIntoTunnel();
         
        void resetTile();
};
#endif