/*
 * File:   vcpu.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "vcpu.h"

int main(int argc, char** argv) {

	printf("\nVirtual CPU\n\n");
	help();
	run();

	return (EXIT_SUCCESS);
}