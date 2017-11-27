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
	/* constructor, set option */
	opt=option; 
}
CPUProgram::CPUProgram(int option,vector <string>vec)
{
	/*constructor, set option and vector */
	opt=option;
	instructions=vec;
}
void CPUProgram::setFile(string fileName)/*This function sets the filename*/
{
	filename=fileName;
}

void CPUProgram::push(string instruct)/*This function pushes string */ 
{
	instructions.push_back(instruct);
}

void CPUProgram::ReadFile(string filename)/*This function reads and stores in to the string*/
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
	return instructions[line];
}
const string  CPUProgram::operator[](int index){
	/* Returns given index , line */
	if(index==instructions.size()){
		cout << "Wrong index ! " << endl << "First index ll be return"
		<< endl;
		return getLine(0);
	}	
	return getLine(index); 
}
CPUProgram CPUProgram::operator+(const string &str){
	CPUProgram newProgram;
	if(str==""){
		cout<<"Empty String ! " << endl;
		return newProgram;
	}
	newProgram.opt=this->opt;
	newProgram.instructions=this->instructions;
	newProgram.filename=this->filename;
	newProgram.push(str);
	return newProgram;
}

CPUProgram & CPUProgram::operator+=(const string & str) {
	if(str==""){
		cout<<"Empty String ! " << endl;
		return *this;
	}
	push(str);
	return *this;
}
CPUProgram &CPUProgram::operator+(CPUProgram & prog) {
	for(int i=0;i<prog.size();i++)
		push(prog.getLine(i));
	return *this;	
} 
ostream & operator<<(ostream &output , const CPUProgram &prog){
	for(int i=0;i<prog.size();i++)
		output << prog.instructions[i]<<endl;
	return output;
}
bool CPUProgram::operator==(const CPUProgram & prog)const{
	/* return 1 , if first object == second object */
	return(instructions.size()==prog.size());
}
bool CPUProgram::operator!=(const CPUProgram & prog)const{
	/* return 1 , if first object != second object */
	return!(instructions.size()==prog.size());
}
bool CPUProgram::operator>=(const CPUProgram & prog)const{
	/* return 1 , if first object >= second object */
	return(instructions.size()>=prog.size());
}
bool CPUProgram::operator>(const CPUProgram & prog)const{
	/* return 1 , if first object > second object */
	return(instructions.size()>prog.size());
}
bool CPUProgram::operator<=(const CPUProgram & prog)const{
	/* return 1 , if first object <= second object */
	return(instructions.size()<=prog.size());
}
bool CPUProgram::operator<(const CPUProgram & prog)const{
	/* return 1 , if first object < second object */
	return(instructions.size()<prog.size());
}
CPUProgram CPUProgram::operator--(){ /*Prefix unary operator*/
	/*Deletes last line */
	instructions.pop_back();
	return CPUProgram(opt,instructions);
}
CPUProgram CPUProgram::operator--(int ignoreMe) { /*Postfix unary operator*/
	/*Deletes last line , after using operator */
	vector <string>tempInstructions;
	tempInstructions=instructions;
	instructions.pop_back();
	return CPUProgram(opt,tempInstructions);
}

CPUProgram CPUProgram::operator()(int start,int end)const{
	/*Returns given numbers's line */
	CPUProgram newProgram;
	if(start<=0){
		cout << "Invalid index " << endl;
		return newProgram;
	}
	else if(end>instructions.size())
	{
		cout << "Invalid index " << endl;
		return newProgram;
	}
	start=start-1;
	while(start<=end-1){
		newProgram.push(instructions[start]);
		start++;
	}
	return newProgram;	
}







