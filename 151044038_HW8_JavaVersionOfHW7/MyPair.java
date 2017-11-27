import java.io.*;
import java.util.*;
@SuppressWarnings("unchecked")
public class MyPair<T,V> {
	private T first;
	private V second;

	public MyPair(T t1 , V t2){
		setPair(t1,t2);
	}

	public void setPair(T t1, V t2){
		this.first=t1;
		this.second=t2;
	}

	public T getFirst(){
		return first;
	}

	public V getSecond(){
		return second;
	}

	public String toString() {
        return first + " " + second;
    }
    
}
