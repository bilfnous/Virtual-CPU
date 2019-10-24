/*
 * File:   memFunc.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "vcpu.h"

 /*
 *   LoadFile is a function that prompts the user to enter file name to be loaded into a buffer.
 *   Checks if file will be truncated(file size bigger than buffer size).
 *   Reads a max specified number of bytes from file.(prevent overflow)
 *   Displays contents read and number of bytes read in decimal and hex.
 *   Returns number of bytes read in decimal.
 *   Returns -1 if file can't open
 */
int LoadFile(void* memory, unsigned int max) {
	FILE* fp;
	char fileName[32];
	int read = 0;
	int size = 0;

	printf("Enter a file name to be loaded: ");
	scanf("%s", &fileName);

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("\nCan't open file!!\n");
		return -1;
	}

	/*get file's size*/
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	if (size > max) {
		printf("!Warning! - File has been truncated!\n");
	}

	/*read file's contents and place them into memory*/
	read = fread(memory, 1, max, fp);
	if (read <= 0) {
		printf("!Warning! - File is empty!\n");
	}
	else {
		printf("%s\n", memory);
	}

	fclose(fp);
	printf("Bytes number that have been read: %d bytes (%x hex).\n", read, read);
	return read;
}

void WriteFile(void* memory) {}
