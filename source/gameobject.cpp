#include "gameobject.h"
#include <SDL3_image/SDL_image.h>
#include <cmath>

int GameObject::getPosY() const
{
    return posY;
}

void GameObject::setPosY(int newPosY)
{
    posY = newPosY;
}

int GameObject::getPosX() const
{
    return posX;
}

void GameObject::setPosX(int newPosX)
{
    posX = newPosX;
}

GameObject::GameObject(SDL_Texture* texture)
{
    this->texture = texture;
}

void GameObject::render(SDL_Renderer* renderer, int camX, int camY)
{
    SDL_FRect renderQuad = { (float)(posX - camX), (float)(posY - camY), (float)texture->w, (float)texture->h };

    if (!SDL_RenderTexture(renderer, texture, nullptr, &renderQuad))
    {
        SDL_Log("Render Failed: %s", SDL_GetError());
    }
}
