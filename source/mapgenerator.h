#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <vector>
#include <SDL3/SDL_rect.h>

namespace mapGen
{
std::vector<SDL_Point> genStar(int seed, int genWidth, int genHeight, int mapWidth, int mapHeight);
}

#endif // MAPGENERATOR_H
