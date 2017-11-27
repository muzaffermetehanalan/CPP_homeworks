#include <iostream>
#include <string>/*For string operations */
#include <fstream>/*For file operations */
#include <cstdlib>/*For exit() function   */
#include <vector>
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"
using namespace std;

Computer::Computer(CPU &cpu,CPUProgram &program,Memory &memory,int option){
	/*This constructor sets the option,cpu,program and memory */
	setOption(option); /*calls setOption*/
	setCPU(cpu); /* calls setCPU */
	setCPUProgram(program); /* calls CPUProgram */
	setMemory(memory); /* calls Memory */
}
Computer::Computer(int option){
	setOption(option); /*This constructor sets the option */
}

void Computer::setCPU(CPU cpu)
{
	Cpu=cpu; /*Sets cpu */
} 

void Computer::setCPUProgram(CPUProgram program)
{
	Prog=program;/*Sets cpuprogram */
} 

void Computer::setMemory(Memory memory)
{
	Mem=memory;/*Sets Memory */
}

CPU Computer::getCPU()
{
	return Cpu;/*Returns cpu object */
}
CPUProgram Computer::getCPUProgram()
{
	return Prog;/*Returns CPUprogram object */
}

Memory Computer::getMemory()
{
	return Mem;/*Returns memory object */
}
void Computer::setOption(int option)
{
	opt=option;/*sets option */
}
void Computer::execute()/*This function makes a loop for executes given file*/
{
	while(!Cpu.halted()) /* while instruction is not equal "HLT" */
	{
		string instruction = Prog.getLine(Cpu.getPC()-1);
		Cpu.execute(instruction,Mem); /* executes the given instruction*/
	} 

}


