/*
 * File:   vcpu.h
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#ifndef VCPU_H
#define VCPU_H


// Constants (sizes)
#define MEMORY_SIZE 16000		// memory(buffer) size
#define MAX32		0xFFFFFFFF	// carryFlag overflow
#define REG_NUM		16			// Number of registers
#define REG_SIZE	0x10		// Register size 16 bits
#define BYTE_SIZE 	0x1

#define LINE_BREAK  0x6

#define THUMB_SIZE  0x2 // instruction size (16 bit)
#define RF_SIZE   	0x10//??????? Register size = 16-bits
//#define REG_SIZE  	0x4	// ??????to move to the next inst.

// Flags
int f_signFlag;
int f_zeroFlag;
int f_stopFlag;
int f_carryFlag;

// Special Registers in Registers Offsets
#define RF_SP   0xD
#define RF_LR   0xE
#define RF_PC   0xF
#define SP      registers[RF_SP]		// Stack Pointer 
#define LR      registers[RF_LR]		// Link Register
#define PC      registers[RF_PC]		// Program Counter

// Instruction Registers 
#define IR0 (unsigned)ir >> 16 		// set ir0 to the lower 16 bits of the 32-bit inst.
#define IR1 ir & 0xFFFF 			// set ir1 to the upper 16 bits of the 32-bit inst.

// Instruction Formats 
#define FORMAT		  (unsigned)cir >> 13	// shift until the last 3-MSbits EX: 110
#define LOAD_STORE 	FORMAT == 0x1 			// to check for Load or Store inst.
#define STOP 	  	  cir == 0xE000		    // to check for stop inst.
#define COND_BRANCH FORMAT == 0x4		    // to check for COND_BRANCH inst.
#define BRANCH      FORMAT == 0x6		    // to check for BRANCH inst.
#define DATA_PROC   FORMAT == 0x0 			// to check for Data Processing inst.

// Data Processing OpCodes
#define DATA_SUB 0x2 == OPERATION 		// to check for SUB inst.
#define DATA_ADD 0x4 == OPERATION 		// to check for ADD inst.

// Instruction Fields
#define RN			((cir >> 4) & 0xF)		// to get the reg 1 number from the inst.
#define RD			 cir & 0xF 				// to get the reg 2 number from the inst.
#define BYTE_BIT	((cir >> 10) & 0x1)		// to check if should store/load single byte 
#define LOAD_BIT	((cir >> 11) & 0x1)		// to check for load inst.
#define CONDITION   ((cir >> 8) & 0xF)		// to check which code is selected for the COND_BRANCH
#define LINK_BIT    ((cir >> 12) & 0x1)		// to check the 13th bit of the cir if set  
#define OFFSET12    cir & 0xFFF 			// to get the offset location 
#define COND_ADDR   cir & 0xFF 				// to get the offset location for COND_BRANCH
#define OPERATION   ((cir >> 8) & 0xF)		// to check if SUB or ADD selected from the inst.

/* 
*  Branch Condition Codes Suffixes
*  Each one checks which code is
*  selected from the inst.
*/
#define EQ 0x0 == CONDITION
#define NE 0x1 == CONDITION
#define CS 0x2 == CONDITION
#define CC 0x3 == CONDITION
#define MI 0x4 == CONDITION 
#define PL 0x5 == CONDITION
#define HI 0x8 == CONDITION
#define LS 0x9 == CONDITION
#define AL 0xE == CONDITION

// Registers
int r_mem_addr_reg;			// Memory Address Register 
int r_mem_buff_reg;			// Memory Buffer Register 
int registers[REG_SIZE];	// Registers  Array
int ir;
int alu;	// Arithmetic logic unit 

int cir;	// Unoffical register for current instructin

// Bit Shifiting, Byte Masks, Extensions
#define CYCLES		4
#define SHIFT_BYTE	8	// for shifting by a byte
#define MSB32MASK 	0x80000000	// Mask for MSB if 32-bits
#define MSBTOLSB  	31			// Shift bits from MSB to LSB
#define BYTE_MASK 	0xFF 

// Functions Prototypes 
void help();
void run();
int LoadFile(char* memory, unsigned int max);
void WriteFile(void* memory);
void MemDump(void* memory, unsigned int offset, unsigned int length);
void MemMod(void* memory, unsigned int address);
int iscarry(unsigned long op1, unsigned long op2, unsigned C);
int loadReg(int mem_addr_reg, void* memory);
void execute(void* memory);

#endif /* VCPU_H */
