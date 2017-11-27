#include <iostream> 
#include <string>  /*For string operations */
#include <fstream> /*For file operations   */
#include <vector>  
#include <cstdlib>/*For exit() function   */
#include "Memory.h"
using namespace std;
Memory::Memory(int option)/*This constructor sets option and Memory*/
{
	progOption=option;
	for(int i=0;i<MEM_SIZE;++i)
		setMem(i,0);
}

void Memory::setMem(int index,int indexValue){ /*This function sets Memory */
	testMemory(index); 
	memArr[index]=indexValue;
}

const void Memory::testMemory(int index)const{
	/*This function checks given Memory*/
	if(index<0 || index>=MEM_SIZE)	{
		cout << "Invalid Memory!" << endl;
		exit(1);
	}	
}
const int Memory::getMem(int index)const{
	 /*This function returns given index's Memory*/
	testMemory(index);
	return memArr[index];
}

const void Memory::printAll()const{ 
	/*This function prints all memory contents */
	for(int i=0;i<MEM_SIZE;++i)
		cout<< "["<<i<<"]" << " ->" << memArr[i] << endl;
}

const void Memory::printForOpt2()const{ 
	/* This function prints all memory contents*/
	
	cout << "				Memory  =			"<<endl;
	for(int i=0;i<MEM_SIZE;i++)
		cout << memArr[i] << '\t';
	cout<<endl;	

}
