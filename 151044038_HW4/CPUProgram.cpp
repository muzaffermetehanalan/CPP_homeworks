#include <iostream>
#include <string> /*for string operations*/
#include <fstream>/*for file operations */
#include <cstdlib>/*for exit() function */
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
#include "Computer.h"
using namespace std;
CPUProgram::CPUProgram(int option)
{
	//This constructor set file and read file
	opt=option; /* calls readfile function*/
}

void CPUProgram::setFile(string fileName)/*This function sets the filename*/
{
	filename=fileName;
}

void CPUProgram::push(string instruct)/*This function pushes string */ 
{
	instructions.push_back(instruct);
}

void CPUProgram::readFile(string filename)/*This function reads and stores in to the string*/
{
	ifstream inputStream;
	string strCp;
	inputStream.open(filename);/* Opens the given file */
	if(inputStream.fail())/*If file can't open*/
		exit(1);
	
	while(!inputStream.eof())/*While it's not end of file */
	{
		getline(inputStream,strCp); /*calls getline function*/
		push(strCp);/* calls push function*/
	}
	instructions.pop_back();
	inputStream.close();/*closes the given file */

}

void CPUProgram::prnStr()const/*Prints the given instruction */
{
	for(string a : instructions)
		cout << a << endl;
	cout << instructions.size() << endl;
}

int CPUProgram::size()const /*This function returns the line size */
{
	return instructions.size();
}
string CPUProgram::getLine(int line)
{
	/*This function returns the given line's string*/
	return instructions[line-1];
}
