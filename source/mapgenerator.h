#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <SDL3/SDL_render.h>
#include <vector>
#include <SDL3/SDL_rect.h>

namespace mapGen
{
std::vector<SDL_Point> genStar(int seed, int genWidth, int genHeight, int mapWidth, int mapHeight);
SDL_Texture* genBackground(int seed, SDL_Renderer* renderer, int mapWidth, int mapHeight);
}

#endif // MAPGENERATOR_H
