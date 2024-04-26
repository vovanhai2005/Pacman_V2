#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <vector>
#include "GameControl.h"
#include "../Manage/Button.h"

class Game
{
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        Menu* startMenu = nullptr;
        GameControl* gameControl = nullptr;

        LogStatus* Console = new LogStatus("Game");
        std::vector<std::string> highScore;
        bool Running = false;
        bool runningMenu = false;
    public:
        static const int SCREEN_WIDTH = 882;
        static const int SCREEN_HEIGHT = 496;
        const std::string WINDOW_TITLE = "Pacman";
        std::vector<std::string> startMenuButtonText = {"New Game", "How to Play", "High Scores", "Sound: ON", "Exit"};

        Game();

        ~Game();

        void initSDL();

        void quitSDL();

        void runGame();

};
#endif