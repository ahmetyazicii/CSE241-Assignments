import java.util.Scanner;
import java.lang.Exception;
import java.util.NoSuchElementException;
import java.util.InputMismatchException;
import java.lang.IndexOutOfBoundsException;

public class testCollection{

	// method for printing operation menu
	public static void printOperationMenu(){
		System.out.println("\nPlease select the operation:");
		System.out.println("1-Iterator      2-Add		3-AddAll");
		System.out.println("4-Clear         5-Contains      6-ContainsAll");
		System.out.println("7-IsEmpty       8-Remove        9-RemoveAll");
		System.out.println("10-RetainAll    11-Get         12-Element");
		System.out.println("13-Offer        14-Poll        15-Size");
		System.out.println("0-Exit");
	}
	// method for printing iterator operation menu
	public static void printIteratorOperationMenu(){
		System.out.println("\nSelect Iterator Options:");
		System.out.println("1-HasNext    2-Next     3-Remove");
	}
	
	// method for perform add operation for integers	
	public static void addInteger(Collection c){
		String inputline = null; 
		int inputint;	
		Scanner input = new Scanner(System.in);
		
		
		System.out.println("Please fill the collection with integer numbers one by one(type HALT for halt)");
		do{
			try{
				inputline= input.nextLine();
			
				inputint = Integer.parseInt(inputline);
			
				c.add(inputint);
			}
			catch (NumberFormatException nexc){
				System.out.println("Please type integer numbers.\n");
			}


		}while(!inputline.equals("HALT"));
	}
	
	// method for perform add operation for strings
	public static void addString(Collection c){
		String inputline = null; 
		Scanner input = new Scanner(System.in);
		
		
		System.out.println("Please fill the collection with strings one by one(type HALT for halt)");
		do{
			try{
				inputline= input.nextLine();			
				if(!inputline.equals("HALT"))
					c.add(inputline);
			}
			catch (NoSuchElementException nexc){
				System.out.println("No line was found.\n");
			}


		}while(!inputline.equals("HALT"));
	}
	
	// method for adding const elements to collection
	public static void fillCollectionInteger(Collection c){
		c.add(1);
		c.add(2);
		c.add(3);
		c.add(4);
	}
	// method for adding const elements to collection
	public static void fillCollectionString(Collection c){
		c.add("HELLO");
		c.add("WORLD");
		c.add("\n");
	}
	

	// method for performing all operations
	public static void test(Collection c,int type){

		Scanner input = new Scanner(System.in);
		int choose;
		int inputint = 0;
		boolean check = true;
		String inputstr = null;
		Iterator iterator = c.iterator();
		
		// creating const collections
		HashSet<Integer> constSetInteger = new HashSet<Integer>();
		HashSet<String> constSetString = new HashSet<String>(); 
		fillCollectionInteger(constSetInteger);
		fillCollectionString(constSetString);
		
		ArrayList<Integer> constListInteger = new ArrayList<Integer>();
		ArrayList<String> constListString = new ArrayList<String>(); 
		fillCollectionInteger(constListInteger);
		fillCollectionString(constListString);
		
		LinkedList<Integer> constLLInteger = new LinkedList<Integer>();
		LinkedList<String> constLLString = new LinkedList<String>(); 		
		fillCollectionInteger(constLLInteger);
		fillCollectionString(constLLString);
		
		do{
			printOperationMenu();
	
			choose = input.nextInt();
			input.nextLine();
			
			switch(choose ){
				case 1:	// iterator operation
					printIteratorOperationMenu();
					inputint = input.nextInt();
					
					try{
						if(inputint == 1){
							if(iterator.hasNext() == false)
								System.out.println("There is no more element.");
							else
								System.out.println("Iterator has more element.");
						}
						if(inputint == 2)
							System.out.printf("\nNext element is = %s \n",iterator.next());
						if(inputint == 3){
							iterator.remove();
							System.out.println("Current element is removed from collection.");
						}
					
					}
					catch(NoSuchElementException elementExcp){
							System.out.println(elementExcp);
					}
					catch(UnsupportedOperationException operationExcp){
							System.out.println(operationExcp);
					}
					break;
				case 2:	 // add operation
					if(type == 0)
						addInteger(c);
					else
						addString(c);
					break;
				case 3: // addAll operation
					System.out.printf("Collection is adding with following collection:");
					if(type == 0){
						System.out.println(constSetInteger);
						if(c instanceof HashSet)
							c.addAll(constSetInteger);
						else if(c instanceof ArrayList)
							c.addAll(constListInteger);
						else
							c.addAll(constLLInteger);
					}
					if(type == 1){
						System.out.println(constSetString);
						if(c instanceof HashSet)
							c.addAll(constSetString);
						else if(c instanceof ArrayList)
							c.addAll(constListString);
						else
							c.addAll(constLLString);
					}
					
					break;
				case 4: // clear operation
					c.clear();
					break;
				case 5: // contains operation
					if(type == 0){
						inputint = input.nextInt();
						if(c.contains(inputint) == true)
							System.out.printf("\n%d is in collection.\n",inputint);
						else
							System.out.printf("\n%d is not in collection.\n",inputint);
					}
					if(type == 1){
						inputstr = input.nextLine();
						if(c.contains(inputint) == true)
							System.out.printf("\n%s is in collection.\n",inputstr);
						else
							System.out.printf("\n%s is not in collection.\n",inputstr);
					}
					break;
				case 6: // containsAll operation
					System.out.printf("Collection is comparing with following collection:");
					if(type == 0){
						System.out.println(constSetInteger);
						if(c instanceof HashSet){
							if(c.containsAll(constSetInteger) == true)
								System.out.println("Collection is contains above collection");
							else
								System.out.println("Collection is not contains above collection");
						}
						else if(c instanceof ArrayList){
							if(c.containsAll(constListInteger) == true)
								System.out.println("Collection is contains above collection");
							else
								System.out.println("Collection is not contains above collection");
						
						}
						else{
							if(c.containsAll(constLLInteger) == true)
								System.out.println("Collection is contains above collection");
							else
								System.out.println("Collection is not contains above collection");
						}
					}
					if(type == 1){
						System.out.println(constSetInteger);
						if(c instanceof HashSet){
							if(c.containsAll(constSetString) == true)
								System.out.println("Collection is contains above collection");
							else
								System.out.println("Collection is not contains above collection");
						}
						else if(c instanceof ArrayList){
							if(c.containsAll(constListString) == true)
								System.out.println("Collection is contains above collection");
							else
								System.out.println("Collection is not contains above collection");
						
						}
						else{
							if(c.containsAll(constLLString) == true)
								System.out.println("Collection is contains above collection");
							else
								System.out.println("Collection is not contains above collection");
						}
					}				
				
					break;
				
				case 7: // isEmpty operation
					if(c.isEmpty() == true)
						System.out.println("Collection is empty.");
					else
						System.out.println("Collection is not empty.");
					break;
				case 8: // remove operation
					if(type == 0){
						inputint = input.nextInt();
						c.remove(inputint);
					}
					if(type == 1){
						inputstr = input.nextLine();
						c.remove(inputstr);
					}
					break;
				case 9: //removeAll operation
					System.out.printf("Following collection is removing:");
					if(type == 0){
						System.out.println(constSetInteger);
						if(c instanceof HashSet)
							c.removeAll(constSetInteger);
						else if(c instanceof ArrayList)
							c.removeAll(constListInteger);
						else
							c.removeAll(constLLInteger);
					}
					if(type == 1){
						System.out.println(constSetString);
						if(c instanceof HashSet)
							c.removeAll(constSetString);
						else if(c instanceof ArrayList)
							c.removeAll(constListString);
						else
							c.removeAll(constLLString);
					}											
					break;				
				case 10: // retainAll operation
					System.out.printf("Retains only following collection:");
					if(type == 0){
						System.out.println(constSetInteger);
						if(c instanceof HashSet)
							c.retainAll(constSetInteger);
						else if(c instanceof ArrayList)
							c.retainAll(constListInteger);
						else
							c.retainAll(constLLInteger);
					}
					if(type == 1){
						System.out.println(constSetString);
						if(c instanceof HashSet)
							c.retainAll(constSetString);
						else if(c instanceof ArrayList)
							c.retainAll(constListString);
						else
							c.retainAll(constLLString);
					}
					break;
				case 11: // get operation
					if(c instanceof ArrayList){						
						ArrayList temp = (ArrayList) c;
						
						try{
							System.out.println("Type index that you want to get.");
							inputint = input.nextInt();
							System.out.printf("\n arr[%d] = %s.\n",inputint,temp.get(inputint));						
						
						}
						catch(IndexOutOfBoundsException inboundExcp){
							System.out.println(inboundExcp);
						}
					}
					else if(c instanceof LinkedList){
						LinkedList temp = (LinkedList) c;
						
						try{
							System.out.println("Type index that you want to get.");
							inputint = input.nextInt();
							System.out.printf("\n arr[%d] = %s.\n",inputint,temp.get(inputint));						
						
						}
						catch(IndexOutOfBoundsException inboundExcp){
							System.out.println(inboundExcp);
						}					
					}
					
					else
						System.out.println("This operation only supported by List's.");
					break;
				case 12: // element operation
					if(c instanceof LinkedList){
						
						LinkedList temp = (LinkedList) c;
						try{
							System.out.printf("The head of queue is: %s\n",temp.element());
						}
						catch(NoSuchElementException noSuchExcp){
							System.out.println(noSuchExcp);
						}
					}						
					else
						System.out.println("This operation only supported by Queue's.");
					break;
				case 13: // offer operation		
					if(c instanceof LinkedList){
						
						LinkedList temp = (LinkedList) c;
						
						if(type == 0){
							inputint = input.nextInt();
							temp.offer(inputint);
						}
						if(type == 1){
							inputstr = input.nextLine();
							temp.offer(inputstr);
						}
					}
					else
						System.out.println("This operation only supported by Queue's.");				
					break;
				case 14: // poll operation
					if(c instanceof LinkedList){
						
						LinkedList temp = (LinkedList) c;
						try{
							temp.poll();
							System.out.println("The head of queue is removed");
						}
						catch(NoSuchElementException noSuchEExcp){
							System.out.println(noSuchEExcp);
						}
					}
					else
						System.out.println("This operation only supported by Queue's.");				
					break;
				case 15: // size
					System.out.printf("\nSize of collection is: %d\n",c.size());				
					break;		
				case 0:  // exit
					check = false;
					System.out.println("\n!HAVE A NICE DAY!");
					break;
				default:
					System.out.println("\nPlease select from menu!");
					break;
				}
			System.out.println(c);
		}while(check != false);
	}

	public static void main(String args[]){


		Scanner input = new Scanner(System.in);
		
		System.out.println("Select From Menu:");
		System.out.println("1-Test HashSet(Integer)");
		System.out.println("2-Test HashSet(String)");
		System.out.println("3-Test ArrayList(Integer)");
		System.out.println("4-Test ArrayList(String)");
		System.out.println("5-Test LinkedList(Integer)");
		System.out.println("6-Test LinkedList(String)");		
		
		try{	
			int choose = input.nextInt();
			switch(choose){
			
				case 1:	test(new HashSet<Integer>(),0);
					break;
				case 2:	test(new HashSet<String>(),1);
					break;			
				case 3:	test(new ArrayList<Integer>(),0);
					break;		
				case 4:	test(new ArrayList<String>(),1);
					break;		
				case 5:	test(new LinkedList<Integer>(),0);
					break;		
				case 6:	test(new LinkedList<String>(),1);
					break;		
				default: throw new InputMismatchException("You did not select from menu.\n");
			}
			
		}
		catch(InputMismatchException inexc){
			System.out.println(inexc);
		}
	}

}
