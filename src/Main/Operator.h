#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include "../Map/Map.h"
#include "../Object/Pacman.h"
#include "../Object/Ghost.h"
#include "../Object/Item.h"
#include "../Object/Texture.h"
#include "../Object/Bomb.h"
#include "../Manage/TickManage.h"
#include "../Manage/GameItemManage.h"
#include "../Manage/SoundManage.h"

class Operator {
    private:
        Map* map;
        Pacman* pacman = nullptr;
        Ghost* blinky = nullptr;
        Ghost* pinky = nullptr;
        Ghost* inky = nullptr;
        Ghost* clyde = nullptr;
        Ghost* greendy = nullptr;
        Ghost* friendy = nullptr;
        Texture* objectTexture;
        TickManage* tickManage;
        GameItemManage* itemManage;
        SoundManage* soundManage;
        SDL_Texture* nextLevel;
        SDL_Texture* ready;
        Bomb* bomb;
        bool runningEGBoard = false;
        bool eatGreenApple = false;
        int timeToNextLevel = 0;
        int timeExist;

        Mix_Chunk* bombSound;

        int sqr(int x){
            return x * x;
        }
    protected:
        void resetObject();

        void ghostAI(Ghost* &ghostID);

        void checkCollision(Ghost* &ghostID);

        void renderGhost(SDL_Renderer *&renderer, Ghost *&ghost, int ghostType);
    public:
        Operator();

        ~Operator();

        void gameOperate(SDL_Renderer* &renderer);

        void init(SDL_Renderer* &renderer);

        void makingEvent(SDL_Event &e , SDL_Renderer* &renderer);

        void inLoop(SDL_Renderer *&renderer);

        void render(SDL_Renderer* &renderer);

        int getTimeLevel(){
            return timeToNextLevel;
        }

};

#endif // _ENGINE_H_