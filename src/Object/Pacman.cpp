#include "Pacman.h"
#include <iostream>

#define PII std::pair<int , std::pair<int , int > >

Pacman::Pacman() : Object(13 , 23){
    while(!Dir.empty()) Dir.pop();
    while(!Unique.empty()) Unique.pop();
}

bool Pacman::emptyDir(){
    return Dir.empty();
}

int Pacman::getDir(){
    return Dir.top();
}

bool Pacman::emptyUnique(){
    return Unique.empty();
}

std::pair<int , int> Pacman::getUnique(){
    return Unique.top().second ;
}

void Pacman::insertStack(int nDir)
{
    if (!Dir.empty()) Dir.pop();
    Dir.push(nDir);
}

void Pacman::insertUnique(int nDir , std::pair<int , int> Cross)
{
    if (!Unique.empty()){
        if (Unique.top().first != nDir)
            Unique.pop();
    }
    Unique.push(PII(nDir , Cross));
}

void Pacman::moving(){
    if (!Dir.empty()){
        int velX = 0 , velY = 0 , dir = -1;
        switch (Dir.top()){
            case UP:   velX = 0; velY = -PACMAN_PACE; dir = 0; break;
            case DOWN: velX = 0; velY = PACMAN_PACE; dir = 1; break;
            case LEFT: velX = -PACMAN_PACE; velY = 0; dir = 2; break;
            case RIGHT: velX = PACMAN_PACE; velY = 0; dir = 3; break;
        }
        changeDir(velX , velY , dir);
        move();
    }
}

void Pacman::stopMoving(){
    while(!Dir.empty()) Dir.pop();
}
void Pacman::turn(){
    stopMoving();

    Dir.push(Unique.top().first);
    Unique.pop();
}
