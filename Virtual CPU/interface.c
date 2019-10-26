/*
 * File:   interface.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "vcpu.h"

void help() {
	printf("\n* d - dump memory\n");
	printf("* g - go - run the entire program\n");
	printf("* l - load a file into memory\n");
	printf("* m - memory modify\n");
	printf("* q - quit\n");
	printf("* r - display registers\n");
	printf("* t - trace - execute one instruction\n");
	printf("* w - write file\n");
	printf("* z - reset all registers to zero\n");
	printf("* ?, h - display list of commands\n");
}

void run() {
	char c;
	int loadFile = 0;
	char memory[MEMORY_SIZE];
	unsigned int offset, length, address;

	while (1) {

		printf("\n>>");
		scanf("%c", &c);

		switch (tolower(c)) {
		case 'd':
			printf("\nEnter offset in bytes for memory dumb: ");
			scanf("%u", &offset);
			printf("\nEnter memory length in bytes: ");
			scanf("%u", &length);
			MemDump(&memory, offset, length);
			break;
		case 'g':
			break;
		case 'l':
			loadFile = LoadFile(&memory, MEMORY_SIZE);
			if (loadFile == -1) {
				printf("\nFile could not open!\n");
			}
			else {
				printf("\nBytes number that have been read: %d bytes (%x hex).\n", loadFile, loadFile);
			}
			break;
		case 'm':
			printf("Enter the offset in memory (decimal):  ");
			scanf("%d", &offset);
			MemMod(&memory, offset);
			break;
		case 'q':
			exit(EXIT_SUCCESS);
			break;
		case 'r':
			break;
		case 't':
			break;
		case 'w':
			WriteFile(&memory);
			break;
		case 'z':
			break;
		case 'h':
		case '?':
			help();
			break;
		default:
			printf("\nInvalid input, try again!!!\n");
		}
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
		fflush(stdin);
	}
}
