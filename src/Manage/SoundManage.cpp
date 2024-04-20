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

    for (int i = 0 ; i < 11 ; ++i){
        if (sound[i] == NULL){
            Console->Status(Mix_GetError());
        }
    }

    Mix_PlayChannel(1 , soundEffect[MOVE_0] , -1);            
    Mix_Pause(1);

    Mix_PlayChannel(3 , soundEffect[EAT_COIN] , -1);           
    Mix_Pause(3);

    Mix_PlayChannel(5 , soundEffect[GHOST_TURN_BLUE] , -1);   
    Mix_Pause(5);

    Mix_PlayChannel(6 , soundEffect[GHOST_HOME] , -1);     
    Mix_Pause(6);
}

void SoundManage::playSound(){
    if (dead){
        Mix_PlayChannel(2 , sound[DEAD] , 0);
        dead = false;
    }
    if (Mix_Playing(2)) return;
    if (eatCoin > 0){
        eatCoin--;
        Mix_Resume(3);
    }
    else Mix_Pause(3);

    if (ghostTurnBlue) Mix_Resume(5);
    else Mix_Pause(5);

    
}