#define SDL_MAIN_USE_CALLBACKS

#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_keycode.h>

#include "gameobject.h"
#include "mapgenerator.h"
#include "assetmanager.h"

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static AssetManager* assetManager = nullptr;
constexpr int CameraSpeed = 10;
constexpr Uint32 wordWidth = 10000;
constexpr Uint32 wordHeight = 10000;
constexpr Uint32 virtualWidth = 960;
constexpr Uint32 virtualHeight = 540;
constexpr Uint32 backgroundParalax = 4;
constexpr Uint32 starParalax = 3;

SDL_Point cameraPosition = { 2500, 2500 };

std::vector<GameObject*> starList;

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_RenderClear(renderer);

    SDL_Texture* backgroundTexture = assetManager->getTexture(textureEnum::background);
    SDL_SetTextureColorMod(backgroundTexture, 0, 0, 255);
    SDL_FRect backgroundRect = { (float)cameraPosition.x / backgroundParalax, (float)cameraPosition.y / backgroundParalax, virtualWidth, virtualHeight };
    SDL_RenderTexture(renderer, backgroundTexture, &backgroundRect , nullptr);

    for (auto star : starList)
    {
        star->render(renderer, cameraPosition.x / starParalax, cameraPosition.y / starParalax);
    }

    GameObject* planettest = new GameObject(assetManager->getTexture(textureEnum::ocean1));
    planettest->setPosX(2600);
    planettest->setPosY(2600);
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

    assetManager = new AssetManager();
    assetManager->loadRessourcesTextures(renderer);

    std::vector<SDL_Point> starPoints = mapGen::genStar(1337, 200 / starParalax, 200 / starParalax, wordWidth / starParalax, wordHeight / starParalax);
    for (SDL_Point point : starPoints)
    {
        GameObject* star = new GameObject(assetManager->getTexture(textureEnum::star));
        star->setPosX(point.x);
        star->setPosY(point.y);
        starList.push_back(star);
    }

    SDL_Texture* background = mapGen::genBackground(1337, renderer, wordWidth / backgroundParalax, wordHeight / backgroundParalax);
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
