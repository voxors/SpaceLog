#include "assetloader.h"
#include <SDL3_image/SDL_image.h>
#include <string>

Assetloader::Assetloader(SDL_Renderer* renderer)
{
    const std::string ressourcePath = "./ressource/";
    const std::string starPath = "Star.png";
    const std::string terran1Path = "Terran-1.png";
    const std::string ocean1Path = "Ocean-1.png";

    //Star
    SDL_Surface* image = IMG_Load((ressourcePath + starPath).c_str());
    textures[textureEnum::star] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_DestroySurface(image);
    //terran1
    image = IMG_Load((ressourcePath + terran1Path).c_str());
    textures[textureEnum::terran1] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_DestroySurface(image);
    //Ocean1
    image = IMG_Load((ressourcePath + ocean1Path).c_str());
    textures[textureEnum::ocean1] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_DestroySurface(image);
}
