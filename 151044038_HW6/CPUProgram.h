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
		void ReadFile(string); /*reads all the file and appends to string */
		CPUProgram(int);/* constructor */
		CPUProgram(){};
		CPUProgram(int,vector<string>);
		string getLine(int);/* returns the given line's string */
		int size()const;/* returns the size of file line*/				
		void push(string);/*appends new string to vector */
		void prnStr()const; /* prints the string */
		CPUProgram operator()(int start,int end)const;
		const string  operator[](int); /* Operator returns given line*/
		CPUProgram operator+(const string &);/*Returns new Program*/
		CPUProgram &operator+=(const string &);/*Returns *this program*/
		CPUProgram &operator+( CPUProgram &);/*Return *this program*/
		CPUProgram operator--(); // prefix operation
		CPUProgram operator--(int);//postfix operation
		bool operator==(const CPUProgram &)const;/* == operation */
		bool operator!=(const CPUProgram &)const;/* != operation */
		bool operator<=(const CPUProgram &)const;/* <= operation */
		bool operator>=(const CPUProgram &)const;/* >= operation */
		bool operator<(const CPUProgram &)const;/* < operation */
		bool operator>(const CPUProgram &)const;/* > operation */
		friend ostream & operator<<(ostream &output , const CPUProgram &);
		
	private:
		int opt;
		vector <string>instructions; /*instructions string*/
		string filename;
};
#endif
