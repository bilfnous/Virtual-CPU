/*
 * File:   interface.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#define _CRT_SECURE_NO_WARNINGS

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

		printf("\n>> ");
		scanf("%c", &c);

		switch (tolower(c)) {
		case 'd':
			printf("\nEnter offset in hex for memory dumb: ");
			scanf("%x", &offset);
			printf("\nEnter memory length in hex: ");
			scanf("%x", &length);
			MemDump(&memory, offset, length);
			break;
		case 'g':
			cycle(&memory);
			break;
		case 'l':
			loadFile = LoadFile(&memory, MEMORY_SIZE);
			if (loadFile == -1) {
				printf("\nFile could not be opened!\n");
			}
			else {
				printf("\nBytes number that have been read: %d bytes (%x hex).\n", loadFile, loadFile);
			}
			break;
		case 'm':
			printf("Enter the offset in memory (decimal): ");
			scanf("%d", &offset);
			MemMod(&memory, offset);
			break;
		case 'q':
			exit(EXIT_SUCCESS);
			break;
		case 'r':
			displayRegs();
			break;
		case 't':
			trace(&memory);
			break;
		case 'w':
			WriteFile(&memory);
			break;
		case 'z':
			reset();
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
