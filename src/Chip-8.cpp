#include "Chip-8.h"
#include "Helper.h"
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iostream>




chip8::chip8()
{
    pc = 0x200;
    stack.resize(16);
    loadFont();
}

void chip8::initialize()
{
    //Reset States
    pc = 0x200;
    I = 0x0;
    delay_timer = {};
    sound_timer = {};
    sp = {};
    opcode = {};
    
    
    //Clearing out
    std::fill(std::begin(memory), std::end(memory), 0);
    std::fill(std::begin(gfx), std::end(gfx), 0);
    std::fill(std::begin(key), std::end(key), 0);
    std::fill(std::begin(V), std::end(V), 0);
    std::fill(std::begin(stack), std::end(stack), 0);
    
    loadFont();
}

void chip8::loadFont()
{
    //Assign font to 050-09F in memory (which is before 0x200)
    for (unsigned int i{ 0 }; i < font.size(); ++i) {
        memory[0x050 + i] = font[i];
    }
    
}

//Code is from Austin Morlan:
//https://austinmorlan.com/posts/chip8_emulator/#loading-a-rom (ty)
void chip8::loadGame(char const* filename)
{
    // Open the file as a stream of binary and move the file pointer to the end
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        // Get size of file and allocate a buffer to hold the contents
        std::streampos size = file.tellg();
        char* buffer = new char[size];

        // Go back to the beginning of the file and fill the buffer
        file.seekg(0, std::ios::beg);
        file.read(buffer, size);
        file.close();

        // Load the ROM contents into the Chip8's memory, starting at 0x200
        for (long i = 0; i < size; ++i)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        // Free the buffer
        delete[] buffer;
    }
}

void chip8::setKeys()
{
    PASS;
}

void chip8::emulateCycle()
{
    //Fetch Opcode
    unsigned short res {memory[pc]};
    res <<= 8;
    opcode = res | memory[pc + 1];
    pc += 2;
    
    //Decode Opcode
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
                case 0x00E0:
                    clearScreen(); //not implemented
                    break;
                case 0x00EE:
                    //Left blank
                    break;
                default: 
                    break;
            }
            break;
        case 0x1000:
            pc = (opcode & 0x0FFF);
            break;
        case 0x6000:
            V[(opcode >> 8) & 0x0F] = (opcode & 0x00FF);
            break;
        case 0x7000:
            V[(opcode >> 8) & 0x0F] += (opcode & 0x00FF);
            break;
        case 0xA000:
            I = (opcode & 0x0FFF);
            break;
        case 0xD000:
            draw( (opcode >> 8) & 0x0F,  (opcode >> 4) & 0x00F,  (opcode & 0x000F));
            break;
        default:
            break;
    }
    
    //Update timers
    if(delay_timer > 0)
        --delay_timer;
 
    if(sound_timer > 0)
    {
        if(sound_timer == 1)
            printf("BEEP!\n"); // replace with actual noise
        --sound_timer;
    } 
}