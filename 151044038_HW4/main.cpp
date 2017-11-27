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
int main(int argc, char *argv[])
{
	
	const char *filename =argv[1];
	int option =atoi(argv[2]);
	Memory myMem(option);
	CPU myCPU(option); /*constructor will set the given option */
	CPUProgram myProg(option);/*constructor will set the given option*/
	myProg.readFile(filename);
	Computer myComputer1(option);
	Computer myComputer2(myCPU,myProg,myMem,option);
	myComputer1.setCPU(myComputer2.getCPU());
	myComputer1.setCPUProgram(myComputer2.getCPUProgram());
	myComputer1.setMemory(myComputer2.getMemory());
	myComputer1.execute();
	return 0; 
}
