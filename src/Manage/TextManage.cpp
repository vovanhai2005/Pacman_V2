#include "TextManage.h"

TextManage::TextManage(int size)
{
    TTF_Init();
    font = TTF_OpenFont(FONT_NAME.c_str(), size);
    textTexture = nullptr;
    textSurface = nullptr;
}
TextManage::~TextManage()
{
    if (font != nullptr){
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (textTexture != nullptr){
        SDL_DestroyTexture(textTexture);
        textTexture = nullptr;
    }

    if (textSurface != nullptr){
        SDL_FreeSurface(textSurface);
        textSurface = nullptr;
    }
}

void TextManage::loadRenderText(SDL_Renderer *&renderer, std::string text, SDL_Color textColor)
{
    if (textSurface != nullptr) SDL_FreeSurface(textSurface);
    textSurface = TTF_RenderText_Blended(font, text.c_str(), textColor);
    if (textTexture != nullptr) SDL_DestroyTexture(textTexture);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
}

void TextManage::renderText(SDL_Renderer *&renderer, int scrPosX, int scrPosY, const int type)
{
    dsRect = {scrPosX, scrPosY, textSurface->w, textSurface->h};
    if (type == CENTER) {
        dsRect.x = scrPosX - textSurface->w / 2;
        dsRect.y = scrPosY - textSurface->h / 2;
    }
    SDL_RenderCopy(renderer, textTexture, nullptr, &dsRect);
}

int TextManage::getTextWidth(){
    return textSurface -> w;
}