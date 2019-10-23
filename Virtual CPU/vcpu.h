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
int LoadFile(void* memory, unsigned int max);
void WriteFile(void* memory);

#endif /* VCPU_H */
