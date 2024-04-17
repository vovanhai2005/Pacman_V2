#pragma once

#ifndef _GAMEITEMMANAGE_H
#define _GAMEITEMMANAGE_H

class GameItemManage {
    private:
        int life;
        int level;
        int score;
        int CoinsEat;
        int GhostEat;
        bool newRecord = false;
        int ghostEatPosX , ghostEatPosY;
    protected:
        SDL_Texture* loadImage(SDL_Renderer* &renderer , std::string imagePath);
    public:
        GameItemManage();

        ~GameItemManage();

        
};