#define SDL_MAIN_USE_CALLBACKS

#include <vector>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_keycode.h>

#include "gameobject.h"
#include "mapgenerator.h"
#include "assetloader.h"

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static Assetloader* assetloader = nullptr;
constexpr int CameraSpeed = 10;

SDL_Point cameraPosition = { 9500, 9500 };

std::vector<GameObject*> starList;

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_RenderClear(renderer);

    for (auto star : starList)
    {
        star->render(renderer, cameraPosition.x / 5, cameraPosition.y / 5);
    }

    GameObject* planettest = new GameObject(assetloader->getTexture(textureEnum::ocean1));
    planettest->setPosX(9700);
    planettest->setPosY(9700);
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

    if (!SDL_CreateWindowAndRenderer("SpaceLog", 960, 540, SDL_WINDOW_RESIZABLE, &window, &renderer))
    {
        SDL_Log("SDL_CreateWindowAndRenderer() failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetRenderLogicalPresentation(renderer, 960, 540, SDL_LOGICAL_PRESENTATION_LETTERBOX))
    {
        SDL_Log("SDL_SetRenderLogicalPresentation() failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    assetloader = new Assetloader(renderer);

    std::vector<SDL_Point> starPoints = mapGen::genStar(1337, 200, 200, 20000, 20000);
    for (SDL_Point point : starPoints)
    {
        GameObject* star = new GameObject(assetloader->getTexture(textureEnum::star));
        star->setPosX(point.x);
        star->setPosY(point.y);
        starList.push_back(star);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
