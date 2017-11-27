#include "BigramDyn.h" 
template <class T>
BigramDyn<T>::BigramDyn(int type){
	dataType= type;
	gramsCount=0;
	dynListSize=1;
	dynList = new T[dynListSize];
}
template <class T>
BigramDyn<T>::~BigramDyn(){
	delete [] dynList;

}
template <class T>
BigramDyn<T>::BigramDyn(const BigramDyn& nesne2)
{
	dynListSize=nesne2.dynListSize;
	dataType = nesne2.dataType;
	gramsCount = nesne2.gramsCount;

	dynList = new T [dynListSize];
	for(int i = 0;i<dynListSize;++i)
		dynList[i]=nesne2.dynList[i];
}

template <class T>
BigramDyn<T> & BigramDyn<T>::operator=(const BigramDyn& nesne2){
	if(dynListSize=nesne2.dynListSize){
		delete [] dynList;
		dynList= new T[dynListSize];
	}
	dynListSize = nesne2.dynListSize;
	dataType = nesne2.dataType;
	gramsCount = nesne2.gramsCount;
	for(int i = 0;i<dynListSize;++i)
		dynList[i]=nesne2.dynList[i];
	return *this;
}

template <class T>
void BigramDyn<T>::readFile(string filename){
	ifstream inputStream;
	T biagType;
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
	dynListSize=0;
	while(inputStream >> biagType){
		gramsCount++;
		dynListSize++;
	}
	gramsCount--;
	inputStream.close();
	dynList=new T[dynListSize];
	inputStream.open(filename);
	int i=0;
	while(inputStream >> biagType){
		dynList[i]=biagType;
		i++;
	}
}

template <class T>
int BigramDyn<T>::numGrams()const {
	return gramsCount;
}
template <class T>
int BigramDyn<T>::numOfGrams(T t1,T t2)const{
	int i=0;
	int count=0;
	while(i<dynListSize){
		if(dynList[i]==t1 && dynList[i+1]==t2)
			count++;
		i++;
	}
	return count;
}
template <class T>
pair<T,T> BigramDyn<T>::maxGrams(){
	
	int i=0,k=1,max2;
	int temp1=0,temp2=1;
	int max1 = numOfGrams(dynList[i],dynList[k]);
	while(k<dynListSize-1){
		max2 = numOfGrams(dynList[i+1],dynList[k+1]);
		if(max2>max1) {
			max1=max2;
			temp1=i+1;
			temp2=k+1;
		}

		max2 = numOfGrams(dynList[i+1],dynList[k+1]);
		i++;
		k++;		
	}
	return pair<T,T>(dynList[temp1],dynList[temp2]);
}
template <class T>
void BigramDyn<T>::printHelper()const{
	pair <T,T> makeS[gramsCount];
	pair <T,T> temp;
	for(int i= 0 , k = 1 , c=0; k<dynListSize ; i++,k++,c++){
		makeS[c].first=dynList[i];
		makeS[c].second=dynList[k];
	}
	for(int i=0;i<gramsCount;i++){
		for(int j=i+1;j<gramsCount;j++){
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
	for(int i = 0;i<gramsCount;i++){
		cout << makeS[i].first << "," << makeS[i].second << " = "
		<< numOfGrams(makeS[i].first,makeS[i].second)<<endl;
	} 
}


