#include "assetmanager.h"
#include <SDL3_image/SDL_image.h>
#include <string>

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
    for (int i = 0; i < TextureEnum::total; i++)
    {
        SDL_DestroyTexture(textures[i]);
    }
}

void AssetManager::loadTextureIntoArray(SDL_Renderer *renderer, const std::string imagePath, TextureEnum textureEnum)
{
    SDL_Surface* image = IMG_Load(imagePath.c_str());
    textures[textureEnum] = SDL_CreateTextureFromSurface(renderer, image);
    SDL_DestroySurface(image);
}

bool AssetManager::loadRessourcesTextures(SDL_Renderer *renderer)
{
    const std::string ressourcePath = "./ressource/";
    const std::string starPath = ressourcePath + "Star.png";
    const std::string terran1Path = ressourcePath + "Terran-1.png";
    const std::string ocean1Path = ressourcePath + "Ocean-1.png";
    const std::string planetShadowPath = ressourcePath + "Planet-Shadow.png";
    const std::string sunPath = ressourcePath + "Sun.png";

    loadTextureIntoArray(renderer, starPath, TextureEnum::star);
    loadTextureIntoArray(renderer, terran1Path, TextureEnum::terran1);
    loadTextureIntoArray(renderer, ocean1Path, TextureEnum::ocean1);
    loadTextureIntoArray(renderer, planetShadowPath, TextureEnum::planetShadow);
    loadTextureIntoArray(renderer, sunPath, TextureEnum::sun);

    return true;
}
