#include "Chip-8.h"
#include "Helper.h"
#include "SDL.h"

int main(int argc, char *argv[])
{
    setupGraphic();
    setupInputs();

    chip8 myChip8 {};

    // Copy the program into the memory
    myChip8.loadGame("../Tests/2-ibm-logo.ch8");

    for (;;)
    {
        myChip8.emulateCycle();
        if (myChip8.getDrawFlag())
            //drawGraphics();

        // If we press or release a key,
        // we should store this state in the part that emulates the keypad
        myChip8.setKeys();
    }
}
