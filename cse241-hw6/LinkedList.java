import java.lang.Exception;
import java.util.NoSuchElementException;
import java.lang.IndexOutOfBoundsException;

public class LinkedList < E > implements Queue < E > , List < E > {


	private E[] arr;
	private int size = 0;
	
	public LinkedList(){
		arr = (E[]) new Object[1];	
	
	}
	public LinkedList(int capacity){
		arr = (E[]) new Object[capacity];
		size = capacity;
	}
	public E get(int index){
		if(index < 0  && index >= size())
			throw new IndexOutOfBoundsException("Invalid index number\n");
		
		E x = arr[index];
		return x;
	}
	
	public void setSize(int s){
		size = s;
	}
	
	public int size(){
		return size;
	}
	public void incSize(){
		size++;
	}
	public void decSize(){
		size--;
	}
	
	public Iterator < E > iterator() {
	
		return new Iterator < E >(){
		
			private int index = 0;
			
			public boolean hasNext(){
				return index < size() && arr[index] != null;
			
			}
			
			public E next() throws NoSuchElementException{
				if(hasNext())
					return (E)arr[index++];
				else
					throw new NoSuchElementException("There is no element.\n");
			}
			
			public void remove() throws UnsupportedOperationException,NoSuchElementException{
				throw new UnsupportedOperationException("Queue's does not support remove operation.\n");
			}
		};
	}
	
	public void add(E e){

		if(size() == arr.length){
			growSize(1);	
		}
		arr[size()] = e;
		incSize();
	}
	public void addAll(Collection c){
			
		LinkedList temp = (LinkedList) c;
				
		for(int i=0;i<temp.size();i++){
			if(size() == arr.length){
				growSize(1);	
			}
			arr[size()] = (E)temp.arr[i];
			incSize();				
		}	
	}
	
	public void clear(){
		arr = (E[]) new Object[1];
		setSize(0);
	}
	
	public boolean isEmpty(){
		if(size() == 0)
			return true;
		else
			return false;
	}
	
	
	public void growSize(int capacity){
		
		E[] temp = (E[]) new Object[size()+capacity];
		for(int i=0; i< size();i++){
			temp[i] = arr[i];
		}
		arr = temp;
	}	
	
	public void shrinkSize(E e){

		int j=0;
		E[] temp = (E[]) new Object[size()-1];
		for(int i=0; i< size();i++){
			if(!arr[i].equals(e)){
				temp[j] = arr[i];
				j++;
			}
			else 
				e = null;
		}
		arr = temp;
	}
	
	
	public boolean contains(E e){
		boolean check = false;
		
		for(int i=0; i < size(); i++){
			if(arr[i].equals(e))
				check = true;
		}	
		return check;
	}
	
	public boolean containsAll(Collection c){
		int counter=0;
		LinkedList temp = (LinkedList) c;
			
		if(size() < temp.size())
			return false;
			
		for(int i=0; i < temp.size(); i++){
			for(int j=0; j<size();j++)
				if(temp.arr[i].equals(arr[j]))
					counter++;
		}
		if(counter == temp.size())	return true;
		else			return false;
	}
	
	public void remove(E e){
	
		if(contains(e) == true){
			shrinkSize(e);
			decSize();
		}
	}
	public void removeAll(Collection c){
		boolean check;
		LinkedList temp = (LinkedList) c;
		for(int i=0; i < temp.size(); i++){
			check = false;
			for(int j=0; j<size();j++)
				if(check == false && temp.arr[i].equals(arr[j])){
					remove((E)temp.arr[i]);
					check = true;
				}
		}
	}
	
	public void retainAll(Collection c){
		clear();
		addAll(c);
	}	
	
	public E element() throws NoSuchElementException{
		if(isEmpty() == true)
			throw new NoSuchElementException();	
		E x = arr[0];
		return x;
	}	
	
	public void offer(E e){
		add(e);
	}

	public E poll() throws NoSuchElementException{
	
		if(isEmpty() == true)
			throw new NoSuchElementException();	
		E x = arr[0];
		remove(x);
		return x;
	}
	
	public String toString(){
		System.out.printf("\nElements in collection is:\n{ ");
		for( E element : arr)
			System.out.printf("(%s)", element);
		System.out.printf(" } --- ");
		return String.format("Size = %d",size());
	}
	
}
