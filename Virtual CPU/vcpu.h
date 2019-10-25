/*
 * File:   vcpu.h
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#ifndef VCPU_H
#define VCPU_H


 // Constants 
#define MEMORY_SIZE 16000


// Functions Prototypes 
void help();
void run();
int LoadFile(char* memory, unsigned int max);
void WriteFile(void* memory);
void MemDump(void* memory, unsigned int offset, unsigned int length);
int MemMod(void* memory, unsigned int address);

#endif /* VCPU_H */
