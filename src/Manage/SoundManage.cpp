#include "SoundManage.h"
#include <iostream>

using namespace std;

SoundManage::SoundManage() {
    for (int i = 0; i < 11; ++i)
        soundEffect[i] = nullptr;
    eatDotTime = 0;
    oldMoveType = -1;
    newMoveType = MOVE_0;
    ghostTurnBlue = false;
    ghostGoHome = false;
    dead = false;
}

SoundManage::~SoundManage() {
    for (int i = 0; i < 11; ++i) {
        Mix_FreeChunk(soundEffect[i]);
        soundEffect[i] = nullptr;
    }
}

void SoundManage::loadingSound(const int soundID) {
    //cout << soundID << endl;
    if (soundID == EAT_COIN) eatDotTime = 16;
    else if (soundID == EAT_GHOST) Mix_PlayChannel(4, soundEffect[EAT_GHOST], 0);
    else if (soundID <= 3) newMoveType = soundID;
    else if (soundID == GHOST_HOME) ghostGoHome = true;
    else if (soundID == RELIFE_GHOST) ghostGoHome = false;
    else if (soundID == GHOST_TURN_BLUE) ghostTurnBlue = true;
    else if (soundID == NORMAL_GHOST) ghostTurnBlue = false;
    else if (soundID == DEAD) {
        dead = true;
        ghostGoHome = false;    Mix_Pause(6);
        ghostTurnBlue = false;  Mix_Pause(5);
        eatDotTime = 0;         Mix_Pause(3);
        Mix_Pause(1);
    }
    else if (soundID == START || soundID == NEXT_LEVEL) {
        dead = false;
        ghostGoHome = false;    Mix_Pause(6);
        ghostTurnBlue = false;  Mix_Pause(5);
        eatDotTime = 0;         Mix_Pause(3);
        Mix_Pause(1);
        if (soundID == NEXT_LEVEL) oldMoveType = MOVE_0;
        else oldMoveType = -1;
        Mix_PlayChannel(2, soundEffect[soundID], 0);
    }
}

void SoundManage::initSound() {
    soundEffect[MOVE_0] = Mix_LoadWAV("assets/Sound/move_0.wav");
    soundEffect[MOVE_1] = Mix_LoadWAV("assets/Sound/move_1.wav");
    soundEffect[MOVE_2] = Mix_LoadWAV("assets/Sound/move_2.wav");
    soundEffect[MOVE_3] = Mix_LoadWAV("assets/Sound/move_3.wav");
    soundEffect[START] = Mix_LoadWAV("assets/Sound/start.wav");
    soundEffect[EAT_COIN] = Mix_LoadWAV("assets/Sound/eat_coin.wav");
    soundEffect[EAT_GHOST] = Mix_LoadWAV("assets/Sound/eat_ghost.wav");
    soundEffect[GHOST_TURN_BLUE] = Mix_LoadWAV("assets/Sound/ghost_turn_blue.wav");
    soundEffect[GHOST_HOME] = Mix_LoadWAV("assets/Sound/ghost_go_home.wav");
    soundEffect[DEAD] = Mix_LoadWAV("assets/Sound/dead.wav");
    soundEffect[NEXT_LEVEL] = Mix_LoadWAV("assets/Sound/next level.wav");

    for (int i = 0; i < 11; ++i) if (soundEffect == nullptr)
        std::cout << "Error at: " << i << std::endl; 

    /*
        8 channels
        move 0->3 : channel 1
        dead start: channel 2
        eat dot: channel 3
        eat ghost: channel 4
        ghost turn blue: channel 5
        ghost go home: channel 6
    */
    Mix_PlayChannel(1, soundEffect[MOVE_0], -1);            Mix_Pause(1);
    Mix_PlayChannel(3, soundEffect[EAT_COIN], -1);           Mix_Pause(3);
    Mix_PlayChannel(5, soundEffect[GHOST_TURN_BLUE], -1);   Mix_Pause(5);
    Mix_PlayChannel(6, soundEffect[GHOST_HOME], -1);     Mix_Pause(6);
    Mix_Pause(8);
}

void SoundManage::playSound() {
    /// channel 1
    if (dead) {
        Mix_PlayChannel(2, soundEffect[DEAD], 0);
        dead = false;
    }
    if (Mix_Playing(2)) return;
    if (newMoveType != oldMoveType) {
        Mix_PlayChannel(1, soundEffect[newMoveType], -1);
        oldMoveType = newMoveType;
    }
    if (eatDotTime > 0) {
        --eatDotTime;
        Mix_Resume(3);
    }
    else Mix_Pause(3);
    if (ghostTurnBlue) Mix_Resume(5);
    else Mix_Pause(5);
    if (ghostGoHome) {
        Mix_Resume(6);
        if (ghostTurnBlue) Mix_Pause(5);
    }
    else {
        Mix_Pause(6);
        if (ghostTurnBlue) Mix_Resume(5);
    }
}

void SoundManage::reset() {
    Mix_PlayChannel(1, soundEffect[oldMoveType], -1);
}
