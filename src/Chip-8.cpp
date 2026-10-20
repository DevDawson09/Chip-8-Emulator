#include "Chip-8.h"
#include <algorithm>
#include <fstream>
#include <cassert>
#include <iostream>
#include <SDL.h>
#include <SDL_events.h>

#include "Helper.h"


chip8::chip8()
{
    initialize();
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
    std::fill(std::begin(keys), std::end(keys), 0);
    std::fill(std::begin(V), std::end(V), 0);
    std::fill(std::begin(gfx), std::end(gfx), 0);
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
    } else {
        std::cerr << "couldn't open ROM" << '\n';
    }
}


void chip8::draw(const BYTE X, const BYTE Y, const BYTE N)
{
    const int xPos {V[X] % 64};
    const int yPos {V[Y] % 32};

    V[0xF] = 0;

    for ( int row {0} ; row < N; ++row) {
        if (yPos + row >= 32)
            break;

        int spriteData {memory[I + row]};

        for (int column {0}; column < 8; ++column) {
            if (xPos + column >= 64)
                break;

            const int screenIndex {(yPos + row)*64 + (xPos + column)};
            const int spritePixel {(spriteData >> (7-column)) & 1};

            if (spritePixel == 1 && gfx[screenIndex] == 1)
                V[0xF] = 1;

            gfx[screenIndex] ^= spritePixel;
        }
    }

    setDrawFlag(true);
}

void chip8::setKeys()
{
    SDL_Event event {};

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        keys[0x1] = 1;
                        break;
                    case SDLK_2:
                        keys[0x2] =1;
                        break;
                    case SDLK_3:
                        keys[0x3] = 1;
                        break;
                    case SDLK_4:
                        keys[0xC] = 1;
                        break;
                    case SDLK_q:
                        keys[0x4] = 1;
                        break;
                    case SDLK_w:
                        keys[0x5] = 1;
                        break;
                    case SDLK_e:
                        keys[0x6] = 1;
                        break;
                    case SDLK_r:
                        keys[0xD] = 1;
                        break;
                    case SDLK_a:
                        keys[0x7] = 1;
                        break;
                    case SDLK_s:
                        keys[0x8] = 1;
                        break;
                    case SDLK_d:
                        keys[0x9] = 1;
                        break;
                    case SDLK_f:
                        keys[0xE] = 1;
                        break;
                    case SDLK_z:
                        keys[0xA] = 1;
                        break;
                    case SDLK_x:
                        keys[0x0] = 1;
                        break;
                    case SDLK_c:
                        keys[0xB] = 1;
                        break;
                    case SDLK_v:
                        keys[0xF] = 1;
                        break;
                    default:
                        std::cerr << "No input" << '\n';
                        break;

                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_1:
                        keys[0x1] = 0;
                        break;
                    case SDLK_2:
                        keys[0x2] =0;
                        break;
                    case SDLK_3:
                        keys[0x3] = 0;
                        break;
                    case SDLK_4:
                        keys[0xC] = 0;
                        break;
                    case SDLK_q:
                        keys[0x4] = 0;
                        break;
                    case SDLK_w:
                        keys[0x5] = 0;
                        break;
                    case SDLK_e:
                        keys[0x6] = 0;
                        break;
                    case SDLK_r:
                        keys[0xD] = 0;
                        break;
                    case SDLK_a:
                        keys[0x7] = 0;
                        break;
                    case SDLK_s:
                        keys[0x8] = 0;
                        break;
                    case SDLK_d:
                        keys[0x9] = 0;
                        break;
                    case SDLK_f:
                        keys[0xE] = 0;
                        break;
                    case SDLK_z:
                        keys[0xA] = 0;
                        break;
                    case SDLK_x:
                        keys[0x0] = 0;
                        break;
                    case SDLK_c:
                        keys[0xB] = 0;
                        break;
                    case SDLK_v:
                        keys[0xF] = 0;
                        break;
                    default:
                        std::cerr << "No input" << '\n';
                        break;

                }
                break;
            case SDL_QUIT:
                exit(0);
                break;

            default:
                break;
        }
    }
}

void chip8::emulateCycle(const Display& graphics)
{

    //Fetch Opcode
    unsigned short res {memory[pc]};
    res <<= 8;
    opcode = res | memory[pc + 1];
    pc += 2;
    
    const int VX {(opcode >> 8) & 0x0F};
    const int VY {(opcode >> 4) & 0x00F};
    //Decode Opcode
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
                case 0x00E0:
                    std::fill(std::begin(gfx), std::end(gfx), 0);
                    clearScreen(graphics);
                    break;
                case 0x00EE:
                    if (sp != 0)
                        pc = stack[--sp];
                    break;
                default:
                    break;
            }
            break;
        case 0x1000:
            pc = (opcode & 0x0FFF);
            break;
        case 0x2000:
            stack[sp++] = pc;
            pc = (opcode & 0x0FFF);
            break;
        case 0x3000:
            if (V[VX] == (opcode & 0x00FF))
                pc += 2;
            break;
        case 0x4000:
            if (V[VX] != (opcode & 0x00FF))
                pc += 2;
            break;
        case 0x5000:
            if ((V[VX]) == (V[VY]))
                pc += 2;
            break;
        case 0x9000:
            if ((V[(opcode >> 8)  & 0x0F]) != (V[VY] ))
                pc += 2;
            break;
        case 0x6000:
            V[VX] = (opcode & 0x00FF);
            break;
        case 0x7000:
            V[VX] += (opcode & 0x00FF);
            break;
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0000:
                    V[VX] = V[VY];
                    break;
                case 0x0001:
                    V[VX] |= V[VY];
                    break;
                case 0x0002:
                    V[VX] &= V[VY];
                    break;
                case 0x0003:
                    V[VX] ^= V[VY];
                    break;
                case 0x0004: {
                    BYTE flag {};
                    if ((V[VX] + V[VY]) >= 255)
                        flag = 1;
                    else
                        flag = 0;

                    V[VX] += V[VY];
                    V[0xF] = flag;
                    break;
                }
                case 0x0005: {
                    const BYTE yValue {V[VY]};
                    const BYTE xValue {V[VX]};

                    const int result { xValue - yValue};
                    const int flag { (xValue >= yValue) ? 1 : 0 };
                    V[VX] = result;
                    V[0xF] = flag;
                    break;
                }
                case 0x0007:
                    V[VX] = V[VY] - V[VX];
                    if (V[VY] >= V[VX])
                        V[0xF] = 1;
                    else
                        V[0xF] = 0;
                    break;
                case 0x0006: {
                    BYTE flag {};
                    if ((V[VX] & 1) == 1)
                        flag = 1;
                    else
                        flag = 0;
                    V[VX] >>= 1;
                    V[0xF] = flag;
                    break;
                }
                case 0x000E: {
                    BYTE flag {};
                    if ((V[VX] & 0x80) == 0x80)
                        flag = 1;
                    else
                        flag = 0;
                    V[VX] <<= 1;
                    V[0xF] = flag;
                    break;
                }
                default:
                    break;
            }
            break;
        case 0xB000:
            pc = 0x0FFF + V[0x0];
            break;
        case 0xA000:
            I = (opcode & 0x0FFF);
            break;
        case 0xC000:
            //Not implemented yet (random byte required)
            break;
        case 0xD000:
            draw( VX,  VY,  (opcode & 0x000F));
            break;
        case 0xE000:
            switch (opcode & 0x000F) {
                case 0x000E:
                    if (keys[V[(VX)]] == 1)
                        pc += 2;
                    break;
                case 0x0001:
                    if (keys[V[(VX)]] != 1)
                        pc += 2;
                    break;
                default:
                    break;
            }
            break;
        case 0xF000:
            switch (opcode & 0x000F) {
                case 0x0007:
                    V[(VX)] = delay_timer;
                    break;
                case 0x0008:
                    sound_timer = V[(VX)];
                    break;
                case 0x000E:
                    I += V[(VX)];
                    break;
                case 0x000A: {
                    bool found {false};
                    updateTimers();
                    for (int i {0}; i < 16; ++i) {
                        if (keys[i] == 1) {
                            V[VX] = i;
                            pc += 2;
                            found = true;
                        }
                    }
                    setKeys();
                    if (found != true)
                        pc -= 2;
                    break;
                }
                case 0x0009:
                    I = 0x050 + (V[VX] * 5);
                    break;
                case 0x0003: {
                    const int number {V[VX]};
                    memory[I + 2] = number % 10;
                    memory[I + 1] =(number % 100) / 10;
                    memory[I] = number / 100;
                    break;
                }
                case 0x0005:
                    switch ((opcode >> 4) & 0x00F) {
                        case 0x005:
                            for (int i {0}; i <= VX; ++i) {
                                memory[I + i] = V[i];
                            }
                            break;
                        case 0x001:
                            delay_timer = V[(VX)];
                            break;
                        case 0x006:
                            for (int i {0}; i <= VX; ++i) {
                                V[i] = memory[I+i];
                            }
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
                }
            break;

        default:
            break;
    }
    
    updateTimers();
}

void chip8::updateTimers() {
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