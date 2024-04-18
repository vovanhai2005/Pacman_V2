#pragma once

#ifndef _PACMAN_H
#define _PACMAN_H

#include "Object.h"
#include <iostream>
#include <algorithm>
#include <stack>

#define II std::pair<int , int>

class Pacman : public Object {
    private:
        std::stack<int> Dir;
        std::stack<std::pair<int , std::pair<int , int> > >  Unique;
    public:
        static const int PACMAN_TILE_X = 13;
        static const int PACMAN_TILE_Y = 23;
        static const int PACMAN_PACE = 2;

        Pacman();

        ~Pacman() {
            while (!Dir.empty()) Dir.pop();
            while (!Unique.empty()) Unique.pop();
        }

        bool emptyDir();

        int getDir();

        bool emptyUnique();

        std::pair<int , int> getUnique();

        void insertStack(int nDir);

        void insertUnique(int nDir , std::pair<int , int> Cross);
        
        void moving();
        
        void stopMoving();

        void stopTurning();

        void turn();

        // std::pair<int , int> size(){
        //     return II(Dir.size() , Unique.size());
        // }
};
#endif