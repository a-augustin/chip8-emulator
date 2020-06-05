#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include "Arduino.h"
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include "Keypad.h"
#include <avr/pgmspace.h>
//#include <Adafruit_SSD1306.h>

#ifndef CHIP_H			//header guards
#define CHIP_H

#define MEM_SIZE 4095		//size of memory in bytes on Chip 8.
#define START_LOCATION 512	//program data can start being stored here 0x200	
#define REG_LOCATIONS 16	//0 - F
#define REFRESH_RATE (unsigned int) 17	//same as 60hz
#define SCREEN_W 64		//64 pixels wide
#define SCREEN_H 32		//32 pixels in height
#define SCALE 12
#define SPRITE_W 8		//all sprites mush be 8 pixels in width
#define MAX_SPRITE_H 15		//between 1 and 15 pixels in height
#define WHITE 0x1
#define BLACK 0x0
#define CHANGE_XOR 0x2
#define ROWS 4 //four rows
#define COLS 4 //three columns

#define RA8875_INT 20
#define RA8875_CS 49
#define RA8875_RESET 48

typedef struct screen{
	uint8_t binaryDisplay[SCREEN_W][SCREEN_H];
}screen;
struct subroutineStack{
		uint8_t size;
		struct node *head;
};
struct node{
	uint16_t address;
	struct node *next;
	int location;
};

typedef struct chip8{

	uint8_t dataMemory[MEM_SIZE];		//Eash instruction is 2 bytes 0x0000 to 0xFFFF
	uint8_t dataRegister[REG_LOCATIONS];	//Values in each reg are 1 byte. 0x00 to 0xFF
	uint16_t iRegister;			//16 bits
	uint16_t programCounter;			//2 bytes but only 12 bits will be used. 0x000 to 0xFFF b/c only 0xFFF memory locations. PC will probably start at 0x200.
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint8_t on;
	screen chipScreen;
	struct subroutineStack *stack; 

}chip8;

extern uint16_t opcode;

void chipInit(chip8 *);
void chipQuit(chip8 *);



#endif