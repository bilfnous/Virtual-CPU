/*
 * File:   execute.c
 * Author: B. Alfanous
 * Created on OCT 29, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include "vcpu.h"


 /*
 *   iscarry()- determine if carry is generated by addition: op1+op2+C
 *   C can only have value of 1 or 0.
 */
int iscarry(unsigned long op1, unsigned long op2, unsigned C) {
	if ((op2 == MAX32) && (C == 1))
		return(1); // special case where op2 is at MAX32
	return((op1 > (MAX32 - op2 - C)) ? 1 : 0);
}

/*
* Receives current instruciton and its type to be executed.
* REGs will be changed depending on the command passed by "cycle()".
*/
void execute(void* memory) {
	int i;

	if (LOAD_STORE) {

		if (LOAD_BIT) {
			/*Load Byte*/
			if (BYTE_BIT) {
				registers[RD] = loadReg(registers[RN], memory);
				registers[RD] = registers[RD] & BYTE_MASK;
			}
			/*Load DWORD*/
			else {
				registers[RD] = loadReg(registers[RN], memory);
			}
		}
		else {
			r_mem_buff_reg = registers[RD];
			/*Store one byte of reg into memory*/
			if (BYTE_BIT) {
				r_mem_addr_reg = registers[RN];
				r_mem_buff_reg = registers[RD];
				*((unsigned char*)memory + r_mem_addr_reg) = (unsigned char)r_mem_buff_reg & BYTE_MASK;
			}
			/*Store DWORD*/
			else {

				for (i = CYCLES - 1; i >= 0; i--) {
					*((unsigned char*)memory + r_mem_addr_reg++) = (unsigned char)(r_mem_buff_reg >> SHIFT_BYTE * i& BYTE_MASK);
				}
			}
		}
	}

	/* Branch inst.*/
	else if (BRANCH)
	{
		/* Jumps to a specified location determined form the inst.*/
		if (LINK_BIT) {
			// set the return address in the link reg.
			LR = PC;
		}
		// set PC to offset determined from the inst.
		PC = OFFSET12;
		ir = 0;
	}
	/* Cond. Branch inst.*/
	else if (COND_BRANCH)
	{
		// check condition code
		if (checkbran()) {
			// setting alu to the result of PC + FF
			alu = PC + (int)COND_ADDR;
			// if IR1 !=0 pc will be pc + alu - 3 + 1 
			if (ir != 0) {

				ir = 0;
				alu = alu + ~THUMB_SIZE + 1;
			}
			// set PC to result of alu
			PC = alu;
		}
	}
	/* Data processing*/
	else if (DATA_PROC)
	{
		/* ADD inst.*/
		if (DATA_ADD) {
			alu = registers[RD] + registers[RN];
			flags(alu);
			f_carryFlag = iscarry(registers[RD], ~registers[RN], 0);
			registers[RD] = alu;
		}
		/* SUB inst.*/
		else if (DATA_SUB) {
			alu = registers[RD] + ~registers[RN] + 1;
			flags(alu);
			f_carryFlag = iscarry(registers[RD], ~registers[RN], 1);
			registers[RD] = alu;
		}
	}

	else if (STOP) {
		f_stopFlag = 1; // Setting the stop flag
	}
}


// Function which determines the condition code suffixes for Cond.Branching
int checkbran() {
	// Equal is based on Zero flag = 1
	if (EQ) {
		if (f_zeroFlag) {
			return 1;
		}
	}
	// Not equal is based on Zero flag = 0
	else if (NE) {

		if (f_zeroFlag == 0) {
			return 1;
		}
	}
	// Higher or same based on carry = 1
	else if (CS) {

		if (f_carryFlag) {
			return 1;
		}
	}
	// Lower based on carry = 0
	else if (CC) {

		if (!f_carryFlag) {
			return 1;
		}
	}
	// Negative based on sign = 1
	else if (MI) {

		if (f_signFlag) {
			return 1;
		}
	}
	// Positive based on sign = 0
	else if (PL) {

		if (!f_signFlag) {
			return 1;
		}
	}
	// Higher based on carry = 1 and zero = 0
	else if (HI) {

		if (f_carryFlag && f_zeroFlag == 0) {
			return 1;
		}
	}
	// Lower based on carry = 0 or zero = 1
	else if (LS) {

		if (f_carryFlag == 0 ||f_zeroFlag) {
			return 1;
		}
	}
	// Alaways is the default when no suffix specified 
	else if (AL) {

		return 1;
	}

	return 0;
}


/*
* Reads the next command from memory and pushes it into IR and MBR registers.
* Keeps running until stop flag is set or PC program counter reaches end of memory.
*/
void fetch(void* memory) {

	ir = loadReg(PC, memory);
	/* PC + 1 instruction */

	int i;
	r_mem_addr_reg = mem_addr_reg;

	for (i = 0; i < CYCLES; i++, r_mem_addr_reg++)
	{
		r_mem_buff_reg = r_mem_buff_reg << SHIFT_BYTE;
		r_mem_buff_reg += *((unsigned char*)memory + r_mem_addr_reg);
	}

	// return r_mem_buff_reg;



	PC += REG_SIZE;
}


/* 
* Performs fetch instructions and executing them.
* Receive command from fetch and passes it to execute.
*/
void cycle() {
	/* Determine which IR to use via IR Active flag */
	if (ir == 0) {
		ir = 1;
		/* Fetch new set of instructions */
		fetch(memory);
		/* Current instruction is now IR0 */
		cir = IR0;
		execute(memory);
	}
	else {
		ir = 0;
		cir = IR1;
		execute(memory);
	}
}

/*
* Display all registers anf flags contents 
*/
void displayRegs() {
	printf("R0: %x\tR1: %x\tR2: %x\tR3: %x\n", REG[0], REG[1], REG[2], REG[3]);
	printf("R4: %x\tR5: %x\tR6: %x\tR7: %x\n", REG[4], REG[5], REG[6], REG[7]);
	printf("R8: %x\tR9: %x\tR10: %x\tR11: %x\tR12: %x\n", REG[8], REG[9], REG[10], REG[11], REG[12]);
	printf("R13(SP): %x\tR14(LR): %x\tR15(PC): %x\n", REG[13], REG[14], REG[15]);
	printf("MBR: %x\tMAR: %x\tIR0: %x\tIR1: %x\n", MBR, MAR, IR0, IR1);
	printf("S: %x\tZ: %x\tC: %x\tIR: %x\n", SIGN, ZERO, CARRY, IR);
}

/*
* Resets all registers and flags
*/
int reset() {
	int i;
	for (i = 0; i < REG_NUM; i++) {
		REG[i] = 0;
	}
	SIGN = false;
	ZERO = false;
	CARRY = false;
	STOP = false;
	IR = 0;
	IR0 = 0;
	IR1 = 0;
	MAR = 0;
	MBR = 0;
	ALU = 0;

	return 0;
}

void trace() {
	fetch();
	displayRegisters();
}
