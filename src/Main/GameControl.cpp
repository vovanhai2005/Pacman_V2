#include "GameControl.h"

#include <iostream>

using namespace std;

GameControl::GameControl(SDL_Renderer* &renderer) {
    ope = new Operator();
    std::cout << "goi tui chua vay\n";
    ope->init(renderer);
    pauseMenu = new Menu(262, 170, pauseMenuButtonText.size(), 320, 30);
    runPauseMenu = false;
}

GameControl::~GameControl() {
    delete ope;
    ope = nullptr;

    runPauseMenu = false;
}

void GameControl::newGame(SDL_Renderer* &renderer) {
    static bool inited = false;
    if (!inited) {
        this->scoreData = scoreData;
        pauseMenu->init(renderer, "assets/All Image/Pacman Pause Menu.png", pauseMenuButtonText);
        ope->init(renderer);
        inited = true;
    }
    else {
        ope->gameOperate(renderer);
    }
}

void GameControl::runGame(SDL_Renderer* &renderer , bool &exitToMenu) {
    if (runPauseMenu == false) ope->inLoop(renderer , exitToMenu);
}

void GameControl::handleEvent(SDL_Event& e, SDL_Renderer* &renderer, bool &exitToMainMenu, std::vector<std::string> &scoreData) {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        runPauseMenu = true;
        pauseMenu->reOpen();
        while (!muteChannel.empty()) muteChannel.pop_back();
        for (int channel = 1; channel <= 8; ++channel) {
            if (Mix_Paused(channel) == 0) {
                Mix_Pause(channel);
                muteChannel.push_back(channel);
            }
        }
    }
    else {
        if (runPauseMenu) {
            pauseMenu->handleEvent(e, renderer);
            switch (pauseMenu->getStatus()) {
                case Menu::RESUME:
                    runPauseMenu = false;
                    for (int channel : muteChannel) Mix_Resume(channel);
                    break;
                case Menu::PLAY_BUTTON_PRESSED:
                    runPauseMenu = false;
                    ope->gameOperate(renderer);
                    break;
                case Menu::EXIT_BUTTON_PRESSED:
                    exitToMainMenu = true;
                    runPauseMenu = false; break;
            }
        }
        else ope->makingEvent(e , renderer , scoreData);
    }
}

void GameControl::render(SDL_Renderer* &renderer, const std::vector<std::string> &scoreData) {
    if (runPauseMenu) pauseMenu->render(renderer, scoreData);
    else ope->render(renderer, scoreData);
}