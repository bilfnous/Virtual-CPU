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
#define REG_NUM		0x10		// Number of registers

// CCR Flags
bool SIGN;	  // Sign Flag
bool ZERO;	  // Zero Flag
bool STOP_F;  // Stop Flag
bool CARRY;	  // Carry Flag

//#define IR_FLAG IR_FLAG //Flag to determine the active Instruction Regist

// Registers
// CIR or IR Current Instruction Register - a temporary holding ground for the instruction that has just been fetched from memory
int32_t IR;						// Instruction Register Combination of IR0 & IR1
int16_t IR0;					// Instruction Register 0
int16_t IR1;					// Instruction Register 1
int32_t MAR;					// Memory Address Register - the address in main memory that is currently being read or written
int32_t MBR;					// Memory Buffer Register  - a two way register that holds data fetched from memory (and ready for the CPU to process) or data waiting to be stored in memory
int32_t ALU;					// Arithmetic logic unit 
int32_t CCR;					// ??? Condition Code Register CCR Flags
int32_t RD;						// RD: Destination register
int32_t RN;						// RN : An operand in a register for an arithmetic operation.
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
#define SP REG[0x0D] // Stack Pointer
/* 
	LR REG stores the return information for subroutines, 
	function calls, and exceptions.
	Reset value is 0xFFFFFFFF. 
*/
#define LR REG[0x0E] // Link Register
/*
	The Program Counter (PC) is register R15. 
	It contains the current program address. On reset, 
	the processor loads the PC with the value of the reset vector,
	which is at address 0x00000004. Bit[0] of the value is loaded 
	into the EPSR T-bit at reset and must be 1.
*/
#define PC REG[0x0F] // Program Counter

// Instructions
/* Check if instruction fetched is equal to one of the predefined instructions. */
#define LOAD_STORE	0x10	
#define HALFWORD	0x01
#define WORD		0x02

#define DATA_PROC	0x30
#define CON_BRANCH	0x40
#define UN_BRANCH	0x50
#define STOP_I		0x00

// Data processing instructions
#define AND 0x31  // Logical bit-wise AND Rd := Rn AND Op2
#define OR	0x32  // Logical bit-wise OR Rd := Rn OR Op2
#define	EOR 0x33  // Logical bit-wise exclusive OR Rd := Rn EOR Op2
#define SUB 0x34  // Subtract Rd := Rn -Op2
#define ADD 0x35  // Add Rd := Rn + Op2
#define ADC 0x36  // Add with carry Rd := Rn + Op2 + C
#define SBC 0x37  // Subtract with carry Rd := Rn -Op2 + C -1
#define MOV 0x38  // Move Rd := Op2

// Condition Branch Codes
#define EQ 0x41  // equal - zero flag set
#define NE 0x42  // not equal - zero flag clear
#define GT 0x43  
#define LT 0x44  
#define GE 0x45  
#define LE 0x46  

// Functions Prototypes 
void help();
void run();
int LoadFile(char* memory, unsigned int max);
void WriteFile(void* memory);
void MemDump(void* memory, unsigned offset, unsigned length);
void MemMod(void* memory, unsigned address);
int iscarry(unsigned long op1, unsigned long op2, unsigned C);
void reset();
void execute(void* memory);
void cycle(void* memory);
void fetch(void* memory);
void displayRegs();
void trace(void* memory);

#endif /* VCPU_H */
