import java.io.*;
import java.util.*;
@SuppressWarnings("unchecked")
public  class BigramDyn<T> implements Bigram<T> {
	private T [] BiagT;
    private int capSize;
    private int used;
    private int gramsCount=0;
    private MyPair<T,T> [] BiagPair;
    private int dataType;

    public BigramDyn(){
    	capSize=1;
    	used = 0;
 		BiagT= (T[]) new Object[capSize];

    }
    public BigramDyn(int datType){
    	dataType = datType;
    	capSize=1;
    	used = 0;
 		BiagT= (T[]) new Object[capSize];
    }
	public  void readFile(String fileName)throws MyException,FileNotFoundException
    { 
		Scanner file = new Scanner(new File(fileName));
		if(file == null)
            throw new MyException("File open error!");
		T i ;
		int c=0;
		if(dataType==1){
			try 
			{	
				while(file.hasNext())
				{
					if(file.hasNext())
						gramsCount++;	
						file.nextInt();	
				}	
				file.close();	
				BiagT= (T[]) new Object[gramsCount];
				file = new Scanner(new File(fileName));
				while(file.hasNext())
				{
					if(file.hasNext()){
					
						i=(T)(Object)(file.nextInt());
						BiagT[c]=i;
						System.out.println(i);
						c++;
					}		
				}	
				file.close();	

			}
			finally {}
		}
		else if(dataType==3){
			try 
			{
				while(file.hasNext())
				{
					if(file.hasNext())
						gramsCount++;
						file.nextDouble();	
				}	
				file.close();
				BiagT= (T[]) new Object[gramsCount];
				file = new Scanner(new File(fileName));	
				while(file.hasNext())
				{
					if(file.hasNext())
					{
						i=(T)(Object)(file.nextDouble());
						BiagT[c]=i;
						System.out.println(i);
						c++;
					}		
				}	
				file.close();		
			}
			finally {}
		}

		else if(dataType==2){
			try 
			{
				while(file.hasNext())
				{
					if(file.hasNext())
						gramsCount++;
						file.next();
				}	
				file.close();
				BiagT= (T[]) new Object[gramsCount];
				file = new Scanner(new File(fileName));	
				while(file.hasNext())
				{
					if(file.hasNext())
					{
						i=(T)(Object)(file.next());
						BiagT[c]=i;
						System.out.println(i);
						c++;
					}		
				}	
				file.close();		
			}
			finally {}

		}
		if(gramsCount== 0 || gramsCount==1)
            throw new MyException("There is no pair!!");

	}
	public  int numGrams(){ return gramsCount-1; }

	public  int numOfGrams(T t1,T t2){
		int i=0;
		int count=0;
		while(i<gramsCount-1){
			if(BiagT[i].toString().equals(t1.toString())&& BiagT[i+1].toString().equals(t2.toString())){
				count++;
			}
			i++;
		}
		return count;
	}

	public  String toString() {
		String str ="";
		BiagPair = new MyPair[gramsCount];
		MyPair<T,T> TempPair =null;
		for(int m=0; m<gramsCount-1;++m){
            BiagPair[m] = new MyPair<T, T>(BiagT[m],BiagT[m+1]);
   		}

   		for(int i=0;i<gramsCount-1;i++){
			for(int j=i+1;j<gramsCount-1;j++){
				if(numOfGrams(BiagPair[i].getFirst(),BiagPair[i].getSecond())<
				   numOfGrams(BiagPair[j].getFirst(),BiagPair[j].getSecond())){
					TempPair= new MyPair<T,T>(BiagPair[i].getFirst(),BiagPair[i].getSecond());
				    BiagPair[i]=new MyPair<T,T>(BiagPair[j].getFirst(),BiagPair[j].getSecond());
				    BiagPair[j]=new MyPair<T,T>(TempPair.getFirst(),TempPair.getSecond());
				}
			}
		}

   		for(int m =0;m<gramsCount-1;++m){
   			str+=BiagPair[m].getFirst()+" " + BiagPair[m].getSecond() +" "
   			+ numOfGrams(BiagPair[m].getFirst(),BiagPair[m].getSecond())+ "\n";
   		}
		return str;
	}

}
