/*
 * File:   execute.c
 * Author: B. Alfanous
 * Created on OCT 29, 2019
 */

#include "vcpu.h"



/*
	- Each cycle consists of fetching, decoding and executing an instruction. 

	* PC has address of next instruction
	* PC copied to the MAR
	* Lookup MAR and get contents. Copy contents into the MBR
	* Copy MBR contents into the IR if the content is an instruction 
	* Each instruction is divided into two parts: 
		1. OP code or operation code, this is the command the cpu will carry out.
		2. Operand data to be operated on.
	* PC is then incremented by 1
	* The instruction is decoded and then executed
	* Repeat
*/



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
* Reads the next command from memory and pushes it into IR and MBR registers.
* Keeps running until stop flag is set or PC program counter reaches end of memory.
*/
void fetch(void* memory) {
	// load first address of memory
	PC = &memory;

	// move the address that is currently being read into MAR register
	MAR = PC;

	//Move memory contents at MAR into MBR
	MBR = *((unsigned char*)memory + MAR);
	
	//Move MBR into the Instruction Registers
	IR = MBR;
	IR0 = IR & 0x00FF;	// IR0 holds instruction
	IR1 = IR & 0xFF00;	// IR1 holds operand

	// Increment programming counter into next position
	PC++; 
}

/*
* Fetches instructions and executes them.
* Commands are passed from fetch to execute using registers.
*/
void cycle(void* memory) {
	while(STOP_F == false) {
		fetch(&memory);
		execute();
	}
}

/*
* Receives current instruciton and its type to be executed.
* REGs will be changed depending on the command passed by "cycle()".
*/
void execute() {
	if (LOAD_STORE) {
		if (LOAD) {
			if (HALFWORD) {
			}
			else if (WORD) {
			}
		
		}
		else if (STORE) {
			if (HALFWORD) {
			}
			else if (WORD) {
			}
		}

	}
	else if (DATA_PROC) {
	
	}
	else if (CON_BRANCH) {
	
	}
	else if (UN_BRANCH) {
	
	}
	else if (STOP_I) {
		printf("\n\n*** End Of Program ***\n\n");
		STOP_F = true;
	}
	else {
		printf("\n\nInstruction Does Not Exists!!!\n\n");
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
void reset() {
	int i;
	for (i = 0; i < REG_NUM; i++) {
		REG[i] = 0;
	}
	SIGN = false;
	ZERO = false;
	CARRY = false;
	STOP_F = false;
	IR = 0;
	MAR = 0;
	MBR = 0;
	ALU = 0;
}

void trace(void* memory) {
	displayRegs();
	fetch(&memory);
}
