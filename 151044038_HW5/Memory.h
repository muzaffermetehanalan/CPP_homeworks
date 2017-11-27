#ifndef _MEMH_
#define _MEMH_
#include <iostream> 
#include <string>  /*For string operations */
#include <fstream> /*For file operations   */
#include <vector>  
#include <cstdlib> /*For exit() function   */
using namespace std;
int const MEM_SIZE=50; /*Definition for Memory Array size */
class Memory {
	public:
		Memory(int); /* This constructor sets option and Memory*/
		Memory(){};
		void setMem(int,int); /* Sets Memory */
		const int getMem(int index)const; /*Returns given index's Memory*/
		const void printAll() const;/*Prints all contents of Memory */
		const void printForOpt2()const;/*Prints all contents of Memory */
	private:
		const void testMemory(int)const;/*This function checks Memory */
		int progOption; /* Option */
		int unsigned  memArr[MEM_SIZE];/*Memory Array */

};

#endif
