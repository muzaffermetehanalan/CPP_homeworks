#include "BigramMap.h"

template <class T>

BigramMap<T>::BigramMap(int type){
	dataType= type;
	gramsCount=0;
}

template <class T>
void BigramMap<T>::readFile(string filename){
	string testLine;
	fstream inputStream;
	T biagType,biagType2;
	typename std::map<pair<T,T>,int>::iterator it;
	inputStream.open(filename);
	if(inputStream.fail())
		throw myException("File couldn't open !!");	

	if(!(inputStream>>biagType)){
		throw myException("Empty File error !!");
	}

	inputStream.close();
	inputStream.open(filename);
	while(!inputStream.eof())
	{
		if(inputStream>>biagType){
		}

		else
			if(!inputStream.eof())
				throw myException("Bad data error");
	}

	inputStream.close();
	inputStream.open(filename);

	while(inputStream >> biagType){

		gramsCount++;
	}
	gramsCount--; 
	inputStream.close();
	inputStream.open(filename);
	
	inputStream>>biagType;
	for(int i =0 ; i<gramsCount ; i++)
	{
		inputStream>>biagType2;
		pair<T,T>biagPair (biagType,biagType2);
		auto it2 = biagList.find(biagPair);
		if(it2 != biagList.end())
			biagList[biagPair]=biagList[biagPair]+1;
		else
			biagList[biagPair]=1;
				
		biagType=biagType2;
	}
			 		
	inputStream.close();
}
template <class T>
int BigramMap<T>::numGrams()const {
	return gramsCount;
}
template <class T>
int BigramMap<T>::numOfGrams(T t1 , T t2)const {
	pair<T,T>biagPair(t1,t2);
	auto it2 = biagList.find(biagPair);
	if(it2 !=biagList.end())
		return it2->second;
	return  0;
}

template <class T>
pair <T,T> BigramMap<T>::maxGrams(){
	auto maxIt = biagList.begin();
	auto iter2=biagList.begin();
	iter2++;
	while(iter2 != biagList.end()) {
		if(iter2->second > maxIt -> second)
			maxIt =iter2;

		iter2++;
	}
	return maxIt->first;
}

template <class T>
void BigramMap<T>::printHelper()const {
	pair <T,T> makeS[gramsCount];
	pair <T,T> temp;
	auto it = biagList.begin();
	int i = 0,j;
	while(it != biagList.end())	{
		makeS[i].first=it->first.first;
		makeS[i].second=it->first.second;
		i++;
		it++;
	}
	

	for(i=0;i<biagList.size();i++){
		for(j=i+1;j<biagList.size();j++){
			if(numOfGrams(makeS[i].first,makeS[i].second)<numOfGrams(makeS[j].first,makeS[j].second))
			{
				temp.first=makeS[i].first;
				temp.second=makeS[i].second;
				makeS[i].first=makeS[j].first;
				makeS[i].second=makeS[j].second;
				makeS[j].first=temp.first;
				makeS[j].second=temp.second;
			}
		}
	}
	cout<<endl;
	for(i=0;i<biagList.size();i++){
		cout << makeS[i].first << "," << makeS[i].second << " = "
		<<  numOfGrams(makeS[i].first,makeS[i].second)<< endl;
	} 
}

