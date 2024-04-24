#include "TextManage.h"

TextManage::TextManage(int size){
    font = TTF_OpenFont(FONT_NAME.c_str(), fontSize);
    textTexture = nullptr;
    textSurface = nullptr;
}