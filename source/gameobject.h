#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>

class GameObject
{
protected:
    int posX = 0;
    int posY = 0;
    SDL_Texture* texture = nullptr;
public:
    GameObject(SDL_Texture *texture);

    virtual void render(SDL_Renderer* renderer, int camX, int camY);

    int getPosX() const;
    void setPosX(int newPosX);
    int getPosY() const;
    void setPosY(int newPosY);
};

#endif

