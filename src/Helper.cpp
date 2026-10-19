#include "Helper.h"
#include <SDL_render.h>

#include "Chip-8.h"
#include "Display.h"


void clearScreen(const Display& graphics)
{
    SDL_SetRenderDrawColor(graphics.renderer, 0,0,0, 255);
    SDL_RenderClear(graphics.renderer);
    SDL_RenderPresent(graphics.renderer);
}

void drawGraphics(const Display& graphics, const chip8& emulator) {

    uint32_t pixels[64 * 32];

    // Convert CHIP-8 monochrome array to RGBA pixels
    for (int i = 0; i < (64 * 32); ++i) {
        // If the CHIP-8 pixel is 1, draw white (0xFFFFFFFF). If 0, draw black (0x000000FF).
        pixels[i] = (emulator.getGFX()[i] == 1) ? 0xFFFFFFFF : 0x000000FF;
    }

    SDL_UpdateTexture(graphics.texture, NULL, pixels, 64 * sizeof(uint32_t) );

    //clear renderer
    SDL_RenderClear(graphics.renderer);

    //Send texture to renderer
    SDL_RenderCopy(graphics.renderer, graphics.texture, nullptr, nullptr);
    
    SDL_RenderPresent(graphics.renderer);
}