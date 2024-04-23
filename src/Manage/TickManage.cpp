#include "TickManage.h"
#include <iostream>

TickManage::TickManage(){
    lastTick = SDL_GetTicks();
    statusManage.push( CID(CHASING_MODE, oo) );
    statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
    statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
    statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
    statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
    statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
    statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
    statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
}

bool TickManage::isFrightenTime(){
    return statusManage.top().first == FRIGHTEN_MODE;
}

bool TickManage::isScatteringTime(){
    return statusManage.top().first == SCATTERING_MODE;
}

void TickManage::makeFrightenTime(){
    lastStatus = statusManage.top().first;
    statusManage.pop();
    if (lastStatus == SCATTERING_MODE){
        statusManage.push(CID(SCATTERING_MODE , SCATTERING_TIME - SDL_GetTicks() + lastTick));
    }
    if (lastStatus == FRIGHTEN_MODE){
        statusManage.push(CID(FRIGHTEN_MODE , FRIGHTEN_TIME - SDL_GetTicks() + lastTick));
    }
    statusManage.push(CID(FRIGHTEN_MODE , FRIGHTEN_TIME));
    lastTick = SDL_GetTicks();
}

double TickManage::remainFrightenTime(){
    return FRIGHTEN_TIME - (SDL_GetTicks() - lastTick) * 1.0 / 1000;
}

void TickManage::update(){
    if (pause == true) {
        lastTick = SDL_GetTicks();
        return;
    }
    double lastTime = (SDL_GetTicks() - lastTick) / 1000.0;

    if (!statusManage.empty()) {
        if (lastTime > statusManage.top().second && statusManage.top().second != oo) {
            statusManage.pop(); 
            lastTick = SDL_GetTicks();
        }
    }
}

void TickManage::stablizeFPS() {
    if (SDL_GetTicks() - lastFrame < 1000 / FPS) {
        SDL_Delay(1000 / FPS + lastFrame - SDL_GetTicks());
    }
    lastFrame = SDL_GetTicks();
}

bool TickManage::pauseTick(const bool status) {
    return pause = status;
}

void TickManage::resetTick(const int level) {
    while (!statusManage.empty()) statusManage.pop();
    if (level == 1) {
        statusManage.push( CID(CHASING_MODE, oo) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 5.0;
    }
    else if (level < 5) {
        statusManage.push( CID(CHASING_MODE, oo) );
        statusManage.push( CID(SCATTERING_MODE, 1.0) );
        statusManage.push( CID(CHASING_MODE, 1033.0) );
        statusManage.push( CID(SCATTERING_MODE, 5.0) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 3.0;
    }
    else {
        statusManage.push( CID(CHASING_MODE, oo) );
        statusManage.push( CID(SCATTERING_MODE, 1.0) );
        statusManage.push( CID(CHASING_MODE, 1037.0) );
        statusManage.push( CID(SCATTERING_MODE, 5.0) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        statusManage.push( CID(CHASING_MODE, CHASING_TIME) );
        statusManage.push( CID(SCATTERING_MODE, SCATTERING_TIME) );
        FRIGHTEN_TIME = 1.0;
    }
    lastTick = SDL_GetTicks();
}