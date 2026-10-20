#include "Chip-8.h"
#include "Helper.h"
#include "setupFunctions.h"
#include "SDL.h"
#include <iostream>

int main(int argc, char *argv[])
{
    const Display graphics {setupGraphic()};

    chip8 myChip8 {};

    //Uncomment when building release
    // if (argc < 2) {
    //     std::cerr << "Incorrect Usage, Use: Chip_8.exe <rom_file>" << '\n';
    //     return 1;
    // }

    //User must directly insert the file path for the rom file they wish to run
    myChip8.loadGame("../Tests/3-corax+.ch8"); //Change to argv[1] for release build

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
    }

    return 0;
}
