#ifndef HELPER_H
#define HELPER_H
#define PASS
#include "Chip-8.h"
#include "Display.h"

void clearScreen(const Display& graphics);

void drawGraphics(const Display& graphics, const chip8& emulator);

#endif