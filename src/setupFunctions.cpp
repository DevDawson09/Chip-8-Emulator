#include "setupFunctions.h"
#include <SDL.h>
#include "Helper.h"

Display setupGraphic()
{
    constexpr Display graphics {};

    constexpr int screenWidth {1024};
    constexpr int screenHeight {512};

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    SDL_CreateRenderer(graphics.window, -1, 0);
    SDL_RenderSetLogicalSize(graphics.renderer, 64, 32); //Chip-8 emulator resolution

    SDL_SetRenderDrawColor(graphics.renderer, 0,0,0,255);
    SDL_RenderClear(graphics.renderer);

    SDL_RenderPresent(graphics.renderer);

    return graphics;

}

void setupInputs()
{
    PASS;
}