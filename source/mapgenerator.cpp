#include "mapgenerator.h"

#include <SDL3/SDL_log.h>

#include <cmath>
#include <random>
#include "FastNoiseLite/FastNoiseLite.h"

std::vector<SDL_Point> mapGen::genStar(int seed, int genWidth, int genHeight, int mapWidth, int mapHeight)
{
    std::vector<SDL_Point> starVector;

    std::random_device rd;
    std::mt19937 gen(seed);

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

constexpr Uint32 grayscaleValue[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    10, 10, 10, 10, 10, 10, 10, 10,
    20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 90, 90, 110,
    110, 110, 120, 120, 120, 120, 120, 120,
    120, 120, 120, 120, 120, 120, 120, 120,
};

SDL_Texture* mapGen::genBackground(int seed, SDL_Renderer* renderer, int mapWidth, int mapHeight)
{
    FastNoiseLite noiseGen(seed);
    noiseGen.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noiseGen.SetFrequency(0.003f);

    SDL_Surface* surface = SDL_CreateSurface(mapWidth, mapHeight, SDL_PIXELFORMAT_RGBA8888);
    Uint32* surfacePixel = reinterpret_cast<Uint32*>(surface->pixels);

    for (int y = 0; y < mapHeight; y++)
    {
        for (int x = 0; x < mapWidth; x++)
        {
            float noise = noiseGen.GetNoise((float)x,(float)y);
            noise += 1;
            noise *= 32;
            Uint32 noiseInt = std::lround(noise);

            *surfacePixel = grayscaleValue[noiseInt] << 24 | grayscaleValue[noiseInt] << 16 | grayscaleValue[noiseInt] << 8 | 255;

            surfacePixel++;
        }
    }

    SDL_Texture* background = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    return background;
}
