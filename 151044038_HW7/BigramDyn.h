#ifndef DYN_H
#define DYN_H
#include "Bigram.h"
template <class T>
class BigramDyn : public Bigram <T>
{
	public:
		BigramDyn(int);
		BigramDyn(const BigramDyn&);
		BigramDyn& operator=(const BigramDyn&);
		void readFile(string filename);
	
		int numGrams()const;
		int numOfGrams(T,T)const;
		pair<T,T> maxGrams();
		void printHelper()const;
		~BigramDyn();
	private:
		int dataType;
		int gramsCount;
		T *dynList;
		int dynListSize;
};
#endif
