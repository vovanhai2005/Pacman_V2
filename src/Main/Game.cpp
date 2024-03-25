#include <Game.h>
#include <stdio.h>
#include <fstream>
Game::Game()
{
    window = NULL;
    renderer = NULL;
    playState = NULL;
    startMenu = NULL;
    runningMenu = false;
}

Game::~Game()
{
    free();
}

Game::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        Console -> Status(SDL_GetError());
    }
    else {
        window = SDL_CreateWindow(WINDOW_TITTLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (!window == NULL){
            Console -> Status(SDL_GetError());
        }
        else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            Console->Status("Renderer created successfully!");
            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY , "linear");
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            if (TTF_Init() < 0) Console->Status( TTF_GetError() );
            else Console->Status("TTF Ready!");

            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 2048) < 0) Console->Status( Mix_GetError() );
            else Console->Status("Audio Ready!");
            Mix_Volume(-1, MIX_MAX_VOLUME);

            ifstream inFILE("score.txt");
            string st;
            int cnt = 0;
            while(getline(inFILE , st)){
                ++cnt;
                if (cnt > 5) break;
                highscore.push_back(st);
            }
            inFILE.close();
        }
    }
}

Game::quitSDL()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRender(renderer);
    window = NULL;
    renderer = NULL;
    Console -> Status("Successfully exited!");
    ofstream revFILE("score.txt");
    for (int i = 1 ; i <= 5 ; ++i) 
        revFILE << highScore[i] << '\n';
    revFILE.close();
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
}

Game::runGame()
{
    
}

