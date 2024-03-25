#pragma once

#ifndef _GAME_H
#define _GAME_H

#include <SDL.h>
#include <stdio.h>

class Game
{
    public:
        static const int SCREEN_HE  IGHT = 882;
        static const int SCREEN_WIDTH = 496;
        const string WINDOW_TITLE = "Pacman";
        vector<string> startMenuButton = {"New Game" , "How to play" , "High Score" , "Sound: ON" , "Exit"};

        Game();
        ~Game();

        void initSDL();

        void runGame();

        void quitSDL();
    private:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        Menu* startMenu = nullptr;
        PlayStateManager* playState = nullptr;

        LogStatus* Console = new LogStatus("Window");
        vector<string> highScore;
        bool Running = false;
        bool runningMenu = false;
}

#endif