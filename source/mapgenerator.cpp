#include "mapgenerator.h"

#include <cmath>
#include <random>
#include "FastNoiseLite/FastNoiseLite.h"

std::vector<SDL_Point> mapGen::genStar(int seed, int genWidth, int genHeight, int mapWidth, int mapHeight)
{
    std::vector<SDL_Point> starVector;

    std::random_device rd;
    std::seed_seq({seed});
    std::mt19937 gen(rd());

    int starSquareWidth = mapWidth/genWidth;
    int starSquareHeight = mapHeight/genHeight;

    std::uniform_int_distribution xPosRd(1, starSquareWidth);
    std::uniform_int_distribution yPosRd(1, starSquareHeight);
    std::uniform_int_distribution existRd(0, 10);

    for (int x = 0; x < genWidth; x++)
    {
        for (int y = 0; y < genHeight; y++)
        {
            int posX = xPosRd(gen);
            int posY = yPosRd(gen);

            posX += x * starSquareWidth;
            posY += y * starSquareHeight;

            if (existRd(gen) < 9)
                starVector.push_back({posX, posY});
        }
    }

    return starVector;
}
