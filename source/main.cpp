#define SDL_MAIN_USE_CALLBACKS

#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_keycode.h>

#include "gameobject.h"
#include "planet.h"
#include "mapgenerator.h"
#include "assetmanager.h"

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static AssetManager* assetManager = nullptr;
constexpr int CameraSpeed = 10;
constexpr Uint32 worldWidth = 10000;
constexpr Uint32 worldHeight = 10000;
constexpr Uint32 virtualWidth = 960;
constexpr Uint32 virtualHeight = 540;
constexpr SDL_Point maxCameraPos = {worldWidth - virtualWidth, worldHeight - virtualHeight};
constexpr Uint32 backgroundParalax = 4;
constexpr Uint32 starParalax = 3;

SDL_Point cameraPosition = { 5000 - virtualWidth / 2, 5000 - virtualHeight / 2 };

std::vector<GameObject*> starList;

SDL_AppResult SDL_AppIterate(void *appstate)
{
    //Verify New Camera position to keep it in bound
    if (cameraPosition.x < 0)
        cameraPosition.x = 0;
    if (cameraPosition.x > maxCameraPos.x)
        cameraPosition.x = maxCameraPos.x;
    if (cameraPosition.y < 0)
        cameraPosition.y = 0;
    if (cameraPosition.y > maxCameraPos.y)
        cameraPosition.y = maxCameraPos.y;

    SDL_RenderClear(renderer);

    SDL_Texture* backgroundTexture = assetManager->getTexture(textureEnum::background);
    SDL_SetTextureColorMod(backgroundTexture, 0, 0, 255);
    SDL_FRect backgroundRect = { (float)cameraPosition.x / backgroundParalax, (float)cameraPosition.y / backgroundParalax, virtualWidth , virtualHeight };
    SDL_RenderTexture(renderer, backgroundTexture, &backgroundRect , nullptr);

    for (GameObject *star : starList)
    {
        star->render(renderer, cameraPosition.x / starParalax,
                     cameraPosition.y / starParalax);
    }

    Planet* planettest = new Planet(assetManager->getTexture(textureEnum::terran1)
                                    , assetManager->getTexture(textureEnum::planetShadow));
    planettest->setPosX(5000);
    planettest->setPosY(5000);
    planettest->setShadowPosition(2);
    planettest->render(renderer, cameraPosition.x, cameraPosition.y);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

void KeyboardEventHandler(SDL_KeyboardEvent* event)
{
    switch (event->key)
    {
    case SDLK_UP:
        cameraPosition.y -= CameraSpeed;
        break;
    case SDLK_DOWN:
        cameraPosition.y += CameraSpeed;
        break;
    case SDLK_LEFT:
        cameraPosition.x -= CameraSpeed;
        break;
    case SDLK_RIGHT:
        cameraPosition.x += CameraSpeed;
        break;
    }
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_QUIT:  /* triggers on last window close and other things. End the program. */
        return SDL_APP_SUCCESS;
        break;
    case SDL_EVENT_KEY_DOWN:
        KeyboardEventHandler((SDL_KeyboardEvent*)event);
        break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("SpaceLog", "0.1", "SpaceLog");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL_Init(SDL_INIT_VIDEO) failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("SpaceLog", virtualWidth, virtualHeight, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer() failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetRenderLogicalPresentation(renderer, virtualWidth, virtualHeight, SDL_LOGICAL_PRESENTATION_LETTERBOX))
    {
        SDL_Log("SDL_SetRenderLogicalPresentation() failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_SetRenderVSync(renderer, true);

    assetManager = new AssetManager();
    assetManager->loadRessourcesTextures(renderer);

    std::vector<SDL_Point> starPoints = mapGen::genStar(1337, 500 / starParalax, 500 / starParalax, worldWidth / (starParalax / 2 ), worldHeight / (starParalax / 2 ));
    for (SDL_Point point : starPoints)
    {
        GameObject* star = new GameObject(assetManager->getTexture(textureEnum::star));
        star->setPosX(point.x);
        star->setPosY(point.y);
        starList.push_back(star);
    }

    SDL_Texture* background = mapGen::genBackground(1337, renderer, worldWidth / (backgroundParalax / 2), worldHeight / (backgroundParalax / 2));
    assetManager->setBackgroundTexture(background);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    delete assetManager;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
