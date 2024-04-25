// #include "Menu.h"
// #include "stdio.h"

// Menu::Menu(){
//     menuTexture = nullptr;

// }

// Menu::~Menu(){
//     SDL_DestroyTexture(menuTexture);
//     menuTexture = nullptr;
// }

// SDL_Texture* Menu::loadIMage(SDL_Renderer* &renderer , std::string imagePath){
//     SDL_Surface* image = IMG_Load(imagePath.c_str());
//     SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer , image);
//     SDL_FreeSurface(image);
//     return imageTexture;
// }

// void Menu::init(SDL_Renderer* &renderer , std::string imagePath , std::vector<std::string> scoreButton){
//     SDL_Surface* image = IMG_Load(imagePath.c_str());
//     if (image == nullptr){
//         std::cout << "Image got error";
//     }
//     else {
//         menuTexture = SDL_CreateTextureFromSurface(renderer , image);
//         SDL_FreeSurface(image);

//     }
// }