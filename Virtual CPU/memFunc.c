/*
 * File:   memFunc.c
 * Author: B. Alfanous
 * Created on OCT 23, 2019
 */

#define _CRT_SECURE_NO_WARNINGS

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

	printf("\nEnter a file name: ");
	scanf("%s", &fileName);
	printf("\n");

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
		while (i < size) {
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

	// program crashes here, there's a bug that needs to be fixed
	write = fwrite(memory, 1, byte, fp);
	fclose(fp);
	printf("Bytes number that have been written: %d bytes (%x hex).\n", write, write);
}

/*
*   This function dumps data depending on what has been placed in memory by the load file function.
*   Args: memptr(points to the start of a section of memory)
*         offset (specifies the part to be displayed)
*	      length (specifies the number of bytes to be displayed)
*/
void MemDump(void* memory, unsigned offset, unsigned length) {
	int i = 0, j = 0;
	unsigned offset_hex = offset;
	unsigned offset_char = offset;
	// The number of header lines, divides length by 16 (in hex 0x10) 
	int header_num = length / 0x10;
	//length of the last header
	int last_header = length % 0x10;

 	if (offset > MEMORY_SIZE || offset < 0) {
		printf("\nInvalid offset, setting default offset to 0.");
		offset = 0;
	}

	if (header_num > 0) {
		for (j = 0; j < header_num; j++) {
			// Prints address
			printf("%04x\t", offset);

			// Prints memory contents in hex
			for (i = 0; i < 16; i++) {
				printf("%02x   ", ((unsigned char*)memory)[offset_hex]);
				offset_hex++;
			}
			printf("\n");
			// Prints memory contents
			printf("\t");
			for (i = 0; i < 16; i++) {
				if (isprint(((unsigned char*)memory)[offset_char]))
					printf("%c    ", ((unsigned char*)memory)[offset_char]);
				else
					printf(".   ");
				offset_char++;
			}
			offset += 0x10;
			printf("\n\n");
		}
		printf("\n\n");
	}

	if (last_header > 0) {
		printf("%04x\t", offset);
		for (i = 0; i < last_header; i++) {
			printf("%02x   ", ((unsigned char*)memory)[offset_hex]);
			offset_hex++;
		}
		printf("\n\n");
		printf("\t");
		for (i = 0; i < last_header; i++) {
			if (isprint(((unsigned char*)memory)[offset_char]))
				printf("%c    ", ((unsigned char*)memory)[offset_char]);
			else
				printf(".   ");
			offset_char++;
		}
		printf("\n\n");
	}
}

/*
* memory modify code ask the user to enter the starting address. Display the address and
* the existing value at that location and prompt the user for a new value. If the input is a period (.),
* exit, if it is a hex value, change the value and increment the address, else increment the address.
*/
void MemMod(void* memory, unsigned offset) {
	char value[3];
	//ensure offset is set within boundaries
	if (offset > MEMORY_SIZE || offset < 0) {
		printf("Invalid offset, setting to default offset 0.");
		offset = 0;
	}

	while (true) {
		//Displays info about current location
		printf("Current address:\t0x%04X\n", offset);
		printf("Value in memory in hex:\t(%02X)\n", ((unsigned char*)memory)[offset]);
		printf("Memory content:\t(%c)\n", ((unsigned char*)memory)[offset]);
		printf("Enter a 2 digit hex value to change this locaiton to, or . to exit:  ");
		//scanf("%x", &value);
		fgets(value, sizeof value, stdin);
		fgets(value, sizeof value, stdin);
		//checks if input is a . to exit
		if (strcmp(value, ".\n") == 0) {
			printf("Exiting modify\n");
			break;
		}

		//checks if values entered is valid
		//always prints out the first time, unsure why
		else if (!isxdigit(value[0]) || !isxdigit(value[1])) {
			printf("Enter a valid 2 digit hex number.\n\n");
			continue;
		}

		//if the new value is valid, place it in memory and move to next location
		else {
			sscanf(value, "%x", &value);
			printf("New value is: %c\n\n", value[0]);
			*(((unsigned char*)memory)+ offset) = value[0]; // doesn't store cprect value ??
			printf("Memory content:\t(%c)\n\n", ((unsigned char*)memory)[offset]);
			offset++;
		}
	}
}