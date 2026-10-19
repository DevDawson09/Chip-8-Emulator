#include "Chip-8.h"
#include "Helper.h"
#include "setupFunctions.h"
#include "SDL.h"

int main(int argc, char *argv[])
{
    const Display graphics {setupGraphic()};
    setupInputs();

    chip8 myChip8 {};

    // Copy the program into the memory
    myChip8.loadGame("../Tests/2-ibm-logo.ch8");

    for (;;)
    {
        myChip8.emulateCycle(graphics);
        if (myChip8.getDrawFlag()) //likely gotta implement a Hertz rate here.
        {
            drawGraphics(graphics, myChip8);
            myChip8.setDrawFlag(false);
        }



        // If we press or release a key,
        // we should store this state in the part that emulates the keypad
        myChip8.setKeys();
        SDL_Delay(1);
    }

    return 0;
}
