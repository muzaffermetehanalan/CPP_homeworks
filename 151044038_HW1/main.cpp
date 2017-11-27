/***********************************************************************/
/*   MUZAFFER METEHAN ALAN - 151044038 */
/*   CSE 241- HW01                     */
/*This program simulates a very simple CPU, that has only 5 registers*/
/*CPU has a small set of instructions */
/* Instructions = MOV-ADD-SUB-PRN-HLT */
/***********************************************************************/
/*   Includes and Defines */
#include <iostream>
#include <string>
#include <fstream>
#define REGISTER_SIZE 5
#define ARR_SIZE 2
using namespace std; /* namespace std */
/*Function Prototypes*/
void mov(int r_X, int r_Y,int regArr[]);
void movConst(int r_X, int constVal,int regArr[]);
void add(int r_X, int r_Y,int regArr[]);
void addConst(int r_X , int constVal , int regArr[]);
void subConst(int r_X , int constVal , int regArr[]);
void sub(int r_X, int r_Y,int regArr[]);
void prn(string str1,int regArr[]);
void hlt(int regArr[],int options);
int myPow(int base,int top);
int converter(int arr[],string str1,string str2);
int stringtoInteger(string strInput);
int main(int argc,char *argv[])
{
	int value1,value2,constValue,indexValue,i,option;
	int array[ARR_SIZE]={0,0};
	int registerArray[REGISTER_SIZE]={0,0,0,0,0};

	ifstream inputStream;

	string myFile,myStr,myStr2,myStr3,myOptions;
	if(argc!=3)
	{
	
		cout <<"Argumanlar Eksik Verildi!" << endl;
		return -1;
	}
	myOptions=argv[2]; /* Option initialize */
	option=stringtoInteger(myOptions); /* String convert  to integer */
	inputStream.open(argv[1]); /*Open the given filename (command line) */
	if(inputStream.fail())
	{
		cout<< "Dosya acilamadi!"<<endl;
		return -1;
	}
	inputStream >> myStr;	
	while(myStr!="HLT" && myStr!="HLT;" && myStr!="hlt" && myStr!="hlt;") 
	{
		
		if(myStr=="MOV"|| myStr=="mov") /* if instruction is MOV or mov */
		{
			inputStream>>myStr2;
			inputStream>>myStr3;
			if(myStr3==",") /* ignores ',' char */
				inputStream>>myStr3;		
			converter(array,myStr2,myStr3); 
			value1= array[0];
			value2= array[1];
			if(converter(array,myStr2,myStr3)==1)
			{	

				mov(value1,value2,registerArray); /* calling mov function */

			}
			else if(converter(array,myStr2,myStr3)==0)
			{

				constValue=stringtoInteger(myStr3);
				movConst(value1,constValue,registerArray);
			}

			if(option==1) /* if option is 1 */
			{
				cout << myStr << " " << myStr2 << "," <<myStr3 << 
				"-R1="<<registerArray[0]<<",R2="<<registerArray[1]<<",R3="<<
				registerArray[2]<<",R4="<<registerArray[3]
				<<",R5="<<registerArray[4]<<endl;
			}
		}
			
		
		else if(myStr=="ADD"||myStr=="add")/* if instruction is ADD or add */
		{
			inputStream>>myStr2;
			inputStream>>myStr3;
			if(myStr3==",") /* ignores ',' char */
				inputStream>>myStr3;
			converter(array,myStr2,myStr3);
			value1= array[0];
			value2= array[1];
			if(converter(array,myStr2,myStr3)==1)
				add(value1,value2,registerArray); /* calling add function */
			else if(converter(array,myStr2,myStr3)==0)
			{
				constValue=stringtoInteger(myStr3);
				addConst(value1,constValue,registerArray);
			}

			if(option==1) /* if option is 1 */
			{
				cout << myStr << " " << myStr2 << "," <<myStr3 << "-R1="
				<<registerArray[0]<<",R2="<<registerArray[1]<<",R3="
				<<registerArray[2]<<",R4="<<registerArray[3]
				<<",R5="<<registerArray[4]<<endl;
			}
		}

		else if(myStr=="SUB"||myStr=="sub")/* if instruction is SUB or sub */
		{
			inputStream>>myStr2;
			inputStream>>myStr3;
			if(myStr3==",") /* ignores ',' char */
				inputStream>>myStr3;
			converter(array,myStr2,myStr3);
			value1= array[0];
			value2= array[1];
			if(converter(array,myStr2,myStr3)==1)
				sub(value1,value2,registerArray);/* calling sub function */
			else if(converter(array,myStr2,myStr3)==0)
			{
				constValue=stringtoInteger(myStr3);
				subConst(value1,constValue,registerArray);
			}

			if(option==1) /* if option is 1 */
			{
				cout << myStr << " " << myStr2 << "," <<myStr3 << "-R1="
				<<registerArray[0]<<",R2="<<registerArray[1]<<",R3="
				<<registerArray[2]<<",R4="<<registerArray[3]
				<<",R5="<<registerArray[4]<<endl;
			}
		}

		else if(myStr=="PRN"||myStr=="prn")/* if instruction is PRN or prn */
		{
			inputStream>>myStr2;
			prn(myStr2,registerArray); /* calling prn function */
			if(option==1) /* if option is 1 */
			{
				cout<< myStr << " " << myStr2 << "-R1="<<registerArray[0]
				<<",R2="<<registerArray[1]<<",R3="<<registerArray[2]<<",R4="<<
				registerArray[3]<<",R5="<<registerArray[4]<<endl;
			}
		}
		else if(myStr=="JMP"||myStr=="jmp")/* if instruction is JMP or jmp */
		{
			inputStream>>myStr2;
			if(myStr2 =="R1"||myStr2=="R1,"||myStr2=="R2"||myStr2=="R2,"||
				myStr2=="R3"||myStr2=="R3,"||myStr2=="R4"||
				myStr2=="R4,"||myStr2=="R5"||myStr2=="R5,")
			{
				inputStream>>myStr3;
				if(myStr3==",") /* ignores ',' char */
					inputStream>>myStr3;
				constValue=stringtoInteger(myStr3);/*string to integer */
				if(myStr2 =="R1"||myStr2=="R1,")
					indexValue=0;
				else if(myStr2 =="R2"||myStr2=="R2,")
					indexValue=1;
				else if(myStr2 =="R3"||myStr2=="R3,")
					indexValue=2;
				else if(myStr2 =="R4"||myStr2=="R4,")
					indexValue=3;
				else if(myStr2 =="R5"||myStr2=="R5,")
					indexValue=4;

				if(registerArray[indexValue]==0)
				{
					inputStream.close(); /* closes the file for jump move */
					inputStream.open(argv[1]);/* open file for  jump */
					for(i=1;i<constValue;i++) /* a loop for jump */
						getline(inputStream,myStr);
					
					if(option==1) /* if option is 1 */
						cout << "JMP" << " " << myStr2 << "," <<myStr3 <<
						"-R1="<<registerArray[0]<<",R2="<<registerArray[1]<<
						",R3="<<registerArray[2]<<",R4="<<registerArray[3]
				    	<<",R5="<<registerArray[4]<<endl;
				}
			}
			else
			{
				constValue=stringtoInteger(myStr2);/* string to integer */
				inputStream.close(); /* closes the file for jump move */
				inputStream.open(argv[1]); /* open file for  jump */
				for(i=1;i<constValue;i++) /* a loop for jump */
					getline(inputStream,myStr);
				if(option==1)/* if option is 1 */
					cout<< "JMP" << " " << myStr2 << "-R1="<<registerArray[0]
					<<",R2="<<registerArray[1]<<",R3="<<registerArray[2]<<
					",R4="<<registerArray[3]<<",R5="<<registerArray[4]<<endl;
			}
		}

		inputStream >> myStr;
	}

	hlt(registerArray,option);
	return 0;
}
void mov(int r_X, int r_Y,int regArr[])
{	
 /* This function copies the value of r_X (R1) to r_Y(R2)*/
	regArr[r_Y]=regArr[r_X]; /* Copies the value of r_X */
}
void movConst(int r_X, int constVal,int regArr[])
{
 /* This function copies the value of constVal to r_X(R1)*/
	regArr[r_X]=constVal; /* Copies the value of r_X */
}
int converter(int arr[],string str1,string str2)
{
    /*This function converts the given strings*/
	int const_value;
	if(str1=="R1"||str1=="R1,")
		arr[0]=0;
	else if(str1=="R2"||str1=="R2,")
		arr[0]=1;
	else if(str1=="R3"||str1=="R3,")
		arr[0]=2;
	else if(str1=="R4"||str1=="R4,")
		arr[0]=3;
	else if(str1=="R5"||str1=="R5,")
		arr[0]=4;

	if(str2=="R1"||str2=="R1;"||str2==",R1"||str2==",R1;")
		arr[1]=0;
	else if(str2=="R2"||str2=="R2;"||str2==",R2"||str2==",R2;")
		arr[1]=1;
	else if(str2=="R3"||str2=="R3;"||str2==",R3"||str2==",R3;")
		arr[1]=2;
	else if(str2=="R4"||str2=="R4;"||str2==",R4"||str2==",R4;")
		arr[1]=3;
	else if(str2=="R5"||str2=="R5;"||str2==",R5"||str2==",R5;")
		arr[1]=4;
	else
		return 0;
	return 1;
}

void add(int r_X, int r_Y,int regArr[])
{
	/*This function adds the value of r_Y to r_X*/
	regArr[r_X]+=regArr[r_Y]; /*adds the value of r_Y to r_X*/
}
void addConst(int r_X , int constVal , int regArr[])
{
    /*This function adds the value of constVal to r_X*/
	regArr[r_X]+=constVal;/*adds the value of constVal to r_X*/
}
void sub(int r_X, int r_Y,int regArr[])
{
    /*This function subtracts the value of r_Y from r_X*/
	regArr[r_X]-=regArr[r_Y];/*subtracts the value of r_Y from r_X*/
}
void subConst(int r_X , int constVal , int regArr[])
{
    /*This function subtracts the value of constVal from r_X*/
	regArr[r_X]-=constVal;/*subtracts the value of constVal from r_X*/
}
void prn(string str1,int regArr[])
{
	/*This function display the value of given register
    or constant value*/
	int cnstVal;
	if(str1=="R1"||str1=="R1;")
		cout << regArr[0] << endl;/*Display R1*/
	else if(str1=="R2"||str1=="R2;")
		cout << regArr[1] << endl;/*Display R2*/
	else if(str1=="R3"||str1=="R3;")
		cout << regArr[2] << endl;/*Display R3*/
	else if(str1=="R4"||str1=="R4;")
		cout << regArr[3] << endl;/*Display R4*/
	else if(str1=="R5"||str1=="R5;")
		cout << regArr[4] << endl;/*Display R5*/

	else
	{
	    /*If given input is constant value*/
		cnstVal=stringtoInteger(str1);
		cout << cnstVal << endl;/*display constant*/
	}
}
int stringtoInteger(string strInput)
{
	/*This function convert the given string to integer value*/
    int size,index,result,sizeCopy;
    result = 0;
    size = strInput.length(); /* size = string size */
    if(strInput[size-1]==';') /* if last char is ';' */
    {
        if(strInput[0]=='-') /* if first char is '-' (negative value*/
        {
            for(index=1,sizeCopy=size;index<size-1;++index,--sizeCopy)
                result+=(strInput[index]-'0')*myPow(10,sizeCopy-3);
            return (-1)*result;
        }
        else
        {
            for(index=0,sizeCopy=size;index<size-1;++index,--sizeCopy)
                result+=(strInput[index]-'0')*myPow(10,sizeCopy-2);
            return result;
        }
    }
    else
    {
        if(strInput[0]=='-') /* if first char is '-' (negative value*/
        {
            for(index=1,sizeCopy=size;index<size;++index,--sizeCopy)
                result+=(strInput[index]-'0')*myPow(10,sizeCopy-2);
            return (-1)*result;
        }
        else /* positive value */
        {
            for(index=0,sizeCopy=size;index<size;++index,--sizeCopy)
                result+=(strInput[index]-'0')*myPow(10,sizeCopy-1);             
            return result;
        }
    }
}

int myPow(int base,int top)
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
void hlt(int regArr[],int options)
{
	cout << "R1 = "<< regArr[0] << endl;
	cout << "R2 = "<< regArr[1] << endl;
	cout << "R3 = "<< regArr[2] << endl;
	cout << "R4 = "<< regArr[3] << endl;
	cout << "R5 = "<< regArr[4] << endl;
	
	if(options==1)
		cout << "HLT" <<"-R1="<<regArr[0]
		<<",R2="<<regArr[1]<<",R3="<<regArr[2]
		<<",R4="<<regArr[3]
		<<",R5="<<regArr[4]<<endl;
}











