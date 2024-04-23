#pragma once

#ifndef _TICKMANAGE_H
#define _TICKMANAGE_H

#define CID std::pair<int , double>

#include <SDL.h>
#include <stack>

class TickManage{
    private:
        Uint32 lastTick;
        Uint32 FlastTick;
        Uint32 GlastTick;
        Uint32 lastFrame = 0;

        std::stack<CID> statusManage;

        int lastStatus;
        bool pause;
        double FRIGHTEN_TIME = 5.0;
        double SCATTERING_TIME = 7.0;
        double CHASING_TIME = 20.0;
    public:
        const int FPS = 60;
        const double FRIENDY_CHASE_TIME = 3.0;
        const double GREENDY_CHASE_TIME = 2.0;
        const int FRIGHTEN_MODE = 0;
        const int SCATTERING_MODE = 1;
        const int CHASING_MODE = 2;
        const double oo = -1;
        TickManage();

        bool isFrightenTime();

        bool isScatteringTime();

        void makeFrightenTime();

        double remainFrightenTime();

        void update();

        void stablizeFPS();

        bool pauseTick(const bool status);

        void resetTick(const int level);
};
#endif