#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "../Manage/LogStatus.h"
#include "../Object/Texture.h"

class Game
{
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

        LogStatus* Console = new LogStatus("Window");
        std::vector<std::string> highScore;
        bool Running = false;
        bool gameRunning = false;
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