#include "Chip-8.h"
#include "Helper.h"
#include "setupFunctions.h"
#include "SDL.h"
#include <iostream>
#include "audioManagement.h"

int main(int argc, char *argv[])
{
    const Display graphics {setupGraphic()};
    initializeAudio();

    chip8 myChip8 {};

    //Uncomment when building release
    // if (argc < 2) {
    //     std::cerr << "Incorrect Usage, Use: Chip_8.exe <rom_file>" << '\n';
    //     return 1;
    // }

    //User must directly insert the file path for the rom file they wish to run
    myChip8.loadGame("../Tests/5-quirks.ch8"); //Change to argv[1] for release build


    for (;;)
    {
        static auto lastTime {Clock::now()};
        const auto currentTime {Clock::now()};

        constexpr Seconds cpuInterval {1.0/700};
        static Seconds cpuAccumulator {0.0};

        cpuAccumulator += (currentTime - lastTime);
        lastTime = currentTime;

        // If we press or release a key,
        // we should store this state in the part that emulates the keypad
        myChip8.setKeys();
        myChip8.updateTimers();

        while (cpuAccumulator >= cpuInterval) {
            cpuAccumulator -= cpuInterval;
            myChip8.emulateCycle(graphics);
        }



        if (myChip8.getDrawFlag())
        {
            drawGraphics(graphics, myChip8);
            myChip8.setDrawFlag(false);
        }

    }

    return 0;
}
