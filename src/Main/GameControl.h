// #pragma once

// #ifndef _GAMECONTROL_H
// #define _GAMECONTROL_H

// #include "Operator.h"
// #include <iostream>
// #include <SDL_mixer.h>
// #include "../Manage/Button.h"
// #include "../Manage/Menu.h"
// #include <vector>


// class GameControl {
//     private:
//         std::vector<std::string> scoreData;
//         std::vector<int> muteChannel;
//         Operator* ope = nullptr;
//         Menu* pauseMenu = nullptr;
//         bool running = true;
//         bool runPauseMenu = false;
//     public:
//         std::vector<std::string> pauseMenuButtonText = {"Resume", "New Game", "How to Play", "Sound: ON", "Exit to Start Menu"};
//         PlayStateManager();

//         ~PlayStateManager();

//         void handleEvent(SDL_Event &e, SDL_Renderer* &renderer, bool &runningMain, std::vector<std::string> &scoreData);

//         void newGame(SDL_Renderer* &renderer);

//         void runGame(bool &exitToMenu);

//         void render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData);
// };
// #endif