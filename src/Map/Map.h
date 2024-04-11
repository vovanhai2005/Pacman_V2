#pragma once

#ifndef _MAP_H
#define _MAP_H

#include "SDL.h"
#include "../Manage/LogStat.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>

class Map{
    private:
        static const int MAP_WIDTH = 28;
        static const int MAP_HEIGHT = 31;
        static const int MODULO = 37;

        const std::string mapFile = "src/Map/Pacman_Map.txt";
        LogStatus* Console = new LogStatus("Map");

        int totalTile[MAP_HEIGHT][MAP_WIDTH];
        int dist[MAP_HEIGHT][MAP_WIDTH][MAP_HEIGHT][MAP_WIDTH][4];
        bool cross[MAP_HEIGHT][MAP_WIDTH][4];
        std::pair<int , int> crossNearestTile[MAP_HEIGHT][MAP_WIDTH][4];

        
    public:

        static const int UP = 0;
        static const int RIGHT = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;
        Map();

        ~Map(){
            Console = NULL;
            delete Console;
        }

        int getID(int x , int y);

        std::pair<int , int> getNearestCross(int x , int y , int dir);
        
        bool isSatis(int x);
        
        bool isWall(int x , int y);

        bool isWallBehind(std::pair<int , int> cross , int newDir);

        int coinCollected(int x , int y);

        bool isDirChange(int x , int y , int dir);

        void trackingCross();

        bool isCross(int y , int x);

        void findNearestCross();

        void distCalc();

        void reset();
};
#endif