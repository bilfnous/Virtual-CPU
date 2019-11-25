all : vcpu

vcpu : vcpu.c memFunc.c interface.c execute.c vcpu.h
	gcc -Wall vcpu.c memFunc.c interface.c execute.c -o vcpu

clean : 