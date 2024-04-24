#pragma once

#ifndef _GAMECONTROL_H
#define _GAMECONTROL_H

#include "Operator.h"
#include <iostream>

class GameControl {
    private:
        Operator* ope = nullptr;
        // Menu* pauseMenu = nullptr;
        bool running = true;
        bool runPauseMenu = false;
    public:
        GameControl();

        ~GameControl();

        void handleEvent(SDL_Event &e, SDL_Renderer* &renderer, bool &runningMain);

        void newGame(SDL_Renderer* &renderer);

        void runGame();

        void render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData);
};
#endif