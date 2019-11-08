/*
 * File:   vcpu.h
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef VCPU_H
#define VCPU_H
/*
	Data types: 
		32-bit words
		16-bit halfwords
		8-bit bytes

	Little-endian format:
		In little-endian format, the processor stores the least 
		significant byte of a word at the lowest-numbered byte, 
		and the most significant byte at the highest-numbered byte.
*/

// Constants (sizes)
#define MEMORY_SIZE 0x4000		// memory(buffer) size
#define MAX32		0xFFFFFFFF	// carryFlag overflow
#define REG_NUM		16			// Number of registers

// CCR Flags
bool SIGN;	// Sign Flag
bool ZERO;	// Zero Flag
bool STOP;	// Stop Flag
bool CARRY;	// Carry Flag

//#define IR_FLAG IR_FLAG //Flag to determine the active Instruction Regist

// Registers
int32_t IR;						//Instruction Register Combination of IR0 & IR1
#define IR0 IR >> 16;			// Instruction Register 0
#define IR1 IR & 0x000FFFF;		// Instruction Register 1
int32_t MAR;					// Memory Address Register - the address in main memory that is currently being read or written
int32_t MBR;					// Memory Buffer Register  - a two way register that holds data fetched from memory (and ready for the CPU to process) or data waiting to be stored in memory
int32_t ALU;					// Arithmetic logic unit 
int32_t CCR;					// Condition Code Register ???
int32_t REG[REG_NUM];			// Registers Array


/*
	The Stack Pointer (SP) is register R13. In Thread mode, 
	bit[1] of the CONTROL register indicates the stack pointer 
	to use:
		� 0 = Main Stack Pointer (MSP). This is the reset value.
		� 1 = Process Stack Pointer (PSP).
	On reset, the processor loads the MSP with the value 
	from address 0x00000000.
*/
#define SP REG[13]; // Stack Pointer
/* 
	LR REG stores the return information for subroutines, 
	function calls, and exceptions.
	Reset value is 0xFFFFFFFF. 
*/
#define LR REG[14]; // Link Register
/*
	The Program Counter (PC) is register R15. 
	It contains the current program address. On reset, 
	the processor loads the PC with the value of the reset vector,
	which is at address 0x00000004. Bit[0] of the value is loaded 
	into the EPSR T-bit at reset and must be 1.
*/
#define PC REG[15]; // Program Counter


// Functions Prototypes 
void help();
void run();
int LoadFile(char* memory, unsigned int max);
void WriteFile(void* memory);
void MemDump(void* memory, unsigned int offset, unsigned int length);
void MemMod(void* memory, unsigned int address);
int iscarry(unsigned long op1, unsigned long op2, unsigned C);
int reset();
void execute();
void cycle(void* memory);
void fetch(void* memory);
void displayRegs();
void trace(void* memory);

#endif /* VCPU_H */
