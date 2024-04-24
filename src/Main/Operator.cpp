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
    objectTexture = NULL;
}

Operator::~Operator(){
    delete map;
    map = NULL;
    delete pacman;
    pacman = NULL;
    delete blinky;
    blinky = NULL;
    delete pinky;
    pinky = NULL;
    delete inky;
    inky = NULL;
    delete clyde;
    clyde = NULL;
    SDL_DestroyTexture(nextLevel);
    nextLevel = NULL;
    SDL_DestroyTexture(ready);
    ready = NULL;
    delete objectTexture;
    objectTexture = NULL;
}

void Operator::init(SDL_Renderer *&renderer)
{
    map = new Map();
    objectTexture = new Texture();
    soundManage = new SoundManage();
    itemManage = new GameItemManage(renderer);
    tickManage = new TickManage();
    objectTexture -> loadImageToTileTexture(renderer);
    objectTexture -> loadCharacterTexture(renderer);
    soundManage -> initSound();
    SDL_Surface* image = IMG_Load("assets/All Image/ready.png");
    ready = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
    image = IMG_Load("assets/All Image/next_level.png");
    nextLevel = SDL_CreateTextureFromSurface(renderer , image);
    SDL_FreeSurface(image);
}

void Operator::gameOperate()
{
    map -> reset();
    itemManage -> resetGameItem();
    delete pacman;
    pacman = new Pacman();
    delete blinky;
    blinky = new Ghost(((itemManage->getLevel() < 5) ? 13 : 12) , 11, false);
    delete pinky;
    pinky  = new Ghost(13, 14, true);
    delete inky;
    inky   = new Ghost(11, 14, true);
    delete clyde;
    clyde  = new Ghost(15, 14, true);
    soundManage -> loadingSound(SoundManage::START);
    tickManage -> resetTick(itemManage -> getLevel());
    tickManage -> pauseTick(true);
}

void Operator::renderGhost(SDL_Renderer *&renderer, Ghost *&ghost, int ghostType)
{
    int ghostPosX = ghost -> getPosX();
    int ghostPosY = ghost -> getPosY();
    int ghostDir = ghost -> getGhostDir();
    
    if (ghost -> isDead())
        objectTexture -> renderGhostTexture(renderer , ghostPosX , ghostPosY , Texture::GHOST_DEAD , ghostDir);
    else if (ghost -> isFrighten()) {
        objectTexture->renderGhostTexture(renderer, ghostPosX, ghostPosY, ghostType, Texture::BLUE_SCARED);
    }
    else objectTexture->renderGhostTexture(renderer, ghostPosX, ghostPosY, ghostType, ghostDir);
}

void Operator::makingEvent(SDL_Event &e , SDL_Renderer* &renderer)
{
    if (Mix_Playing(2) || Mix_Playing(4)) return;
    if (pacman -> isDead()) {
        if (runningEGBoard) itemManage -> handleEGBoard(e);
        return;
    }
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_LEFT || e.key.keysym.sym == SDLK_RIGHT || e.key.keysym.sym == SDLK_s || e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_d)
        {
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

void Operator::render(SDL_Renderer *&renderer){
    tickManage -> stablizeFPS();    
    // Render map
    SDL_Rect dsRect;
    for (int i = 0; i < 28; ++i){
        for (int j = 0; j < 31; ++j){
            dsRect = {i * 16 + 217, j * 16, 16, 16};
            objectTexture -> renderTileTexture(renderer , map -> getID(i , j), &dsRect);
        }
    }
    if (!runningEGBoard){
        int dir = -1;
        if (!pacman -> emptyDir()) dir = pacman -> getDir();
        if (!pacman -> isDead()){
            renderGhost(renderer , blinky , Texture::BLINKY);
            renderGhost(renderer , pinky , Texture::PINKY);
            renderGhost(renderer , inky , Texture::INKY);
            renderGhost(renderer , clyde , Texture::CLYDE);
            if (Mix_Playing(2) && !timeToNextLevel) {
                dsRect = {441 - 100, 285 - 35, 200, 60};
                SDL_RenderCopy(renderer, ready, nullptr, &dsRect);
            }
            objectTexture -> renderPacmanTexture(renderer , pacman -> getPosX() , pacman -> getPosY() , dir);
        }
        else{
            if(objectTexture -> pacmanIsDead()){
                if (itemManage -> getLife() > 0) resetObject();    
            }
            else objectTexture -> renderPacmanTexture(renderer , pacman -> getPosX(), pacman -> getPosY(), Texture::PACMAN_DEAD);
        }
        if (timeToNextLevel > 0) {
            dsRect = {441 - 97, 248 - 52, 194, 104};
            SDL_RenderCopy(renderer , nextLevel , nullptr , &dsRect);
        }
        if (Mix_Playing(4))  objectTexture -> renderGhostScore(renderer , itemManage -> getGhostEatPosX() , itemManage -> getGhostEatPosY() , itemManage -> ghostStreak());
        soundManage -> playSound();
        }
    if (runningEGBoard) itemManage->runEGBoard(renderer);
    else itemManage->renderInfoInGame(renderer); 
}

void Operator::inLoop()
{
    if (itemManage -> coinClear()) {
        if (timeToNextLevel > 0) timeToNextLevel--;
        else {
            itemManage -> nextLevel();
            tickManage -> resetTick(itemManage -> getLevel());
            resetObject();
            map -> reset();
        }
        return;
    }
    if (Mix_Playing(2) || Mix_Playing(4)) {
        if (Mix_Playing(2)) tickManage->pauseTick(true);
        return;
    }
    // if (pacman->isDead()) {
    //     if (runningEGBoard) {
    //         switch (itemManage->getPlayerDecision()) {
    //             case GameItemManage::AGAIN:
    //                 gameOperate();
    //                 break;
    //         }
    //     }
    //     return;
    // }
    tickManage -> update();
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
    int remainCoin = itemManage -> remainCoins();
    if (remainCoin < 50) soundManage -> loadingSound(SoundManage::MOVE_3);
    else if (remainCoin < 100) soundManage -> loadingSound(SoundManage::MOVE_2);
    else if (remainCoin < 150) soundManage -> loadingSound(SoundManage::MOVE_1);
    else soundManage -> loadingSound(SoundManage::MOVE_0);
    // Eat coin
    pacmanTileX = pacman -> getTileX();
    pacmanTileY = pacman -> getTileY();
    int typeOfCoin = map -> coinCollected(pacmanTileX, pacmanTileY);
    if (typeOfCoin) {
        itemManage -> eatCoins(typeOfCoin);
        soundManage -> loadingSound(SoundManage::EAT_COIN);
        if (typeOfCoin == GameItemManage::bigCoin) {
            tickManage -> makeFrightenTime();
            soundManage -> loadingSound(SoundManage::GHOST_TURN_BLUE);
            if (!blinky -> isDead()) blinky -> makeFrighten(true);
            if (!pinky -> isDead()) pinky -> makeFrighten(true);
            if (!inky -> isDead()) inky -> makeFrighten(true);
            if (!clyde -> isDead()) clyde -> makeFrighten(true);
        }
    }
    // Set frighten time
    if (!tickManage -> isFrightenTime()) {
        soundManage -> loadingSound(SoundManage::NORMAL_GHOST);
        blinky -> makeFrighten(false);
        pinky  -> makeFrighten(false);
        inky   -> makeFrighten(false);
        clyde  -> makeFrighten(false);
    }
    // Add scattering time
    blinky -> makeScattering(tickManage -> isScatteringTime());
    pinky  -> makeScattering(tickManage -> isScatteringTime());
    inky   -> makeScattering(tickManage -> isScatteringTime());
    clyde  -> makeScattering(tickManage -> isScatteringTime());

    pacmanPosX = pacman -> getPosX();
    pacmanPosY = pacman -> getPosY();
    lastDir = -1;
    if (!pacman -> emptyDir()) lastDir = pacman -> getDir();

    if (!pacman -> isDead()) {
        tickManage -> pauseTick(false);
        if (blinky -> isDead())
            blinky -> markDestination(13, 11);
        else if (!blinky -> isScattering())
            blinky -> markDestination(pacmanTileX , pacmanTileY);
        else blinky -> markDestination(Ghost::BLINKY_CORNER_TILE_X, Ghost::BLINKY_CORNER_TILE_Y);

        if (pinky -> isDead())
            pinky -> markDestination(13, 11);
        else if (!pinky -> isScattering()) {
            switch (lastDir) {
                case Map::UP:
                    pinky -> markDestination(pacmanTileX, pacmanTileY - 4);
                    break;
                case Map::DOWN:
                    pinky -> markDestination(pacmanTileX, pacmanTileY + 4);
                    break;
                case Map::LEFT:
                    pinky -> markDestination(pacmanTileX - 4, pacmanTileY);
                    break;
                case Map::RIGHT:
                    pinky -> markDestination(pacmanTileX + 4, pacmanTileY);
                    break;
            }
        }
        else pinky -> markDestination(Ghost::PINKY_CORNER_TILE_X, Ghost::PINKY_CORNER_TILE_X);

        if (inky -> isDead())
            inky -> markDestination(13, 11);
        else if (!inky -> isScattering())
            inky -> markDestination(2 * pacmanTileX - blinky -> getTileX(), 2 * pacmanTileY - blinky -> getTileY());
        else inky -> markDestination(Ghost::INKY_CORNER_TILE_X, Ghost::INKY_CORNER_TILE_Y);

        if (clyde -> isDead())
            clyde -> markDestination(13, 11);
        else if (!clyde -> isScattering()) {
            if ((pacmanTileX - clyde -> getTileX()) * (pacmanTileX - clyde -> getTileX()) + (pacmanTileY - clyde -> getTileY()) * (pacmanTileY - clyde -> getTileY()) <= 64)
                clyde -> markDestination(Ghost::CLYDE_CORNER_TILE_X, Ghost::CLYDE_CORNER_TILE_Y);
            else
                clyde -> markDestination(pacmanTileX, pacmanTileY);
        }
        else clyde -> markDestination(Ghost::CLYDE_CORNER_TILE_X, Ghost::CLYDE_CORNER_TILE_Y);
    }
    pacman -> goIntoTunnel();
    ghostAI(blinky);
    ghostAI(pinky);
    ghostAI(inky);
    ghostAI(clyde);

    itemManage -> ghostStart(pinky, inky, clyde);

    if (itemManage -> coinClear()){
        soundManage -> loadingSound(SoundManage::NEXT_LEVEL);
        timeToNextLevel = 100;
    }
}

void Operator::ghostAI(Ghost* &ghostID){
    
    if (ghostID == nullptr) return;
    int ghostTileX = ghostID -> getTileX();
    int ghostTileY = ghostID -> getTileY();
    int ghostPosX  = ghostID -> getPosX();
    int ghostPosY  = ghostID -> getPosY();
    int lastDir = ghostID -> getGhostDir();
    int ghostNextTileX = ghostID -> getNextTileX();
    int ghostNextTileY = ghostID -> getNextTileY();

    if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 == ghostPosY) {
        if (map -> isCross(ghostTileX, ghostTileY)) {
            if (ghostID -> isFrighten()) {
                std::stack<int> dirStack;
                if (lastDir % 2 == 1) {
                    if (map -> isDirChange(ghostTileX, ghostTileY, Map::UP)) dirStack.push(0);
                    if (map -> isDirChange(ghostTileX, ghostTileY, Map::DOWN)) dirStack.push(2);
                }
                else {
                    if (map -> isDirChange(ghostTileX, ghostTileY, Map::LEFT)) dirStack.push(3);
                    if (map -> isDirChange(ghostTileX, ghostTileY, Map::RIGHT)) dirStack.push(1);
                }
                if (map -> isDirChange(ghostTileX, ghostTileY, lastDir)) dirStack.push(lastDir);
                int dir = rand() % (int) dirStack.size() + 1;
                while (dir > 1) dirStack.pop(), --dir;
                ghostID -> setDir(dirStack.top());
                while (!dirStack.empty()) dirStack.pop();
            }
            else{
                int distanceUP = __INT32_MAX__ , distanceDOWN = __INT32_MAX__ , distanceLEFT = __INT32_MAX__ , distanceRIGHT = __INT32_MAX__;
                // Up distance
                if (map -> isDirChange(ghostTileX, ghostTileY, Map::UP)) distanceUP = map -> getDist(II(ghostTileX, ghostTileY - 1), II(ghostNextTileX, ghostNextTileY), Map::UP);
                // Down distance
                if (map -> isDirChange(ghostTileX, ghostTileY, Map::DOWN)) distanceDOWN = map -> getDist(II(ghostTileX, ghostTileY + 1), II(ghostNextTileX, ghostNextTileY), Map::DOWN);
                // Left distance
                if (map -> isDirChange(ghostTileX, ghostTileY, Map::LEFT)) distanceLEFT = map -> getDist(II(ghostTileX - 1, ghostTileY), II(ghostNextTileX, ghostNextTileY), Map::LEFT);
                // Right distance
                if (map -> isDirChange(ghostTileX, ghostTileY, Map::RIGHT)) distanceRIGHT = map -> getDist(II(ghostTileX + 1, ghostTileY), II(ghostNextTileX, ghostNextTileY), Map::RIGHT);

                int finalDist;
                if (lastDir == Map::UP) {
                    finalDist = std::min({distanceUP, distanceLEFT, distanceRIGHT});
                    if (finalDist == distanceUP) ghostID -> setDir(Map::UP);
                    else if (finalDist == distanceLEFT) ghostID -> setDir(Map::LEFT);
                    else ghostID -> setDir(Map::RIGHT);
                }
                else if (lastDir == Map::DOWN) {
                    finalDist = std::min({distanceDOWN , distanceLEFT, distanceRIGHT});
                    if (finalDist == distanceDOWN) ghostID -> setDir(Map::DOWN);
                    else if (finalDist == distanceLEFT) ghostID -> setDir(Map::LEFT);
                    else ghostID -> setDir(Map::RIGHT);
                }
                else if (lastDir == Map::LEFT) {
                    finalDist = std::min({distanceUP , distanceDOWN, distanceLEFT});
                    if (finalDist == distanceUP) ghostID -> setDir(Map::UP);
                    else if (finalDist == distanceDOWN) ghostID -> setDir(Map::DOWN);
                    else ghostID -> setDir(Map::LEFT);
                }
                else if (lastDir == Map::RIGHT) {
                    finalDist = std::min({distanceUP , distanceRIGHT, distanceDOWN});
                    if (finalDist == distanceUP) ghostID -> setDir(Map::UP);
                    else if (finalDist == distanceRIGHT) ghostID -> setDir(Map::RIGHT);
                    else ghostID -> setDir(Map::DOWN);
                }
            }
        }
        if (map -> isDirChange(ghostTileX, ghostTileY, ghostID -> getGhostDir())) ghostID -> moving();
    }
    else {
        if (map -> isDirChange(ghostTileX, ghostTileY, ghostID -> getGhostDir())) ghostID -> moving();
        else {
            if (ghostTileX * 16 == ghostPosX && ghostTileY * 16 != ghostPosY && ghostID -> getGhostDir() % 2 == 0) ghostID -> moving();
            else if (ghostTileY * 16 == ghostPosY && ghostTileX * 16 != ghostPosX && ghostID -> getGhostDir() % 2 == 1) ghostID -> moving();
        }
    }
    ghostID -> goIntoTunnel();
    if (ghostPosX == ghostNextTileX * 16 && ghostPosY == ghostNextTileY * 16) {
        if (ghostID -> isDead()) {
            ghostID -> setDead(false);
            soundManage -> loadingSound(SoundManage::RELIFE_GHOST);
            ghostID -> markDestination(Ghost::GHOST_COMMON_TILE_X , Ghost::GHOST_COMMON_TILE_Y);
        }
    }
    checkCollision(ghostID);
}

void Operator::checkCollision(Ghost* &ghostID){
    if (ghostID -> isDead()) return;
    int dist = sqr((pacman -> getPosX() - ghostID -> getPosX())) + sqr((pacman -> getPosY() - ghostID->getPosY()));
    if (dist <= 9){
        if (ghostID -> isFrighten()) {
            itemManage -> eatGhost(ghostID -> getPosX(), ghostID -> getPosY());
            ghostID -> setDead(true);
            ghostID -> makeFrighten(false);
            soundManage -> loadingSound(SoundManage::EAT_GHOST);
            soundManage -> loadingSound(SoundManage::GHOST_HOME);
        }
        else {
            pacman -> setDead(true, 1);
            itemManage -> dead();
            soundManage -> loadingSound(SoundManage::DEAD);
        }
    }
}

void Operator::resetObject(){
    delete pacman;
    pacman = new Pacman();
    //pacman->respawn();
    delete blinky;
    blinky = new Ghost(Ghost::BLINKY_START_TILE_X , Ghost::BLINKY_START_TILE_Y , false);
    delete pinky;
    pinky  = new Ghost(Ghost::PINKY_START_TILE_X , Ghost::PINKY_START_TILE_Y , true);
    delete inky;
    inky   = new Ghost(Ghost::INKY_START_TILE_X , Ghost::INKY_START_TILE_Y , true);
    delete clyde;
    clyde  = new Ghost(Ghost::CLYDE_START_TILE_X, Ghost::CLYDE_START_TILE_Y, true);
    soundManage -> reset();
    tickManage -> pauseTick(false);
}