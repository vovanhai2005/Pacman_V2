#pragma once

#ifndef _SOUNDMANAGE_H_
#define _SOUNDMANAGE_H_

#include <SDL_mixer.h>
#include <vector>
#include "LogStatus.h"

class SoundManage {
    private:
        bool dead;
        bool ghostTurnBlue;
        bool ghostGoHome;
        int eatDotTime;
        int oldMoveType, newMoveType;
        Mix_Chunk* soundEffect[11];
    public:
        static const int MOVE_0 = 0;
        static const int MOVE_1 = 1;
        static const int MOVE_2 = 2;
        static const int MOVE_3 = 3;
        static const int START = 4;
        static const int EAT_COIN = 5;
        static const int EAT_GHOST = 6;
        static const int GHOST_TURN_BLUE = 7;
        static const int GHOST_HOME = 8;
        static const int DEAD = 9;
        static const int NEXT_LEVEL = 10;
        static const int TOTAL_SOUND_EFFECT = 11;
        static const int NORMAL_GHOST = 11;
        static const int RELIFE_GHOST = 12;

        SoundManage();

        ~SoundManage();

        void loadingSound(const int soundID);

        void initSound();

        void playSound();

        void reset();
};

#endif // _SOUNDMANAGE_H_
