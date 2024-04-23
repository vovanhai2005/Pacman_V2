#pragma once

#ifndef _OPERATOR_H
#define _OPERATOR_H

#include <SDL.h>
#include <SDL_Mixer.h>
#include "../Map/Map.h"
#include "../Object/Pacman.h"
#include "../Object/Ghost.h"
#include "../Object/Item.h"
#include "../Object/Texture.h"
#include "../Manage/LogStat.h"
#include "../Manage/GameItemManage.h"
#include "../Manage/SoundManage.h"
#include "../Manage/TickManage.h"

class Operator {
    private:
        Map* map;
        Pacman* pacman = NULL;
        Ghost* blinky = NULL;
        Ghost* pinky = NULL;
        Ghost* inky = NULL;
        Ghost* clyde = NULL;
        Item* apple;
        Texture* objectTexture;
        SDL_Texture* nextLevel;
        SDL_Texture* ready;
        GameItemManage* itemManage;
        SoundManage* soundManage;
        TickManage* tickManage;
        int timeToNextLevel;    

    public:

        static const int UP = 0;
        static const int RIGHT = 1;
        static const int DOWN = 2;
        static const int LEFT = 3;

        Operator();

        ~Operator();

        void init(SDL_Renderer* &renderer);

        void gameOperate();

        void renderGhost(SDL_Renderer* &renderer , Ghost* &ghost , int ghostType);

        void makingEvent(SDL_Event &e , SDL_Renderer* &renderer);

        void render(SDL_Renderer* &renderer);

        void inLoop();

        void ghostAI(Ghost* &ghostID);

        int sqr(int x){
            return x * x;
        }

        void checkCollision(Ghost* &ghostID);

        void resetObject();

};
#endif