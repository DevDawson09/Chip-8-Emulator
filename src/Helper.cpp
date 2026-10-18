#include "Chip-8.h"
#include "Helper.h"
#include <SDL_render.h>
#include "Display.h"


void clearScreen(const Display& graphics)
{
    SDL_SetRenderDrawColor(graphics.renderer, 0,0,0, 255);
    SDL_RenderClear(graphics.renderer);
    SDL_RenderPresent(graphics.renderer);

}

void drawGraphics(const Display& graphics, const chip8& emulator) {
    PASS; //read from gfx
}

void draw(chip8::BYTE X, chip8::BYTE Y, chip8::BYTE N)
{
    //V[X], V[Y], N
    PASS;
}