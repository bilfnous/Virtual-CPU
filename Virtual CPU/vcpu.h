/*
 * File:   vcpu.h
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef VCPU_H
#define VCPU_H

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
int32_t MAR;	// Memory Address Register 
int32_t MBR;	// Memory Buffer Register 
int32_t IR;			//Instruction Register Combination of IR0 & IR1
int16_t IR0, IR1;	// Instruction Register 0 and 1
int32_t ALU;		// Arithmetic logic unit 
int32_t registers[REG_NUM];	// Registers  Array

#define SP registers[13]; // Stack Pointer
#define LR registers[14]; // Link Register
#define PC registers[15]; // Program Counter


// Functions Prototypes 
void help();
void run();
int LoadFile(char* memory, unsigned int max);
void WriteFile(void* memory);
void MemDump(void* memory, unsigned int offset, unsigned int length);
void MemMod(void* memory, unsigned int address);
int iscarry(unsigned long op1, unsigned long op2, unsigned C);
int loadReg(int mem_addr_reg, void* memory);
int reset();
void execute(void* memory);

#endif /* VCPU_H */
