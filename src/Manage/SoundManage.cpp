#include "SoundManage.h"
#include <iostream>

SoundManage::SoundManage(){
    for (int i = 0 ; i < 11 ; ++i){
        sound[i] = NULL;
    }           
}

SoundManage::~SoundManage(){
    for (int i = 0 ; i < 11 ; ++i){
        Mix_FreeChunk(sound[i]);
        sound[i] = NULL;
    }   
}

void SoundManage::initSound(){
    sound[MOVE_0] = Mix_LoadWAV("assets/Sound/move_0.wav");
    sound[MOVE_1] = Mix_LoadWAV("assets/Sound/move_1.wav");
    sound[MOVE_2] = Mix_LoadWAV("assets/Sound/move_2.wav");
    sound[MOVE_3] = Mix_LoadWAV("assets/Sound/move_3.wav");
    sound[START] = Mix_LoadWAV("assets/Sound/start.wav");
    sound[EAT_COIN] = Mix_LoadWAV("assets/Sound/eat_coin.wav");
    sound[EAT_GHOST] = Mix_LoadWAV("assets/Sound/eat_ghost.wav");
    sound[GHOST_TURN_BLUE] = Mix_LoadWAV("assets/Sound/ghost_turn_blue.wav");
    sound[GHOST_HOME] = Mix_LoadWAV("assets/Sound/ghost_go_home.wav");
    sound[DEAD] = Mix_LoadWAV("assets/Sound/dead.wav");
    sound[NEXT_LEVEL] = Mix_LoadWAV("assets/Sound/next level.wav");

    bool check = true;
    for (int i = 0 ; i < 11 ; ++i){
        if (sound[i] == NULL){
            std::cout << "Error at: " << i << std::endl;
            check = false;
        }
    }
    if (check){
        std::cout << "Sound loaded successfully!";
    }

    Mix_PlayChannel(1 , sound[MOVE_0] , -1);            
    Mix_Pause(1);

    Mix_PlayChannel(3 , sound[EAT_COIN] , -1);           
    Mix_Pause(3);

    Mix_PlayChannel(5 , sound[GHOST_TURN_BLUE] , -1);   
    Mix_Pause(5);

    Mix_PlayChannel(6 , sound[GHOST_HOME] , -1);     
    Mix_Pause(6);
}

void SoundManage::loadingSound(const int soundID){
    if (soundID >= 0 && soundID <= 3) move = soundID;
    else if (soundID == EAT_COIN) eatCoin = 16;
    else if (soundID == EAT_GHOST) Mix_PlayChannel(4 , sound[EAT_GHOST] , -1);
    else if (soundID == NORMAL_GHOST) ghostTurnBlue = false;
    else if (soundID == GHOST_TURN_BLUE) ghostTurnBlue = true;
    else if (soundID == GHOST_HOME) ghostHome = true;
    else if (soundID == dead){
        dead = true;
        ghostTurnBlue = false;
        Mix_Pause(5);
        ghostHome = false;
        Mix_Pause(6);
        eatCoin = 0;
        Mix_Pause(3);
        Mix_Pause(1);
    }
    else if (soundID == START || soundID == NEXT_LEVEL){
        dead = false;
        ghostHome = false;    
        Mix_Pause(6);
        ghostTurnBlue = false;  
        Mix_Pause(5);
        eatCoin = 0;         
        Mix_Pause(3);
        Mix_Pause(1);
        if (soundID == NEXT_LEVEL) lastMove = MOVE_0;
        else lastMove = -1;
        Mix_PlayChannel(2 , sound[soundID] , 0);
    }
}

void SoundManage::playSound(){
    if (dead){
        Mix_PlayChannel(2 , sound[DEAD] , 0);
        dead = false;
    }
    if (Mix_Playing(2)) return;
    if (move != lastMove){
        Mix_PlayChannel(1 , sound[move] , -1);
        lastMove = move;
    }
    if (eatCoin > 0){
        eatCoin--;
        Mix_Resume(3);
    }
    else Mix_Pause(3);

    if (ghostTurnBlue) Mix_Resume(5);
    else Mix_Pause(5);

    if (ghostHome){
        Mix_Resume(6);
        if (ghostTurnBlue) Mix_Pause(5);
    }
    else{
        Mix_Pause(6);
        if (ghostTurnBlue) Mix_Resume(5);
    }
}

void SoundManage::reset(){
    Mix_PlayChannel(1 , sound[lastMove] , -1);
}

