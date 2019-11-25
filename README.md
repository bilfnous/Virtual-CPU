# Virtual-CPU
C program that simulates a simple CPU at the register level (i.e. will simulate register to register transfers). Based on the ARM Cortex M0+ architecture. This program has a simple user interface that would allow it to be used to test machine level programs written for the CPU (read a binary file into memory, display memory, single step instructions, display registers, etc.) While single stepping the program should display the registers after the end of each instruction cycle.

## To run the code
* **Windows** 
* Download the repository
* Create a C project with your compiler of choice *i.e. Visual Studio*
* Add .C files to your *Resource Files* and add .h files to your *Header Files*
* Compile the program and run it
* Your first choice should be to load the cpu.txt file, which contains the cpu test code
<br>
* **Linux**
* Download the repository
* Go to the directory that has the project files and makefile
* Run the command `make` 
* Type `vcpu` to the run the program
* Your first choice should be to load the cpu.txt file, which contains the cpu test code