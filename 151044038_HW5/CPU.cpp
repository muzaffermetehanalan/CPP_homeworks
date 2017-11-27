#include <iostream>
#include <string>/* for string operations*/
#include <fstream>/*for file operations */
#include <cstdlib>/* for exit() functions*/
#include <vector>
#include "CPU.h"
#include "Memory.h"
#include "CPUProgram.h"
using namespace std;
CPU::CPU(int Option){ /*Constructor sets Registers,PC and Option */
	setRegisters(); /* calls the setRegisters function */
	setPC(); /* calls the setPc function */
	setOption(Option);/* calls the setOption function */
}
void CPU::setOption(int Option)/*This function sets option */
{
	opt=Option;
}

void CPU::setRegisters(){/*This function sets the values of registers with 0 */
	for(int i=0;i<REG_SIZE;++i)
		registerArr[i]=0;
}

void CPU::setPC(){ /*This function sets the value of PC with 1 */
	PC=1;
}

int CPU::getPC() const{ /*This function returns the value of PC */
	return PC;
}	
bool CPU::halted()const{/*This function returns (T||F) */
	if(checkValue) /* if function will be halt */
		return true;
	else
		return false;
}
void CPU::execute(string lineString,Memory &Mem){/*This function executes given string */
	if(isThatHalt(lineString)) /*If string is "HLT" */
	{
		print(); /* calls print function */
		Mem.printAll();
		if(opt==1) /*If option is 1 */
		{
			cout << lineString << "-" << "R1="<<registerArr[0]<<",R2="<<
			registerArr[1]<<",R3="<<registerArr[2]<<",R4="<<registerArr[3]<<
			",R5="<<registerArr[4]<<endl;
		}
		else if(opt==2)
		{
			Mem.printForOpt2();
		}
		checkValue=1; /* Initializes checkValue for the halted() function */
	}
	else 
	{
		int i=3,indexArray[INDEX_SIZE];
		checkValue=0; /*Initializes checkValue for the halted() function */
		if(isThatMov(lineString)) /* If string is MOV */
		{
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			if(firstRegConvert(lineString,i,indexArray)){/*converts the register*/
				++i;
				while(lineString[i]!=',')/* Ignores ',' character */
			 		++i;
				++i;
				while(lineString[i]==' ')/* Ignores ' ' characters */
					++i;
				if(secondRegConvert(lineString,i,indexArray)==1)/*converts the regist*/
					mov(indexArray,registerArr); /* calls mov function */
				else if(secondRegConvert(lineString,i,indexArray)==0){
					movRegToAddress(indexArray,registerArr,Mem);
				}
				else if(secondRegConvert(lineString,i,indexArray)==-1){
					movConst(indexArray,registerArr);/* calls movConst function */
				}
			}
			else {
				++i;
				while(lineString[i]!=',')/* Ignores ',' character */
			 		++i;
				++i;
				while(lineString[i]==' ')/* Ignores ' ' characters */
					++i;
				if(secondRegConvert(lineString,i,indexArray)==1)/*converts the regist*/
					movAddressToReg(indexArray,registerArr,Mem);
				else if(secondRegConvert(lineString,i,indexArray)==-1)
					movConstToAddress(indexArray,Mem);
			}
			PC++; /* Program Counter adding with 1 */
		}
		else if(isThatAdd(lineString))/* If string is ADD */
		{
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			firstRegConvert(lineString,i,indexArray);/*converts the register*/
			++i;
			while(lineString[i]!=',')/* Ignores ',' character */
			 	++i;
			++i;
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			if(secondRegConvert(lineString,i,indexArray)==1)/*converts the regist*/
				add(indexArray,registerArr);/* calls add function */
			else if(secondRegConvert(lineString,i,indexArray)==0)
				addAddressToReg(indexArray,registerArr,Mem);
			else if(secondRegConvert(lineString,i,indexArray)==-1)
				addConst(indexArray,registerArr);/* calls addConst function */
			PC++;
		}
		else if(isThatSub(lineString))/* If string is SUB */
		{
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			firstRegConvert(lineString,i,indexArray);/*converts the register*/
			++i;
			while(lineString[i]!=',')/* Ignores ',' character */
			 	++i;
			++i;
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			if(secondRegConvert(lineString,i,indexArray)==1)/*converts the regist*/
				sub(indexArray,registerArr);/* calls sub function */
			else if(secondRegConvert(lineString,i,indexArray)==0)
				subAddressToReg(indexArray,registerArr,Mem);
			else if(secondRegConvert(lineString,i,indexArray)==-1)
				subConst(indexArray,registerArr);/* calls subConstfunction */
			PC++;
		}
		else if(isThatJmp(lineString))/* If string is JMP*/
		{
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			if(secondRegConvert(lineString,i,indexArray)==1)/*converts the register*/
			{
				++i;
				if(registerArr[indexArray[1]]==0)
				{
					while(lineString[i]!=',')/* Ignores ',' character */
						++i;
					++i;
					while(lineString[i]==' ')/* Ignores ' ' characters */
						++i;
					secondRegConvert(lineString,i,indexArray);
					PC=indexArray[1];/*PC initializes with given value */
				}
				else
					++PC;
			}
			else if(secondRegConvert(lineString,i,indexArray)==-1)
				PC=indexArray[1];
		}
		else if(isThatPrn(lineString))/*If string is PRN */
		{
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			if(secondRegConvert(lineString,i,indexArray)==1)
				cout<< registerArr[indexArray[1]]<<endl;
			else if(secondRegConvert(lineString,i,indexArray)==0)
				cout<< Mem.getMem(indexArray[1])<<endl;
			else if(secondRegConvert(lineString,i,indexArray)==-1)
				cout << indexArray[1] << endl;
			PC++;
		}
		else if(isThatJpn(lineString))/*If string is JPN */
		{
			while(lineString[i]==' ')/* Ignores ' ' characters */
				++i;
			if(secondRegConvert(lineString,i,indexArray)==1)/*converts the register*/
			{
				++i;
				if(registerArr[indexArray[1]]<=0)
				{
					while(lineString[i]!=',')/* Ignores ',' character */
						++i;
					++i;
					while(lineString[i]==' ')/* Ignores ' ' characters */
						++i;
					secondRegConvert(lineString,i,indexArray);
					PC=indexArray[1];/*PC initializes with given value */
				}
				else
					PC++;
			}
			else if(secondRegConvert(lineString,i,indexArray)==-1)
				PC=indexArray[1];			
		}
		else /* If string is not equal (MOV,ADD,SUB,PRN,JMP) */
		{
			cout<<"Invalid Instruction! ==" <<lineString<< endl;
			exit(1);
		}
		if(opt==1) /* If option is 1 */
		{
			cout << lineString << "-" << "R1="<<registerArr[0]<<",R2="<<
			registerArr[1]<<",R3="<<registerArr[2]<<",R4="<<registerArr[3]<<
			",R5="<<registerArr[4]<<endl;
		}
 		else if(opt==2)
		{
			Mem.printForOpt2();
		}
	}
}
void CPU::print()const{ //This function prints the contents of registers and PC
	for(int i=0,k=1;i<REG_SIZE;++i,++k)
		cout<<"R"<<k<<" = " << registerArr[i]<<endl;

	cout << "Program Counter = " << PC<<endl;
}
int CPU::isThatHalt(string lineString)const{
	/*This function checks the given string,if string is "HLT" returns 1
	 else returns 0 */
	if((lineString[0]=='H'||lineString[0]=='h')&&(lineString[1]=='L'||
		lineString[1]=='l')&&(lineString[2]=='T'||lineString[2]=='t'))
		return 1;
	else
		return 0;
}
int CPU::isThatMov(string lineString)const{
	/*This function checks the given string,if string is "MOV" returns 1
	 else returns 0 */
	if((lineString[0]=='M'||lineString[0]=='m')&&(lineString[1]=='O'||
		lineString[1]=='o')&&(lineString[2]=='V'||lineString[2]=='v'))
		return 1;
	else
		return 0;
}
int CPU::isThatAdd(string lineString)const{
	/*This function checks the given string,if string is "ADD" returns 1
	 else returns 0 */
	if((lineString[0]=='A'||lineString[0]=='a')&&(lineString[1]=='D'||
		lineString[1]=='d')&&(lineString[2]=='D'||lineString[2]=='d'))
		return 1;
	else
		return 0;
}
int CPU::isThatSub(string lineString)const{
	/*This function checks the given string,if string is "SUB" returns 1
	 else returns 0 */
	if((lineString[0]=='S'||lineString[0]=='s')&&(lineString[1]=='U'||
		lineString[1]=='u')&&(lineString[2]=='B'||lineString[2]=='b'))
		return 1;
	else
		return 0;
}
int CPU::isThatJmp(string lineString)const{
	/*This function checks the given string,if string is "JMP" returns 1
	 else returns 0 */
	if((lineString[0]=='J'||lineString[0]=='j')&&(lineString[1]=='M'||
		lineString[1]=='m')&&(lineString[2]=='P'||lineString[2]=='p'))
		return 1;
	else
		return 0;
}
int CPU::isThatPrn(string lineString)const{
	/*This function checks the given string,if string is "PRN" returns 1
	 else returns 0 */
	if((lineString[0]=='P'||lineString[0]=='p')&&(lineString[1]=='R'||
		lineString[1]=='r')&&(lineString[2]=='N'||lineString[2]=='n'))
		return 1;
	else
		return 0;
}
int CPU::isThatJpn(string lineString)const{
	/*This function checks the given string,if string is "JPN" returns 1
	 else returns 0 */
	if((lineString[0]=='J'||lineString[0]=='j')&&(lineString[1]=='P'||
		lineString[1]=='p')&&(lineString[2]=='N'||lineString[2]=='n'))
		return 1;
	else
		return 0;
}
int CPU::firstRegConvert(string lineString,int i,int indexArray[])
{
	if(lineString[i]=='r' || lineString[i]=='R'){
		++i;
		if(lineString[i]=='1')
			indexArray[0]=0;
	    else if(lineString[i]=='2')
			indexArray[0]=1;	
	    else if(lineString[i]=='3')
			indexArray[0]=2;	
	    else if(lineString[i]=='4')
			indexArray[0]=3;	
	    else if(lineString[i]=='5')
			indexArray[0]=4;
		return 1;
	}
	else if(lineString[i]=='#'){
		++i;
		indexArray[0]=myAtoi(lineString,i);
		return 0;
	}
	else {
		cout<<"Invalid Register" << endl;
		exit(1);
	}
}
int  CPU::secondRegConvert(string lineString,int i ,int indexArray[])
{
	if(lineString[i]=='r' || lineString[i]=='R')
	{
		++i;
		if(lineString[i]=='1')
			indexArray[1]=0;
		else if(lineString[i]=='2')
			indexArray[1]=1;	
		else if(lineString[i]=='3')
			indexArray[1]=2;	
		else if(lineString[i]=='4')
			indexArray[1]=3;	
		else if(lineString[i]=='5')
			indexArray[1]=4;
		return 1;	
	}
	else if(lineString[i]=='#')
	{
		++i;
		indexArray[1]=myAtoi(lineString,i);
		return 0;
	}
	else 
	{
		if(lineString[i]<='9' && lineString[i]>='0'){
			indexArray[1]=myAtoi(lineString,i);
		}
		else if(lineString[i]=='-')
		{
			++i;
			indexArray[1]=myAtoi(lineString,i);
		}
		return -1;

	}
}
int CPU::myAtoi(string lineString,int i)
{
	int copyValue,copyValue2,count=0,result=0;
	copyValue=i;
	copyValue2=i;
	while(lineString[copyValue]<='9' && lineString[copyValue]>='0')
	{
		++count;
		++copyValue;
	}
	while(count-1>=0)
	{
		result+=(lineString[i]-'0')*myPow(10,count-1);
		++i;
		--count;
	}
	if(lineString[copyValue2-1]=='-')
		return result*(-1);
	else
		return result;	
}
int CPU::myPow(int base,int top)
{
	/*The implemantation of pow() function */
	if(base==0)
		return base;
	else if(base==1)
		return base;
	else if(top==0)
		return 1;
	else
	{
		int result=1;
		for(int k=0;k<top;k++)
			result*=base;
		return result;
	}	
}
void CPU::mov(int indexArray[],int registerArr[])
{
	registerArr[indexArray[1]]=registerArr[indexArray[0]];
}
void CPU::movConst(int indexArray[],int registerArr[])
{
	registerArr[indexArray[0]]=indexArray[1];
}
void CPU::add(int indexArray[],int registerArr[])
{
	registerArr[indexArray[0]]+=registerArr[indexArray[1]];
}
void CPU::addConst(int indexArray[],int registerArr[])
{
	registerArr[indexArray[0]]+=indexArray[1];
}
void CPU::sub(int indexArray[],int registerArr[])
{
	registerArr[indexArray[0]]-=registerArr[indexArray[1]];
}
void CPU::subConst(int indexArray[],int registerArr[])
{
	registerArr[indexArray[0]]-=indexArray[1];
}
void CPU::movRegToAddress(int indexArray[],int registerArr[],Memory &Mem)
{
	Mem.setMem(indexArray[1],registerArr[indexArray[0]]);
}
void CPU::movAddressToReg(int indexArray[],int registerArr[],Memory &Mem){
	registerArr[indexArray[1]]=Mem.getMem(indexArray[0]);
}
void CPU::movConstToAddress(int indexArray[],Memory &Mem){
	Mem.setMem(indexArray[0],indexArray[1]);
}
void CPU::addAddressToReg(int indexArray[],int registerArr[],Memory &Mem){
	registerArr[indexArray[0]]+=Mem.getMem(indexArray[1]);
}
void CPU::subAddressToReg(int indexArray[],int registerArr[],Memory &Mem){
		registerArr[indexArray[0]]-=Mem.getMem(indexArray[1]);
}
