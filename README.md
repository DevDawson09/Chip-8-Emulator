# Chip-8

CHIP-8 Emulator — Windows x64

## Overview
A Chip-8 is a virtual machine designed to run old 8-bit games on low-level hardware such as the COSMAC VIP. It lets 
user's run or write old retro games without complex machine code. A Chip-8 emulator is designed to mimic this simplicity
of the original virtual machine while also acting as a very beginner-friendly gateway into emulation design in general.

## Why I Built This
I recently got super interested in lower-level programming languages coming from python due
to a friend I have who can code Assembly inspiring me to learn it. To start I figured i'd learn
C++ and the number 1 project I was told to do as my first proper C++ project was a chip-8 emulator.

From this, I've learnt not just more about C++, but also CPU's and emulation in general. While i'm sure i still
have much to learn, and my skills are certainly not great, this project served its purpose in solidifying my current 
understanding of C++ as well as my interest in the programming language.

**FEATURES**
Runs all 35 opcodes according to the behavior of the COSMAC VIP Chip-8.
Uses SDL2 to handle graphics, input, and audio.
Can run all ROMs suited for the COSMAC VIP version of chip-8 emulators.

**HOW TO RUN**
Unloaded Version:
1. Download the latest release
2. Extract .zip file
3. open extracted file in terminal
4. Use the following command to run the emulator with specific rom file

   .\Chip_8.exe "C:\path\to\your-rom.ch8"

Loaded Version:
1. Download the latest release
2. Extract .zip file
3. run Chip_8.exe (will automatically run whatever rom is pre-loaded into that version)

**REQUIREMENTS**
- Windows 64-bit
- Required runtime dependencies included with the release
- A compatible CHIP-8 ROM

**KEYMAP**
Due to the 16 key keymap of the chip-8 emulator, the following keys
represent the corresponding chip-8 keys.

``text
1 2 3 4         1 2 3 C
q w e r   =>    4 5 6 D
a s d f         7 8 9 E
z x c v         A 0 B F
``



**HOW IT WORKS**
Alright bear with me as i may be wrong, or not fully understand the system.
Essentially, it first initializes an instance that is meant to mimic the properties of the original chip-8 emulator
(along with some additionally properties for functionality). Then it also intializes the audio and graphics libraries
which will be used to read information from the chip-8 instance, and present the according
results on our machine.

As for the actual game loop, it first reads through the rom file and loads all the information
into the chip-8's memory. Then, at a fixed rate, we cycle through the opcodes that were written into the memory
and decode them using the program counter. Since each opcode is 2 bytes long while the program counter is only 1 byte,
to fetch the opcode we must combine the current, and next byte in memory with one another.
Then we decode each opcode using bitwise operators to read the most significant nibble first, and if needed the second
or third as well. Once we have deciphered the opcode, we execute the corresponding command (Each opcode can be seen and
explained on the chip-8 wiki) and increment the program counter by 2, to find the next pair of bytes.

**TECH STACK**
Language: C++
Libraries: SDL2
IDE's Used: Clion, Visual Studio

**KNOWN LIMITATIONS**
Currently, no known compatability issues besides being exclusive to windows due to lack of testing.
No known incomplete features besides minor performance enhancements for the display and/or audio.

**AI USAGE DISCLOSURE**
AI was used primarily for debugging and research purposes. However, the implementation of rate limiting on the
DXYN opcode and delayDisplay function were heavily assisted. Furthermore, minor use cases of AI may be present
as it was used as a learning resource specifically with the chip-8 emulator in mind, this could result in indirect
use of AI across some functionality. Lastly, I also used it as a guide to tell me which headers to include in this
README file.

**CREDITS AND REFERENCES**
https://austinmorlan.com/posts/chip8_emulator/#loading-a-rom
https://tobiasvl.github.io/blog/write-a-chip-8-emulator/?utm_source=chatgpt.com#fx55-and-fx65-store-and-load-memory
https://multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/
http://www.codeslinger.co.uk/pages/projects/chip8.html
https://wiki.libsdl.org/SDL2/CategoryAudio
https://en.wikipedia.org/wiki/CHIP-8
https://laurencescotford.net/2020/07/19/chip-8-on-the-cosmac-vip-drawing-sprites/

