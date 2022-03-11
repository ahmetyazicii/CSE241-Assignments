import java.lang.IndexOutOfBoundsException;
import java.lang.Exception;
import java.util.NoSuchElementException;
public class ArrayList < E > implements List < E > {

	private E[] arr;
	private int size = 0;
	
	public ArrayList(){
		arr = (E[]) new Object[1];	
	
	}
	public ArrayList(int capacity){
		arr = (E[]) new Object[capacity];
		size = capacity;
	}
	public E get(int index){
		if(index < 0  && index >= size())	// checking for invalid index
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
	
		return new Iterator < E >(){	// returning iterator
		
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
				if(! hasNext())
					throw new NoSuchElementException("There is no element.\n");
				shrinkSize(index);
				decSize();
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
			
		ArrayList temp = (ArrayList) c;
				
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
	
	public void growSize(int capacity){	// increasing array size and copying old array to new one
		
		E[] temp = (E[]) new Object[size()+capacity];
		for(int i=0; i< size();i++){
			temp[i] = arr[i];
		}
		arr = temp;
	}	
	
	public void shrinkSize(E e){ // decreasing array size and copying old array to new one 

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
	
	public void shrinkSize(int index){	

		int j=0;
		E[] temp = (E[]) new Object[size()-1];
		for(int i=0; i< size();i++){
			if(i != index){
				temp[j] = arr[i];
				j++;
			}
		}
		arr = temp;
	}
		
	public boolean contains(E e){
		boolean check = false;
		for(int i=0; i < size(); i++){
			if( arr[i].equals(e))
				check = true;
		}
		return check;
	}
	
	public boolean containsAll(Collection c){
		int counter=0;
		ArrayList temp = (ArrayList) c;
			
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
		ArrayList temp = (ArrayList) c;
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

	
	public String toString(){
		System.out.printf("\nElements in collection is:\n{ ");
		for( E element : arr)
			System.out.printf("(%s)", element);
		System.out.printf(" } --- ");
		return String.format("Size = %d",size());
	}

}
