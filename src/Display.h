#ifndef CHIP_8_DISPLAY_H
#define CHIP_8_DISPLAY_H
#include <SDL_render.h>

struct Display {
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
};

#endif //CHIP_8_DISPLAY_H
