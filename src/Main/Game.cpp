#include <stdio.h>
#include <string>
#include <fstream>

#include "Game.h"
using namespace std;
Game::Game()
{
    window = nullptr;
    renderer = nullptr;
    gameControl = nullptr;
    startMenu = nullptr;
    runningMenu = false;
}

Game::~Game()
{
    delete gameControl;
    gameControl = nullptr;

    delete startMenu;
    startMenu = nullptr;

    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }

    if (window != nullptr) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
}

void Game::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        Console->Status( SDL_GetError() );
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        Console->Status("Window opened successfully!");
        Running = true;

        if (window == nullptr) {
            Console->Status( SDL_GetError() );
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            Console->Status("Renderer created successfully!");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (TTF_Init() < 0) Console->Status( TTF_GetError() );
            else Console->Status("TTF Ready!");

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) Console->Status( Mix_GetError() );
            else Console->Status("Audio Ready!");
            Mix_Volume(-1, MIX_MAX_VOLUME);

            freopen("score.txt", "r", stdin);
            std::string t = "";
            for (int i = 0; i < 10; ++i) {
                std::getline(std::cin, t);
                highScore.push_back(t);
            }
        }
    }
}

void Game::runGame()
{
    startMenu = new Menu(262, 170, startMenuButtonText.size(), 320, 30);
    startMenu->init(renderer, "assets/All Image/Pacman Pause Menu.png", startMenuButtonText);
    startMenu->changeRunStatus();

    SDL_Event e;
    runningMenu = true;
    bool startGame = false;
    gameControl = new GameControl();

    while (Running) {

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) Running = false;
            else {
                if (runningMenu) {
                    startMenu->handleEvent(e, renderer);
                    switch (startMenu->getStatus()) {
                        case Menu::PLAY_BUTTON_PRESSED:
                            runningMenu = false; break;
                        case Menu::EXIT_BUTTON_PRESSED:
                            Running = false; break;
                    }
                }
                else {
                    gameControl->handleEvent(e, renderer, runningMenu, highScore);
                    if (runningMenu) startMenu->reOpen();
                }
            }
        }
        if (!runningMenu) {
            if (!startGame) {
                gameControl->newGame(renderer);
                startGame = true;
            }
            std::cout << "haha";
            gameControl->runGame(renderer , runningMenu);
            if (runningMenu) startMenu->reOpen(), startGame = false;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (runningMenu)
            startMenu->render(renderer, highScore);
        else gameControl->render(renderer, highScore);

        SDL_RenderPresent(renderer);
    }
}

void Game::quitSDL()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = NULL;
    renderer = NULL;
    Console->Status("Successfully exited!");
    std::ofstream revFILE("score.txt");
    for (int i = 1; i <= 5; ++i)
        revFILE << highScore[i] << '\n';
    revFILE.close();
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}