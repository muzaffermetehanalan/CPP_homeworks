#ifndef _CPROGH_
#define _CPROGH_
#include <iostream>
#include <string>/* for string operations*/
#include <fstream>/*for file operations */
#include <cstdlib>/*for exit() function*/
#include <vector>
using namespace std;

class CPUProgram {
	public :
		void setFile(string);/* sets filename */
		void readFile(string); /*reads all the file and appends to string */
		CPUProgram(int);/* constructor */
		CPUProgram(){};
		string getLine(int);/* returns the given line's string */
		int size()const;/* returns the size of file line*/				
		void push(string);/*appends new string to vector */
		void prnStr()const; /* prints the string */
	private:
		int opt;
		vector <string>instructions; /*instructions string*/
		string filename;
};
#endif
