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
	printf("\n\n\nd dump memory\n");
	printf("g go – run the entire program\n");
	printf("l load a file into memory\n");
	printf("m memory modify\n");
	printf("q quit\n");
	printf("r display registers\n");
	printf("t trace – execute one instruction\n");
	printf("w write file\n");
	printf("z reset all registers to zero\n");
	printf("?, h display list of commands\n\n\n");
}

void run() {
	char c;

	while (1) {

		printf("\n>>");
		scanf("%c", &c);

		switch (tolower(c)) {
		case 'd':
			break;
		case 'g':
			break;
		case 'l':
			break;
		case 'm':
			break;
		case 'q':
			exit(EXIT_SUCCESS);
			break;
		case 'r':
			break;
		case 't':
			break;
		case 'w':
			break;
		case 'z':
			break;
		case 'h':
		case '?':
			help();
			break;
		default:
			printf("Invalid input, try again!!!\n");
		}
	}
}
