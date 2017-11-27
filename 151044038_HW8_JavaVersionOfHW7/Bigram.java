import java.io.*;
import java.util.*;
public interface Bigram<T> {

	public abstract void readFile(String fileName)throws MyException, FileNotFoundException;

	public abstract int numGrams();

	public abstract int numOfGrams(T t1,T t2);

	public abstract  String toString();

}
