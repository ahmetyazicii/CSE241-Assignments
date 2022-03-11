import java.lang.Exception;
import java.util.NoSuchElementException;

interface Iterator < E >{
	boolean hasNext();
	E next() throws NoSuchElementException;
	void remove() throws UnsupportedOperationException,NoSuchElementException;
}
