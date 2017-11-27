#ifndef MAP_H
#define MAP_H
#include "Bigram.h"
template <class T>
class BigramMap : public Bigram <T>
{
	public:
		BigramMap(int);
		void readFile(string filename);
		int numGrams()const;
		int numOfGrams(T,T)const;
		pair<T,T> maxGrams();
		void printHelper()const;
	private:
		int dataType;
		int gramsCount;
		map <pair<T,T>,int> biagList;
};
#endif
