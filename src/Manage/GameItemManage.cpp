#include "GameItemManage.h"
#include <iostream>
#include <string>

GameItemManage::GameItemManage(SDL_Renderer* &renderer) {
    level = 1;
    life = 3;
    coinsEat = 0;
    ghostEat = -1;
    score = 0;
    PINKY_COIN_OUT = 5;
    INKY_COIN_OUT = 30;
    CLYDE_COIN_OUT = 90;
}

GameItemManage::~GameItemManage() {

}

SDL_Texture* GameItemManage::loadImage(SDL_Renderer* &renderer, const std::string imagePath) {
    SDL_Surface* Image = IMG_Load(imagePath.c_str());
    SDL_Texture* loadTexture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);
    return loadTexture;
}

void GameItemManage::resetGameItem() {
    level = 1;
    life = 5;
    score = 0;
    coinsEat = 0;
    ghostEat = -1;
    PINKY_COIN_OUT = 5;
    INKY_COIN_OUT = 30;
    CLYDE_COIN_OUT = 90;
    pos = -1;
}

void GameItemManage::eatCoins(const int typeOfCoin) {
    ++coinsEat;
    if (typeOfCoin == smallCoin) score += 10;
    else if (typeOfCoin == bigCoin) {
        ghostEat = -1;
        score += 50;
    }
}

void GameItemManage::eatGhost(const int ghostTileX, const int ghostTileY) {
    (++ghostEat) %= 4;
    switch (ghostEat) {
        case 0: score += 200; break;
        case 1: score += 400; break;
        case 2: score += 800; break;
        case 3: score += 1600; break;
    }
    ghostEatPosX = ghostTileX;
    ghostEatPosY = ghostTileY;
}

void GameItemManage::dead() {
    --life;
}

int GameItemManage::ghostStreak() {
    return ghostEat;
}

int GameItemManage::getGhostEatPosX() {
    return ghostEatPosX;
}

int GameItemManage::getGhostEatPosY() {
    return ghostEatPosY;
}

int GameItemManage::getLife() {
    return life;
}

void GameItemManage::nextLevel() {
    ++level;
    coinsEat = 0;
    ghostEat = -1;
    if (level <= 3) {
        PINKY_COIN_OUT = 5;
        INKY_COIN_OUT = 30;
        CLYDE_COIN_OUT = 90;
    }
    else if (level <= 5) {
        PINKY_COIN_OUT = 0;
        INKY_COIN_OUT  = 5;
        CLYDE_COIN_OUT = 10;
    }
    else PINKY_COIN_OUT = INKY_COIN_OUT = CLYDE_COIN_OUT = 0;
}

bool GameItemManage::coinClear() {
    return (coinsEat == 244);
    //return true;
}

int GameItemManage::getLevel() {
    return level;
}

void GameItemManage::ghostStart(Ghost* &pinky, Ghost* &inky, Ghost* &clyde) {
    if (pinky->Lock() && coinsEat >= PINKY_COIN_OUT) pinky->ghostRespawn(Ghost::GHOST_COMMON_TILE_X, Ghost::GHOST_COMMON_TILE_Y, false);
    if (inky ->Lock() && coinsEat >= INKY_COIN_OUT) inky ->ghostRespawn(Ghost::GHOST_COMMON_TILE_X, Ghost::GHOST_COMMON_TILE_Y, false);
    if (clyde->Lock() && coinsEat >= CLYDE_COIN_OUT) clyde->ghostRespawn(Ghost::GHOST_COMMON_TILE_X, Ghost::GHOST_COMMON_TILE_Y, false);
}


int GameItemManage::remainCoins() {
    return 244 - coinsEat;
}

void GameItemManage::renderInfoInGame(SDL_Renderer* &renderer) {
    levelText -> loadRenderText(renderer, "Level: " + std::to_string(level), {255, 255, 255, 255});
    levelText -> renderText(renderer , 0 , 0 , TextManage::LEFT);
    livesText -> loadRenderText(renderer, "Life: " + std::to_string(life), {255, 255, 255, 255});
    livesText -> renderText(renderer, 0, 50, TextManage::LEFT);
    scoreText -> loadRenderText(renderer, "Scores: " + std::to_string(score), {255, 255, 255, 255});
    scoreText -> renderText(renderer, 0, 100, TextManage::LEFT);
}

// void GameItemManage::handleEGBoard(SDL_Event &e) {
//     if (e.type == SDL_KEYDOWN)
//     {
//         Mix_PlayChannel(7, navigationSound, 0);
//         if (e.key.keysym.sym == SDLK_d || e.key.keysym.sym == SDLK_RIGHT)
//         {
//             currentBut = 2;
//             noBut -> setStatus(Button::BUTTON_IN);
//             yesBut -> setStatus(Button::BUTTON_OUT);
//         }
//         else if (e.key.keysym.sym == SDLK_a || e.key.keysym.sym == SDLK_LEFT)
//         {
//             currentBut = 1;
//             yesBut->setStatus(Button::BUTTON_IN);
//             noBut->setStatus(Button::BUTTON_OUT);
//         }
//         else if (e.key.keysym.sym == SDLK_RETURN)
//         {
//             if (currentBut == 1)
//                 playerDecision = AGAIN;
//             else
//                 playerDecision = QUIT;
//         }
//         return;
//     }
// }

// void GameItemManage::runEGBoard(SDL_Renderer* &renderer) {
//     SDL_Rect dsRect = {441 - 250, 248 - 150, 500, 300};
//     SDL_RenderCopy(renderer, egBoard, nullptr, &dsRect);
//     yesBut->renderButton(renderer);
//     noBut ->renderButton(renderer);
//     if (newRecord) {
//         SDL_RenderCopy(renderer, hsBoard, nullptr, &dsRect);
//         static int caretTime = 0;
//         SDL_Rect caret = {395 + playerName->getTextWidth(), 265, 2, 20};
//         if (caretTime % 20 > 10) {
//             SDL_RenderFillRect(renderer, &caret);
//         }
//         ++caretTime;
//         caretTime %= 20;
//         if (playername != "") {
//             playerName->loadRenderText(renderer, playername.c_str(), {0, 0, 0, 255});
//             playerName->renderText(renderer, 395, 268, TextManage::LEFT);
//         }
//     }
// }

// int GameItemManage::getPlayerDecision(){
//     return playerDecision;
// }