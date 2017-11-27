#ifndef _CPUH_
#define _CPUH_
#include <iostream> 
#include <string>  /*For string operations */
#include <fstream> /*For file operations   */
#include <vector>  
#include <cstdlib> /*For exit() function   */
#include "Memory.h"
using namespace std;
int const REG_SIZE=5; /*Initialize register array*/
int const INDEX_SIZE=2;/*Initalize  index array */
class CPU {

	public:
		void print() const; /*Prints contents of registers and PC */
		void setRegisters();/*Sets value of registers */
		void setPC();/*Sets value of Program Counter */
		void setOption(int);/*Sets the value of option*/
		int getPC() const; /*Returns the value of PC */
		void execute(string,Memory &Mem);/*Executes the given string*/
		bool halted()const;/*Halts the program if given string(HLT)*/
		CPU(int); /* constructor */
		CPU(){};
	private:
		int registerArr[REG_SIZE]; /* register array */
		int PC; /* program counter */
		int checkValue=0; /* for the halted function */
		int opt; /* for the option */
		int isThatHalt(string)const; /*returns 1 if string is HLT */
		int isThatMov(string)const;  /*returns 1 if string is MOV */
	    int isThatAdd(string)const;  /*returns 1 if string is ADD */
		int isThatSub(string)const;  /*returns 1 if string is SUB */
		int isThatJmp(string)const;  /*returns 1 if string is JMP */
		int isThatPrn(string)const;  /*returns 1 if string is PRN */
		int isThatJpn(string)const;
		int myAtoi(string,int);	/*returns the integer value of string*/
		int myPow(int,int);/* Power function */
		int firstRegConvert(string,int,int[]);/*register converter*/
		int secondRegConvert(string,int,int[]);/*register converter*/
		void mov(int[],int[]); /* executes move instruction */
		void movConst(int[],int[]);/*executes move instruction*/
		void add(int[],int[]);/*executes add instruction */
		void addConst(int[],int[]);/*executes add instruction*/
		void sub(int[],int[]);/*executes sub instruction */
		void subConst(int[],int[]);/*executes sub instruction*/
		void movRegToAddress(int[],int[],Memory &Mem);/*executes mov*/
		void movAddressToReg(int[],int[],Memory &Mem);/*executes mov */
		void movConstToAddress(int[],Memory &Mem);/*executes mov */
		void subAddressToReg(int [],int[],Memory &Mem);/*executes Sub*/
		void addAddressToReg(int [],int[],Memory &Mem);/*executes Add*/
} ;
#endif
