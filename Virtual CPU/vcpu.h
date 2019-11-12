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

		Rd: Destination register
		Rn: An operand in a register for an arithmetic operation.
*/

// Constants (sizes)
#define MEMORY_SIZE 0x4000		// memory(buffer) size
#define MAX32		0xFFFFFFFF	// carryFlag overflow
#define REG_NUM		0x10		// Number of registers

// CCR Flags
bool SIGN;	// Sign Flag
bool ZERO;	// Zero Flag
bool STOP;	// Stop Flag
bool CARRY;	// Carry Flag

//#define IR_FLAG IR_FLAG //Flag to determine the active Instruction Regist

// Registers
// CIR or IR Current Instruction Register - a temporary holding ground for the instruction that has just been fetched from memory
int32_t IR;						// Instruction Register Combination of IR0 & IR1
#define IR0 IR >> 0x10;			// Instruction Register 0
#define IR1 IR & 0x000FFFF;		// Instruction Register 1
int32_t MAR;					// Memory Address Register - the address in main memory that is currently being read or written
int32_t MBR;					// Memory Buffer Register  - a two way register that holds data fetched from memory (and ready for the CPU to process) or data waiting to be stored in memory
int32_t ALU;					// Arithmetic logic unit 
int32_t CCR;					// ??? Condition Code Register CCR Flags
int32_t REG[REG_NUM];			// Registers Array

/*
	The Stack Pointer (SP) is register R13. In Thread mode, 
	bit[1] of the CONTROL register indicates the stack pointer 
	to use:
		• 0 = Main Stack Pointer (MSP). This is the reset value.
		• 1 = Process Stack Pointer (PSP).
	On reset, the processor loads the MSP with the value 
	from address 0x00000000.
*/
#define SP REG[0xD]; // Stack Pointer
/* 
	LR REG stores the return information for subroutines, 
	function calls, and exceptions.
	Reset value is 0xFFFFFFFF. 
*/
#define LR REG[0xE]; // Link Register
/*
	The Program Counter (PC) is register R15. 
	It contains the current program address. On reset, 
	the processor loads the PC with the value of the reset vector,
	which is at address 0x00000004. Bit[0] of the value is loaded 
	into the EPSR T-bit at reset and must be 1.
*/
#define PC REG[0xF]; // Program Counter

// Instructions
/* Check if instruction fetched is equal to one of the predefined instructions. */
#define LOAD_STORE	0x11 & IR0
#define DATA_PROC	0x12 & IR0
#define CON_BRANCH	0x13 & IR0
#define UN_BRANCH	0x14 & IR0
#define STOP		0x15 & IR0

// Data processing instructions
#define AND 0x0
#define OR	0xC
#define	EOR 0x1
#define SUB 0x2
#define ADD 0x4
#define ADC 0x5
#define SBC 0x6
#define CMP 0xA
#define CMN 0xB
#define MOV 0xD

// Condition Branch Codes
#define EQ 0x0
#define NE 0x1
#define CS 0x2
#define CC 0x3
#define MI 0x4
#define PL 0x5
#define HI 0x8
#define LS 0x9
#define AL 0xE


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
