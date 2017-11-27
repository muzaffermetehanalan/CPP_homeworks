#ifndef _COMH_
#define _COMH_
#include <iostream>
#include <string>/*For string operations */
#include <fstream>/*For file operations */
#include <cstdlib>/*For exit() function   */
#include <vector>
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
using namespace std;
class Computer {
	public:
		Computer(int);/*This constructor sets the option*/
		Computer(CPU&,CPUProgram&,Memory&,int);
		/*This constructor sets the option,cpu,program and memory */
		void setCPU(CPU);/*Sets cpu */
		void setCPUProgram(CPUProgram);/*Sets cpuprogram */
		void setMemory(Memory);/*Sets memory */
		CPU getCPU();/*Returns CPU object */
		CPUProgram getCPUProgram();/*Returns CPUProgram object */
		Memory getMemory();/*Returns memory object */
		void setOption(int);/*Sets option */
		void execute();/*executes given file */
	private:
		int opt; /* option */
		CPU Cpu; /* CPU object */
		CPUProgram Prog; /*CPUProgram object */
		Memory Mem; /*Memory object */
};
#endif
