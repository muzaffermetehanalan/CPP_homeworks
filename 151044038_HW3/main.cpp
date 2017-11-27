#include <iostream>
#include <string>/*For string operations */
#include <fstream>/*For file operations */
#include <cstdlib>/*For exit() function   */
#include <vector>
#include "CPU.h"
#include "CPUProgram.h"
using namespace std;
int main(int argc, char *argv[])
{

	CPU myCPU(argv[2]); /*constructor will set the given option */
	CPUProgram myProg(argv[1]);/*constructor will set the given filename */
	while(!myCPU.halted()) /* while instruction is not equal "HLT" */
	{
		string instruction = myProg.getLine(myCPU.getPC());
		myCPU.execute(instruction); /* executes the given instruction*/
	} 
	return 0;
}
