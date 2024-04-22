#pragma once

#ifndef _GHOST_H
#define _GHOST_H

#include "Object.h"
#include <iostream>

class Ghost : public Object {
    private:
        int nextTileX;
        int nextTileY;
        int ghostDir;
        bool frighten;
        bool scattering;
        bool lock;
        int velocity;
        int accelerate;
    public:

        static const int GHOST_COMMON_TILE_X = 13;
        static const int GHOST_COMMON_TILE_Y = 11;

        static const int BLINKY_START_TILE_X = 13;
        static const int BLINKY_START_TILE_Y = 11;
        static const int BLINKY_CORNER_TILE_X = 26;
        static const int BLINKY_CORNER_TILE_Y = 1;

        static const int PINKY_START_TILE_X = 13;
        static const int PINKY_START_TILE_Y = 14;
        static const int PINKY_CORNER_TILE_X = 1;
        static const int PINKY_CORNER_TILE_Y = 1;

        static const int INKY_START_TILE_X = 11;
        static const int INKY_START_TILE_Y = 14;
        static const int INKY_CORNER_TILE_X = 26;
        static const int INKY_CORNER_TILE_Y = 29;
        
        static const int CLYDE_START_TILE_X = 15;
        static const int CLYDE_START_TILE_Y = 14;
        static const int CLYDE_CORNER_TILE_X = 1;
        static const int CLYDE_CORNER_TILE_Y = 29;
        
        Ghost(int tileX , int tileY , bool Lock);

        int getNextTileX();

        int getNextTileY();

        int getGhostDir();

        void setDir(int dir);

        bool Lock();

        bool isFrighten();

        bool isScattering();

        void makeFrighten(bool stat);

        void makeScattering(bool stat);

        void moving();

        void markDestination(int tileX , int tileY , int acce = 1);

        void ghostRespawn(const int tileX , const int tileY , const bool lock);

};
#endif