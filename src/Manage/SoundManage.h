#pragma once

#ifndef _SOUNDMANAGE_H
#define _SOUNDMANAGE_H

#include <SDL.h>
#include <SDL_mixer.h>

class SoundManage{
    private:
        Mix_Chunk* sound[11];

        bool dead = false;
        int eatCoin = 0;
        bool ghostTurnBlue = false;
    public:
        //Channel 1
        static const int MOVE_0 = 0;
        static const int MOVE_1 = 1;
        static const int MOVE_2 = 2;
        static const int MOVE_3 = 3;
        //  Channel 2
        static const int START = 4;
        static const int NEXT_LEVEL = 10;
        static const int DEAD = 9;
        // Channel 3
        static const int EAT_COIN = 5;
        // Channel 4
        static const int EAT_GHOST = 6;
        // Channel 5
        static const int GHOST_TURN_BLUE = 7;
        // Channel 6
        static const int GHOST_HOME = 8;

        SoundManage();

        ~SoundManage();

        void initSound();

        void playSound();
};
#endif