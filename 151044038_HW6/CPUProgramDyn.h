#ifndef _CPROGDYNH_
#define _CPROGDYNH_
#include <iostream>
#include <string>/* for string operations*/
#include <fstream>/*for file operations */
#include <cstdlib>/*for exit() function*/
#include <vector>
using namespace std;
namespace program {
	class CPUProgramDyn {
		public :
			void setFile(string);/* sets filename */
			void ReadFile(string); /*reads all the file and appends to string */
			CPUProgramDyn(int);/* constructor */
			CPUProgramDyn(){};
			CPUProgramDyn(int,string *,int);
			string getLine(int)const;/* returns the given line's string */
			int size()const;/* returns the size of file line*/				
			void push(string);/*appends new string to vector */
			void prnStr()const; /* prints the string */
			CPUProgramDyn operator()(int start,int end)const;
			const string  operator[](int)const; /* Operator returns given line*/
			CPUProgramDyn operator+(const string &);/*Returns new Program*/
			CPUProgramDyn &operator+=(const string &);/*Returns *this program*/
			CPUProgramDyn &operator+(const CPUProgramDyn &);/*Return *this program*/
			CPUProgramDyn operator--(); // prefix operation
			CPUProgramDyn operator--(int);//postfix operation
			bool operator==(const CPUProgramDyn &)const;/* == operation */
			bool operator!=(const CPUProgramDyn &)const;/* != operation */
			bool operator<=(const CPUProgramDyn &)const;/* <= operation */
			bool operator>=(const CPUProgramDyn &)const;/* >= operation */
			bool operator<(const CPUProgramDyn &)const;/* < operation */
			bool operator>(const CPUProgramDyn &)const;/* > operation */
			friend ostream & operator<<(ostream &output , const CPUProgramDyn &);
			CPUProgramDyn(const CPUProgramDyn &nesne2);
			CPUProgramDyn& operator=(const CPUProgramDyn& nesne2);
			~CPUProgramDyn();
		
		private:
			int opt;/*instructions string*/
			string filename;
			int strSize=0;
			string *str;
	};
}
#endif
