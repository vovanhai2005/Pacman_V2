#include "Operator.h"
#include <limits>
#include <random>
#include <time.h>

#define fi first
#define se second

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
    soundManage = new SoundManage();
    itemManage = new GameItemManage();
    objectTexture -> loadImageToTileTexture(renderer);
    objectTexture -> loadCharacterTexture(renderer);
    soundManage -> initSound();
}

void Operator::gameOperate()
{
    map -> reset();
    delete pacman;
    delete blinky;
    delete pinky;
    delete inky;
    delete clyde;
    delete apple;
    pacman = new Pacman();
    blinky = new Ghost(13, 11, false);
    // std::cout << blinky -> getNextTileX() << " " << blinky -> getNextTileY() << std::endl;
    pinky = new Ghost(13, 14, true);
    inky = new Ghost(11, 14, true);
    std::cout << inky -> Lock() << std::endl;
    clyde = new Ghost(15, 14, true);
}

void Operator::renderGhost(SDL_Renderer *&renderer, Ghost *&ghost, int ghostType)
{
    // std::cout << ghost -> getNextTileX() << std::endl;
    // std::cout << ghost -> getPosX() << std::endl;
    // std::cout << ghost -> getPosY() << std::endl;
    // std::cout << ghost -> getGhostDir() << std::endl;
    objectTexture -> renderGhostTexture(renderer, ghost -> getPosX(), ghost -> getPosY(), ghostType, ghost -> getGhostDir());
}

void Operator::makingEvent(SDL_Event &e , SDL_Renderer *&renderer)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_d)
        {
            // std::cout << "true" << std::endl;

            int newDir = -1;
            int lastDir = -1;
            int pacmanTileX = pacman -> getTileX();
            int pacmanTileY = pacman -> getTileY();
            int pacmanPosX = pacman -> getPosX();
            int pacmanPosY = pacman -> getPosY();
            // for (int x = 0; x < 28; ++x) {
            //     for (int y = 0; y < 31; ++y) {
            //         std::cout << x << " " << y << " ";
            //         for (int dir = 0; dir < 4; ++dir){
            //             std::cout << map -> isDirChange(x , y , dir) << " ";
            //         }
            //         std::cout << std::endl;
            //     }
            // }
            // std::cout << std::endl;
            if (!pacman -> emptyDir()) lastDir = pacman -> getDir();

            if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) newDir = 0;
            else if (e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_d) newDir = 1;
            else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) newDir = 2;
            else if (e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_a) newDir = 3;
            // std::cout << lastDir << " " << newDir << " ";
            if (lastDir == -1){
                // std::cout << "case -1 " << map -> isDirChange(pacmanTileX , pacmanTileY , newDir) << " ";
                if (map -> isDirChange(pacmanTileX, pacmanTileY, newDir)){
                    pacman -> emptyUnique();
                    pacman -> insertStack(newDir);
                }
            }
            else{
                if (newDir % 2 == lastDir % 2){
                    if (map -> isDirChange(pacmanTileX, pacmanTileY, newDir))
                    {
                        pacman -> insertStack(newDir);
                        pacman -> emptyUnique();
                    }
                }
                else
                {
                    std::pair<int, int> nextCross = map -> getNearestCross(pacmanTileX, pacmanTileY, lastDir);
                    if (lastDir % 2 == 1 && newDir % 2 == 0)
                    {
                        if (pacmanPosY == pacmanTileY * 16)
                        {
                            if (map -> isDirChange(pacmanTileX, pacmanTileY, newDir))
                                pacman -> insertUnique(newDir, II(pacmanTileX, pacmanTileY));
                            else if (nextCross != II(-1, -1) && !map -> isWallBehind(nextCross, newDir) && abs(pacmanPosX - nextCross.first * 16) <= 48)
                                pacman -> insertUnique(newDir, nextCross);
                        }
                    }
                    else if (lastDir % 2 == 0 && newDir % 2 == 1)
                    {
                        if (pacmanPosX == pacmanTileX * 16)
                        {
                            if (map -> isDirChange(pacmanTileX, pacmanTileY, newDir))
                            {
                                pacman -> insertUnique(newDir, II(pacmanTileX, pacmanTileY));
                            }
                            else if (nextCross != II(-1, -1) && !map -> isWallBehind(nextCross, newDir) && abs(pacmanPosY - nextCross.second * 16) <= 48)
                                pacman -> insertUnique(newDir, nextCross);
                        }
                    }
                }
            }
            // std::cout << pacman -> size() << std::endl;
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
            objectTexture -> renderTileTexture(renderer, map -> getID(i, j), &dsRect);
        }
    }
    int dir = -1;
    if (!pacman -> emptyDir()) dir = pacman -> getDir();
    if (!pacman -> isDead())
    {
        renderGhost(renderer, blinky, Texture::BLINKY);
        renderGhost(renderer, pinky, Texture::PINKY);
        renderGhost(renderer, inky, Texture::INKY);
        renderGhost(renderer, clyde, Texture::CLYDE);
    }
    if (pacman -> isDead()) {
        objectTexture -> renderPacmanTexture(renderer, pacman -> getPosX(), pacman -> getPosY(), Texture::PACMAN_DEAD);
    }
    else objectTexture -> renderPacmanTexture(renderer, pacman -> getPosX(), pacman -> getPosY(), dir);
    // std::cout << pacman -> size() << std::endl;
    soundManage -> playSound();

}

void Operator::inLoop()
{
    int pacmanTileX = pacman -> getTileX();
    int pacmanTileY = pacman -> getTileY();
    int pacmanPosX = pacman -> getPosX();
    int pacmanPosY = pacman -> getPosY();
    int lastDir = -1;
    if (!pacman -> emptyDir()) lastDir = pacman -> getDir();

    if (!pacman -> isDead() && lastDir != -1) {
        if (pacmanTileX * 16 == pacmanPosX && pacmanTileY * 16 == pacmanPosY) {
            if (map -> isCross(pacmanTileX, pacmanTileY)) {
                if (!pacman -> emptyUnique() && pacman -> getUnique() == II(pacmanTileX, pacmanTileY)) pacman -> turn();
            }
            if (map -> isDirChange(pacmanTileX, pacmanTileY, pacman -> getDir())) pacman -> moving();
            else pacman -> stopMoving();
        }
        else {
            if (map -> isDirChange(pacmanTileX, pacmanTileY, lastDir)) pacman -> moving();
            else {
                if (pacmanTileX * 16 == pacmanPosX && pacmanTileY * 16 != pacmanPosY) pacman -> moving();
                else if (pacmanTileX * 16 != pacmanPosX && pacmanTileY * 16 == pacmanPosY) pacman -> moving();
                else pacman -> stopMoving();
            }
        }
    }

    int coinType = map -> coinCollected(pacmanTileX, pacmanTileY);

    if (coinType != 0){
        itemManage -> eatCoins(coinType);
        soundManage -> loadingSound(SoundManage::EAT_COIN);
    }

    pacman -> goIntoTunnel();
    
    ghostAI(blinky);
    ghostAI(pinky);
    ghostAI(inky);
    ghostAI(clyde);

    itemManage -> ghostStart(pinky , inky , clyde);     
}

void Operator::ghostAI(Ghost* &ghostID){
    
    if (ghostID == nullptr) return;
    int ghostTileX = ghostID -> getTileX();
    int ghostTileY = ghostID -> getTileY();
    int ghostPosX  = ghostID -> getPosX();
    int ghostPosY  = ghostID -> getPosY();
    int ghostOldDir = ghostID -> getGhostDir();
    int ghostNextTileX = ghostID -> getNextTileX();
    int ghostNextTileY = ghostID -> getNextTileY();

    if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 == ghostPosY) {
        if (map->isCross(ghostTileX, ghostTileY)) {
            if (ghostID->isFrighten()) {
                std::stack<int> whichDir;
                if (ghostOldDir % 2 == 1) {
                    if (map->isDirChange(ghostTileX, ghostTileY, Map::UP)) whichDir.push(0);
                    if (map->isDirChange(ghostTileX, ghostTileY, Map::DOWN)) whichDir.push(2);
                    if (map->isDirChange(ghostTileX, ghostTileY, ghostOldDir)) whichDir.push(ghostOldDir);
                }
                else {
                    if (map->isDirChange(ghostTileX, ghostTileY, Map::LEFT)) whichDir.push(3);
                    if (map->isDirChange(ghostTileX, ghostTileY, Map::RIGHT)) whichDir.push(1);
                    if (map->isDirChange(ghostTileX, ghostTileY, ghostOldDir)) whichDir.push(ghostOldDir);
                }
                int dir = rand() % (int) whichDir.size() + 1;
                while (dir > 1) whichDir.pop(), --dir;
                ghostID->setDir(whichDir.top());
                while (!whichDir.empty()) whichDir.pop();
            }
            else {
                int distanceUP, distanceDOWN, distanceLEFT, distanceRIGHT;
                distanceUP = distanceDOWN = distanceLEFT = distanceRIGHT = __INT32_MAX__;

                if (map->isDirChange(ghostTileX, ghostTileY, Map::UP))
                    distanceUP = map->getDist(II(ghostTileX, ghostTileY - 1), II(ghostNextTileX, ghostNextTileY), Map::UP);

                if (map->isDirChange(ghostTileX, ghostTileY, Map::DOWN))
                    distanceDOWN = map->getDist(II(ghostTileX, ghostTileY + 1), II(ghostNextTileX, ghostNextTileY), Map::DOWN);

                if (map->isDirChange(ghostTileX, ghostTileY, Map::LEFT))
                    distanceLEFT = map->getDist(II(ghostTileX - 1, ghostTileY), II(ghostNextTileX, ghostNextTileY), Map::LEFT);

                if (map->isDirChange(ghostTileX, ghostTileY, Map::RIGHT))
                    distanceRIGHT = map->getDist(II(ghostTileX + 1, ghostTileY), II(ghostNextTileX, ghostNextTileY), Map::RIGHT);

                int distanceMIN;
                if (ghostOldDir == Map::UP) {
                    distanceMIN = std::min(distanceUP, std::min(distanceLEFT, distanceRIGHT));
                    if (distanceMIN == distanceUP) ghostID->setDir(Map::UP);
                    else if (distanceMIN == distanceLEFT) ghostID->setDir(Map::LEFT);
                    else ghostID->setDir(Map::RIGHT);
                }
                else if (ghostOldDir == Map::DOWN) {
                    distanceMIN = std::min(distanceDOWN, std::min(distanceLEFT, distanceRIGHT));
                    if (distanceMIN == distanceDOWN) ghostID->setDir(Map::DOWN);
                    else if (distanceMIN == distanceLEFT) ghostID->setDir(Map::LEFT);
                    else ghostID->setDir(Map::RIGHT);
                }
                else if (ghostOldDir == Map::LEFT) {
                    distanceMIN = std::min(distanceUP, std::min(distanceDOWN, distanceLEFT));
                    if (distanceMIN == distanceUP) ghostID->setDir(Map::UP);
                    else if (distanceMIN == distanceDOWN) ghostID->setDir(Map::DOWN);
                    else ghostID->setDir(Map::LEFT);
                }
                else if (ghostOldDir == Map::RIGHT) {
                    distanceMIN = std::min(distanceUP, std::min(distanceRIGHT, distanceDOWN));
                    if (distanceMIN == distanceUP) ghostID->setDir(Map::UP);
                    else if (distanceMIN == distanceRIGHT) ghostID->setDir(Map::RIGHT);
                    else ghostID->setDir(Map::DOWN);
                }
            }
        }
        if (map->isDirChange(ghostTileX, ghostTileY, ghostID->getGhostDir())) ghostID->moving();
    }
    else {
        if (map->isDirChange(ghostTileX, ghostTileY, ghostID->getGhostDir())) ghostID->moving();
        else {
            if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 != ghostPosY && ghostID->getGhostDir() % 2 == 0) ghostID->moving();
            else if (ghostTileY * 16 == ghostPosY && ghostTileX * 16 != ghostPosX && ghostID->getGhostDir() % 2 == 1) ghostID->moving();
        }
    }
    ghostID->goIntoTunnel();
}

// void Operator::printf(){
//     std::cout << pacman -> size().first << " " << pacman -> size().second << '\n';
// }