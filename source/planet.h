#ifndef PLANET_H
#define PLANET_H

#include <vector>
#include "gameobject.h"

class Planet : public GameObject
{
private:
    SDL_Texture* shadow = nullptr;
    std::vector<int> shadowPosition = {0, 90, 180, 270};
    int shadowIndex = 0;
public:
    Planet(SDL_Texture* texture, SDL_Texture* shadow);

    void setShadowPosition(int index)
    {
        if (index >= 0 && index < shadowPosition.size())
        {
            shadowIndex = index;
        }
    }

    void render(SDL_Renderer* renderer, int camX, int camY) override;
};

#endif

