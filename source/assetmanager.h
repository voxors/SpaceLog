#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <SDL3/SDL_render.h>

enum TextureEnum
{
    background,
    star,
    terran1,
    ocean1,
    planetShadow,
    sun,
    total
};

class AssetManager
{
private:
    SDL_Texture* textures[TextureEnum::total] = { nullptr };
    void loadTextureIntoArray(SDL_Renderer *renderer, const std::string imagePath, TextureEnum textureEnum);
public:
    AssetManager();
    ~AssetManager();
    bool loadRessourcesTextures(SDL_Renderer* renderer);
    SDL_Texture* getTexture(TextureEnum texture) { return textures[texture]; }
    void setBackgroundTexture(SDL_Texture* background) { textures[TextureEnum::background] = background; }
};

#endif // ASSETMANAGER_H
