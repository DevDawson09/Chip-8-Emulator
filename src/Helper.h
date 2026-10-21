#ifndef HELPER_H
#define HELPER_H
#define PASS
#include <chrono>

#include "Chip-8.h"
#include "Display.h"

using Clock = std::chrono::steady_clock;
using Seconds = std::chrono::duration<double>;

void clearScreen(const Display& graphics);

void drawGraphics(const Display& graphics, const chip8& emulator);

#endif