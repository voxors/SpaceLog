#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL3/SDL_render.h>

enum textureEnum
{
    background,
    star,
    terran1,
    ocean1,
    total
};

class AssetManager
{
    SDL_Texture* textures[textureEnum::total] = { nullptr };
public:
    AssetManager();
    ~AssetManager();
    bool loadRessourcesTextures(SDL_Renderer* renderer);
    SDL_Texture* getTexture(textureEnum texture) { return textures[texture]; }
    void setBackgroundTexture(SDL_Texture* background) { textures[textureEnum::background] = background; }
};

#endif // ASSETMANAGER_H
