#include "setupFunctions.h"
#include <SDL.h>
#include "Helper.h"

Display setupGraphic()
{
    Display graphics {};

    constexpr int screenWidth {1024};
    constexpr int screenHeight {512};

    SDL_Init(SDL_INIT_EVERYTHING);
    graphics.window = SDL_CreateWindow("Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

    graphics.renderer = SDL_CreateRenderer(graphics.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(graphics.renderer, 64, 32); //Chip-8 emulator resolution

    graphics.texture = SDL_CreateTexture(graphics.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);
    SDL_SetTextureScaleMode(graphics.texture, SDL_ScaleModeNearest);

    SDL_SetRenderDrawColor(graphics.renderer, 0,0,0,255);
    SDL_RenderClear(graphics.renderer);

    SDL_RenderPresent(graphics.renderer);

    return graphics;

}

