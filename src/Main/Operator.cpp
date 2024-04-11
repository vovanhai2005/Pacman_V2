#include "Operator.h"
#include <limits>
#include <random>
#include <time.h>

#define II std::pair<int , int>

using namespace std;

Operator::Operator()
{
    map = NULL;
    pacman = NULL;
    blinky = NULL;
    pinky = NULL;
    inky = NULL;
    clyde = NULL;
    apple = NULL;
    objectTexture = NULL;
}

void Operator::init(SDL_Renderer *&renderer)
{
    map = new Map();
    objectTexture = new Texture();
    objectTexture->loadImageToTileTexture(renderer);
    objectTexture->loadCharacterTexture(renderer);
}

void Operator::gameOperate()
{
    map->reset();
    delete pacman;
    delete blinky;
    delete pinky;
    delete inky;
    delete clyde;
    delete apple;
    pacman = new Pacman();
    blinky = new Ghost(13, 11, false);
    // std::cout << blinky->getNextTileX() << " " << blinky->getNextTileY() << std::endl;
    pinky = new Ghost(13, 14, true);
    inky = new Ghost(11, 14, true);
    clyde = new Ghost(15, 14, true);
}

void Operator::renderGhost(SDL_Renderer *&renderer, Ghost *&ghost, int ghostType)
{
    // std::cout << ghost -> getNextTileX() << std::endl;
    // std::cout << ghost -> getPosX() << std::endl;
    // std::cout << ghost -> getPosY() << std::endl;
    // std::cout << ghost -> getGhostDir() << std::endl;
    objectTexture->renderGhostTexture(renderer, ghost->getPosX(), ghost->getPosY(), ghostType, ghost->getGhostDir());
}

void Operator::makingEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        SDL_Keycode event = e.key.keysym.sym;
        if (event == SDLK_UP || event == SDLK_w || event == SDLK_DOWN || event == SDLK_s || event == SDLK_RIGHT || event == SDLK_d || event == SDLK_LEFT || event == SDLK_a)
        {
            int lastDir = -1, newDir = -1;
            if (!pacman->emptyDir())
                lastDir = pacman->getDir();
            if (event == SDLK_UP || event == SDLK_w)
                newDir = UP;
            if (event == SDLK_DOWN || event == SDLK_s)
                newDir = DOWN;
            if (event == SDLK_RIGHT || event == SDLK_d)
                newDir = RIGHT;
            if (event == SDLK_LEFT || event == SDLK_a)
                newDir = LEFT;

            if (lastDir == -1)
            {
                if (map -> isDirChange(pacman -> getTileX() , pacman -> getTileY() , newDir))
                {
                    pacman -> emptyUnique();
                    pacman -> insertStack(newDir);
                }
            }
            else
            {
                if ((newDir + lastDir) % 2 == 0)
                {
                    if (map->isDirChange(pacman->getTileX(), pacman->getTileY(), newDir))
                    {
                        pacman->insertStack(newDir);
                        pacman->emptyUnique();
                    }
                }
                else {
                    std::pair<int, int> nextCross = map -> getNearestCross(pacman -> getTileX() , pacman -> getTileY() , lastDir);
                    if (lastDir % 2 == 1 && newDir % 2 == 0) {
                        if (pacman -> getPosY() == pacman -> getTileY() * 16) {
                            if (map -> isDirChange(pacman -> getTileX() , pacman -> getTileY(), newDir)) {
                                pacman -> insertUnique(newDir , II(pacman -> getTileX() , pacman -> getTileY()));
                            }
                            else if (nextCross != II(-1, -1) && !map -> isWallBehind(nextCross, newDir) && abs(pacman -> getPosX() - nextCross.first * 16) <= 32) {
                                pacman -> insertUnique(newDir , nextCross);
                            }
                        }
                    }
                    else if (lastDir % 2 == 0 && newDir % 2 == 1)
                    {
                        if (pacman -> getPosX() == pacman -> getTileX() * 16) {
                            if (map->isDirChange(pacman -> getTileX() , pacman -> getTileY(), newDir)) {
                                pacman -> insertUnique(newDir, II(pacman -> getTileX() , pacman -> getTileY()));
                            }
                            else if (nextCross != II(-1, -1) && !map->isWallBehind(nextCross, newDir) && abs(pacman -> getPosY() - nextCross.second * 16) <= 32) {
                                pacman -> insertUnique(newDir , nextCross);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Operator::render(SDL_Renderer *&renderer)
{
    // Render map
    SDL_Rect dsRect;
    for (int i = 0; i < 28; ++i)
    {
        for (int j = 0; j < 31; ++j)
        {
            dsRect = {i * 16 + 217, j * 16, 16, 16};
            objectTexture->renderTileTexture(renderer, map->getID(j, i), &dsRect);
        }
    }
    renderGhost(renderer, blinky, Texture::BLINKY);
    renderGhost(renderer, pinky, Texture::PINKY);
    renderGhost(renderer, inky, Texture::INKY);
    renderGhost(renderer, clyde, Texture::CLYDE);
    pacman -> insertStack(LEFT);
    // std::cout << pacman -> getDir() << std::endl;
    objectTexture -> renderPacmanTexture(renderer , pacman -> getPosX() , pacman -> getPosY() , pacman -> getDir());
}
