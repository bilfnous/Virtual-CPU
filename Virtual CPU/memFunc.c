/*
 * File:   memFunc.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "vcpu.h"

 /*
 *   LoadFile is a function that prompts the user to enter file name to be loaded into a buffer.
 *   Checks if file will be truncated(file size bigger than buffer size).
 *   Reads a max specified number of bytes from file.(prevent overflow)
 *   Displays contents read and number of bytes read in decimal and hex.
 *   Returns number of bytes read in decimal.
 *   Returns -1 if file can't open
 */
int LoadFile(char* memory, unsigned int max) {
	FILE* fp;
	char fileName[32];
	int read = 0;
	int size = 0;

	printf("Enter a file name: ");
	scanf("%s", &fileName);

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		return -1;
	}

	/*get file's size*/
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	if (size > max) {
		printf("!Warning! - File has been truncated!\n");
		read = fread(memory, 1, max, fp);
	}
	else {
		/*read file's contents and place them into memory*/
		read = fread(memory, 1, size, fp);
	}

	if (read <= 0) {
		printf("!Warning! - File is empty!\n");
	}
	else {
		int i = 0;
		while (i <= size) {
			printf("%c", memory[i]);
			i++;
		}
		printf("\n");
	}

	fclose(fp);
	return read;
}


/*
*   WriteFile is a function that prompts the user to enter file name.
*   If the file already exists, it will be overridden.
*   The user will be asked to enter the number of bytes to be written to the file.
*   A file will be created, and the data entered will be written to the file from the buffer.
*   Checks if file could be opened; if not, it returns -1.
*/
void WriteFile(void* memory) {
	FILE* fp;
	char fileName[32];
	short int byte = 0, write = 0;
	char ch;

	printf("Enter a file name to be created: ");
	scanf("%s", &fileName);
	fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("\nCan't open file!!\n");
		return -1;
	}

	printf("\nEnter number of bytes to be written to the file: ");
	do {
		scanf("%d", &byte);
		if (byte > MEMORY_SIZE)
			printf("\nError!!!...File size should be less than %dK Bytes!!\n", MEMORY_SIZE);
	} while (byte > MEMORY_SIZE);

	write = fwrite(memory, 1, byte, fp);
	fclose(fp);
	printf("Bytes number that have been written: %d bytes (%x hex).\n", write, write);
}

/*
*   The interface code will prompt the user for an offset and length to be dumped from the CPU memory.
*   The data dumped will depend on what has been placed in memory by the load file function.
*   Args: memptr(points to the start of a section of memory)
*         offset (specifies the part to be displayed)
*	      length (specifies the number of bytes to be displayed)
*/
void MemDump(void* memory, unsigned int offset, unsigned int length) {
	int i = 0, x = 0, y = 0, z = 16;
	int a = 0, hex = 0;

	for (i = 0; i < length; i++) {
		a = 0;
		x++;
		if (x == 0 || x == 16) {
			for (a = 0; a < 16; a++) {
				printf("%x  ", hex);
				hex++;
			}
		}
		if (x == 16) {
			printf("\n");
			x = 0;
			z = 16;
			for (y = 0; y < 16; y++) {
				if (isprint(((unsigned char*)memory)[offset - z]))
					printf("%c   ", ((unsigned char*)memory)[offset - z]);
				else
					printf(".   ");
				z--;
			}
			printf("\n\n");
		}
		offset++;
	}
}
