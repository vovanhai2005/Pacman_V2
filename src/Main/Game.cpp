#include <stdio.h>
#include <string>
#include <fstream>

#include "Game.h"
#include "../Map/Map.h"

Game::Game()
{
    window = NULL;
    renderer = NULL;
    // playState = NULL;
    // startMenu = NULL;
    gameRunning = false;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Game::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        Console->Status(SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        gameRunning = true;
        if (window == NULL)
        {
            Console->Status(SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            Console->Status("Renderer created successfully!");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            // if (TTF_Init() < 0) Console->Status( TTF_GetError() );
            // else Console->Status("TTF Ready!");

            // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) Console->Status( Mix_GetError() );
            // else Console->Status("Audio Ready!");
            // Mix_Volume(-1, MIX_MAX_VOLUME);

            std::ifstream inFILE("score.txt");
            std::string st;
            int cnt = 0;
            while (getline(inFILE, st))
            {
                ++cnt;
                if (cnt > 5)
                    break;
                highScore.push_back(st);
            }
            inFILE.close();
        }
    }
}

void Game::runGame()
{
    SDL_Event e;
    while (gameRunning)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                gameRunning = false;
        }
        // Clear renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        Map* map = new Map();
        Texture *objectTexture = new Texture();
        objectTexture->loadImageToTileTexture(renderer);
        objectTexture->loadCharacterTexture(renderer);

        SDL_Rect dsRect;
        for (int i = 0; i < 28; ++i)
        {
            for (int j = 0; j < 31; ++j)
            {
                dsRect = {i * 16 + 217, j * 16 , 16 , 16};
                objectTexture -> renderTileTexture(renderer , map -> getID(j , i) , &dsRect);
            }
        }

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
    // Mix_Quit();
    // TTF_Quit();
}
