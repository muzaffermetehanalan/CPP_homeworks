#include <iostream>
#include <string> /*for string operations*/
#include <fstream>/*for file operations */
#include <cstdlib>/*for exit() function */
#include "CPU.h"
#include "Memory.h"
#include "Computer.h"
#include "CPUProgramDyn.h"
namespace program {
	CPUProgramDyn::CPUProgramDyn(int option)
	{
		/* constructor, set option */
		strSize=1;
		str = new string[strSize];
		opt=option; 
	}
	CPUProgramDyn::CPUProgramDyn(int option,string * tempStr,int size)
	{	
		cout <<"sa" << endl;	
		opt=option;
		str = new string[size];

		for(int i =0 ;i<size;i++)
			str[i]=tempStr[i];
	}
	CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& nesne2)
	{
		strSize=nesne2.size();
		opt = nesne2.opt;
		filename=nesne2.filename;

		str = new string [nesne2.size()];
		for(int i = 0;i<strSize;++i)
			str[i]=nesne2.str[i];
	}

	CPUProgramDyn & CPUProgramDyn::operator=(const CPUProgramDyn& nesne2){
		if(strSize!=nesne2.size()){
			delete [] str;
			str = new string [nesne2.size()];
		}
		strSize = nesne2.size();
		opt= nesne2.opt;
		filename=nesne2.filename;
		for(int i = 0;i<strSize;++i)
			str[i]=nesne2.str[i];
	
		return *this;
	}

	void CPUProgramDyn::setFile(string fileName)/*This function sets the filename*/
	{
		filename=fileName;
	}

	void CPUProgramDyn::ReadFile(string filename)/*This function reads and stores in to the string*/
	{
		ifstream inputStream;
		string strCp;
		int fileSize=0;
		inputStream.open(filename);/* Opens the given file */
		if(inputStream.fail())/*If file can't open*/
			exit(1);
	
		while(!inputStream.eof())/*While it's not end of file */
		{
			fileSize++;
			getline(inputStream,strCp);
		}
		inputStream.close();
		fileSize--;
		delete [] str;
		str = new string[fileSize];
		inputStream.open(filename);
		for(int i =0;i<fileSize;i++)
		{
			getline(inputStream,strCp);
			str[i]=strCp;
		}
		strSize=fileSize;
	}

	CPUProgramDyn::~CPUProgramDyn(){  delete  [] str;  }

	string CPUProgramDyn::getLine(int line)const
	{
		return str[line];
	}

	int CPUProgramDyn::size()const/* returns the size of file line*/
	{
		return strSize;
	}

	void CPUProgramDyn::push(string instruct){
		string *tempStr;
	
		tempStr= new string[strSize];

		for(int i = 0 ; i < strSize;++i)
			tempStr[i]=str[i];

		delete [] str;

		str = new string[strSize+1];

		for(int i = 0 ; i < strSize;++i)
			str[i]=tempStr[i];
		str[strSize]=instruct;

		delete [] tempStr;
		strSize++;
	}
	void CPUProgramDyn::prnStr()const/*Prints the given instruction */
	{
		for(int i =0 ; i<strSize ; ++i)
			cout << str[i] << endl;

		cout <<"Line count = " << size()<<endl;
	}

	bool CPUProgramDyn::operator==(const CPUProgramDyn & prog)const{
		/* return 1 , if first object == second object */
		return(size()==prog.size());
	}
	bool CPUProgramDyn::operator!=(const CPUProgramDyn & prog)const{
		/* return 1 , if first object != second object */
		return!(size()==prog.size());
	}
	bool CPUProgramDyn::operator>=(const CPUProgramDyn & prog)const{
		/* return 1 , if first object >= second object */
		return(size()>=prog.size());
	}
	bool CPUProgramDyn::operator>(const CPUProgramDyn & prog)const{
		/* return 1 , if first object > second object */
		return(size()>prog.size());
	}
	bool CPUProgramDyn::operator<=(const CPUProgramDyn & prog)const{
		/* return 1 , if first object <= second object */
		return(size()<=prog.size());
	}
	bool CPUProgramDyn::operator<(const CPUProgramDyn & prog)const{
		/* return 1 , if first object < second object */
		return(size()<prog.size());
	}
	const string CPUProgramDyn::operator[](int index)const{ /* Operator returns given line*/
		/* Returns given index , line */
		if(index>=strSize){
			cout << "Wrong index ! " << endl << "First index ll be return"
			<< endl;
			return getLine(0);
		}	
		return getLine(index); 
	}

	CPUProgramDyn CPUProgramDyn::operator()(int start,int end)const {
		/*Returns given numbers's line */
		CPUProgramDyn newProgram;
		if(start<=0){
			cout << "Invalid index " << endl;
			return newProgram;
		}
		else if(end>strSize)
		{
			cout << "Invalid index " << endl;
			return newProgram;
		}
		newProgram.strSize=(end-start)+1;
		newProgram.str = new string[newProgram.size()];
		cout << newProgram.size() << endl;
		start=start-1;

		for(int i =0;i<newProgram.size();++i,++start)
			newProgram.str[i]=str[start];
		return newProgram;
	} 

	ostream &operator<<(ostream &output ,const CPUProgramDyn& prog){
		for(int i=0;i<prog.size();i++)
			output << prog.str[i]<<endl;
		return output;
	}

	CPUProgramDyn CPUProgramDyn::operator--() // prefix operation 
	{
		CPUProgramDyn tmpProg(*this);
		delete [] str;
		--strSize;
		str = new string[strSize];
		for(int i =0;i<strSize;i++)
			str[i]=tmpProg.str[i];
		return *this;
	}
	CPUProgramDyn CPUProgramDyn::operator--(int ignoreMe) // postfix operation 
	{
		CPUProgramDyn tmpProg(*this);
		delete [] str;
		--strSize;
		str = new string[strSize];
		for(int i =0;i<strSize;i++)
			str[i]=tmpProg.str[i];
		return tmpProg;
	}

	CPUProgramDyn &CPUProgramDyn::operator+=(const string & tmpStr)/*Returns *this program*/
	{
		CPUProgramDyn tmpProg(*this);
		delete [] str;
		strSize++;
		str=new string[strSize];
		for(int i =0;i<tmpProg.size();i++)
			str[i]=tmpProg.str[i];
		str[strSize-1]=tmpStr;
		return *this;
	}

	CPUProgramDyn &CPUProgramDyn::operator+(const CPUProgramDyn & prog){
		CPUProgramDyn tmpProg(*this);
		delete [] str;
		str = new string[strSize+ prog.size()];
		strSize+=prog.size();

		for(int i =0;i<tmpProg.size();i++)
			str[i]=tmpProg.str[i];	
	
		for(int i=0,k=tmpProg.size();k<strSize;k++,i++)
			str[k]=prog.str[i];
		return *this;
	}
	CPUProgramDyn CPUProgramDyn::operator+(const string & tmpStr){
		CPUProgramDyn tmpProg;
		tmpProg.strSize=strSize+1;
		tmpProg.str = new string[tmpProg.size()];

		for(int i =0;i<strSize;i++)
			tmpProg.str[i]=str[i];

		tmpProg.str[strSize]= tmpStr;

		return tmpProg;
	}
}
