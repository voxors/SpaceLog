#include "planet.h"
#include <SDL3/SDL_log.h>

Planet::Planet(SDL_Texture* texture, SDL_Texture* shadow) : GameObject(texture)
{
    this->shadow = shadow;
}

void Planet::render(SDL_Renderer *renderer, int camX, int camY)
{
    GameObject::render(renderer, camX, camY);

    SDL_FRect renderQuad = { (float)(posX - camX), (float)(posY - camY), (float)shadow->w, (float)shadow->h };

    if (!SDL_RenderTextureRotated(renderer, shadow, nullptr, &renderQuad, shadowPosition.at(shadowIndex), nullptr, SDL_FLIP_NONE))
    {
        SDL_Log("Render Failed: %s", SDL_GetError());
    }
}
