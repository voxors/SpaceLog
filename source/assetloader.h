#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <SDL3/SDL_render.h>

enum textureEnum
{
    star,
    terran1,
    ocean1,
    total
};

class Assetloader
{
    SDL_Texture* textures[textureEnum::total];
public:
    Assetloader(SDL_Renderer* renderer);
    SDL_Texture* getTexture(textureEnum texture) { return textures[texture]; }
};

#endif // ASSETLOADER_H
