#include "Button.h"

Button::Button(int width , int height , int srcPosX , int srcPosY){
    buttonRect = {srcPosX , srcPosY , width , height};
    normalText = new TextManage(24);
    selectText = new TextManage(24);
    selectTextDetail = new TextManage(18);
}

void Button::loadButton(SDL_Renderer* &renderer, std::string text) {
    if (text == "") return;
    normalText -> loadRenderText(renderer , text , normalColor);
    selectText -> loadRenderText(renderer , text , selectColor);
    bText = text;
    if (text == "New Game") bDetail = "Press Enter to play a new game.";
    else if (text == "Resume") bDetail = "Press Enter to continue the game.";
    else if (text == "How to Play") bDetail = "Press Enter for instructions on how to play.";
    else if (text == "High Scores") bDetail = "Press Enter for High score.";
    else if (text == "Exit") bDetail = "Press Enter to quit the game.";
    else if (text == "Exit to Start Menu") bDetail = "Press Enter to return to the Start Menu.";
    else bDetail = "";

    if (bDetail != "") selectTextDetail->loadRenderText(renderer, bDetail, normalColor);
    else {
        delete selectTextDetail;
        selectTextDetail = nullptr;
    }
}

void Button::renderButton(SDL_Renderer* &renderer) {
    if (buttonStatus == BUTTON_IN) {
        SDL_SetRenderDrawColor(renderer, 251, 69, 152, 255);
        SDL_RenderFillRect(renderer, &buttonRect);

        SDL_SetRenderDrawColor(renderer, selectColor.r, selectColor.g, selectColor.b, selectColor.a);
        selectText->renderText(renderer, buttonRect.x + buttonRect.w / 2, buttonRect.y + buttonRect.h / 2, TextManage::CENTER);

        if (selectTextDetail != nullptr) {
            SDL_SetRenderDrawColor(renderer, normalColor.r, normalColor.g, normalColor.b, normalColor.a);
            selectTextDetail->renderText(renderer, 441, 400, TextManage::CENTER);
        }
    }
    else if (buttonStatus == BUTTON_OUT) {
        SDL_SetRenderDrawColor(renderer, normalColor.r, normalColor.g, normalColor.b, normalColor.a);
        normalText->renderText(renderer, buttonRect.x + buttonRect.w / 2, buttonRect.y + buttonRect.h / 2, TextManage::CENTER);
    }
}

void Button::setStatus(const int status) {
    buttonStatus = status;
}

bool Button::checkMousePos(const int &x, const int &y) const {
    if (x < buttonRect.x || x > buttonRect.x + buttonRect.w) return false;
    if (y < buttonRect.y || y > buttonRect.y + buttonRect.h) return false;
    return true;
}

std::string Button::getText() const {
    return bText;
}
