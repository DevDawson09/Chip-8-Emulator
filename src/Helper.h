#ifndef HELPER_H
#define HELPER_H
#define PASS
#include "Display.h"

void draw(chip8::BYTE X, chip8::BYTE Y, chip8::BYTE N);

void clearScreen(const Display& graphics);

void drawGraphics(const Display& graphics, const chip8& emulator);

#endif