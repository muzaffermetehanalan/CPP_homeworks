#ifndef BIAG_H
#define BIAG_H
#include "myException.h"
#include <iostream>
#include <map>
#include <fstream>/*for file operations */
#include <string>
using namespace std;
template <class T>
class Bigram {
	public:
		virtual void readFile(string filename)=0;
		virtual int numGrams()const=0;
		virtual int numOfGrams(T,T)const=0;
		virtual pair<T,T> maxGrams()=0;
		virtual void printHelper()const=0;
		friend ostream & operator <<(ostream &os ,const Bigram <T> & biagObj)
		{
			biagObj.printHelper();
			return os;
		}

};

#endif 
