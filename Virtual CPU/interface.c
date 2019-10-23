/*
 * File:   interface.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#include <stdio.h>
#include <stdlib.h>
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

void run() {}
