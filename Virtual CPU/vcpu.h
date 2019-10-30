/*
 * File:   vcpu.h
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#ifndef VCPU_H
#define VCPU_H


 // Constants 
#define MEMORY_SIZE 16000 // memory(buffer) size
#define MAX32 4
#define REG_NUM 16 // Number of registers


// Functions Prototypes 
void help();
void run();
int LoadFile(char* memory, unsigned int max);
void WriteFile(void* memory);
void MemDump(void* memory, unsigned int offset, unsigned int length);
void MemMod(void* memory, unsigned int address);
int iscarry(unsigned long op1, unsigned long op2, unsigned C);

#endif /* VCPU_H */
