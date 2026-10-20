#ifndef CHIP8_H
#define CHIP8_H

#include <array>
#include <vector>

#include "Display.h"

constexpr unsigned int START_ADDRESS = 0x200;

class chip8 {
public:
	using BYTE = unsigned char;
private:
	//Only influenced by opcode 0x00E0 (clear screen) and 0xDXYN (draw a sprite)
	bool drawFlag {};
	
	unsigned short opcode{};
	
	unsigned short I{};

	unsigned short pc{};
	//Simply used to store which level of the stack is currently being used
	unsigned short sp{};

	//Both count down at a rate of 60Hz (60 times a second) when set above 0.
	BYTE delay_timer{};
	BYTE sound_timer{};
	
	//used to remember the current location before a jump to a subroutine
	//is performed, always store pc in here before jumping
	std::array<uint16_t, 16> stack {};
	
	std::array<BYTE, 4096> memory{};
	
	std::array<BYTE, 16> V{};
	
	std::array<BYTE, 16> keys{};
	
	std::array<BYTE, 64 * 32> gfx{};
	

	
	
	std::array<BYTE, 80> font{  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
									0x20, 0x60, 0x20, 0x20, 0x70, // 1
									0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
									0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
									0x90, 0x90, 0xF0, 0x10, 0x10, // 4
									0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
									0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
									0xF0, 0x10, 0x20, 0x40, 0x40, // 7
									0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
									0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
									0xF0, 0x90, 0xF0, 0x90, 0x90, // A
									0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
									0xF0, 0x80, 0x80, 0x80, 0xF0, // C
									0xE0, 0x90, 0x90, 0x90, 0xE0, // D
									0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
									0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};
public:
	chip8();
	
	bool getDrawFlag() const {return drawFlag;}
	void setDrawFlag( const bool state = false) {drawFlag = state;}
	std::array<BYTE, 64*32> getGFX() const {return gfx;}
	
	void initialize();
	void loadFont();
	void loadGame(char const* file);
	void emulateCycle(const Display& graphics); //Still gotta implement ocpodes
	void setKeys(); //Not Working
	void draw(BYTE X, BYTE Y, BYTE N);
	void updateTimers();

};



#endif
