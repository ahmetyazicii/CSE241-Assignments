import java.lang.Exception;
import java.util.NoSuchElementException;

interface Queue < E > extends List < E > {
	
	void add(E e);
	E element() throws NoSuchElementException;
	void offer(E e);
	E poll() throws NoSuchElementException;

}
