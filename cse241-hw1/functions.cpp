#include<iostream>
#include<string>
#include"functions.h"
using namespace std;

// printing the rules of game
void rules_of_game(){
	cout << "The Hex Rules:" << endl
		 << "1-Players choose a colour and take turns.On each turn one counter is placed in an hexagonal cell." << endl
		 << "2-The Blue side always starts first. " << endl
		 << "3-The first player to form a connected path of their counters linking the opposing sides of board marked by their colour wins." << endl
		 << "4-The four corner hexagons belong to both adjacent sides " << endl;
}

/* This function creates initial map (clean board). It fills every cells with '.' */
void create_initial_map(char map[12][12],int size){

	int i,j;

	for(i=0;i<size;++i)
		for(j=0;j<size;++j)
			map[i][j] = '.';

}

/* This function prints the game map with the given size */
void print_map(char map[12][12],int size){

	char c= 'a';
	int i,j,k;

	cout << endl << ' ';

	for(i=0;i<size;++i,++c)	// printing the letter(rows)
		cout << c << ' ';

	cout << endl;

	for(i=0;i<size;++i){
		cout << i+1;		// printing numbers(columns)
		if(i>=9)				// when the number is 10 or greater than 10,there must be one less whitespace, because 10 has two digit.
			for(k=0;k<i;k++)	// printing white spaces
				cout << ' ';
		else
			for(k=0;k<=i;k++)	// printing white spaces
				cout << ' ';
		for(j=0;j<size;++j)	// printing board
		cout << map[i][j] << ' ';

		cout << endl;
	}
}

/* This function gets board size from user and returns it to the main. Function keeps going till the user
 * types valid size.The check variable is false initially. When the user types valid input, variable will be true
 * and loop ends. */
int get_board_size(){
	int size;			// integer size variable for return
	bool check = false; // variable for condition

	do{
		cout << endl << "Please type the board size(for 8x8 board,type 8)(from 6x6 to 12x12) : ";
		cin >> size;

		if(size >= 6 && size <= 12 ) // checking whether the input value is in range or not
			check = true;
		else
			cerr << "You have typed invalid board size!Please type valid size." << endl;
	}while(check != true);
	cout << "Board size successfully received." << endl;
	return size;
}

/* This function gets game mode from user and returns it to the main. Function keeps going till the user
 * types valid input.
 * NOTE: in this function i used string for receiving input from user. To reason that, when user accidentally types
 * char instead of integer, program goes crazy. To prevent this, i used string. Then,i convert first element of
 * string to integer. */
int get_game_mode(){

	string input_mode;	//
	int mode;			// variable for return
	bool check = false;	// variable for condition

	do{
		cout << endl << "1-User vs User"
			 << endl << "2-User vs Computer"
			 << endl << "Please select the game mode: ";
		cin >> input_mode;
		mode = input_mode[0] - '0';
		if(mode==1 || mode==2)
			check = true;
		else
			cerr << endl << "You have typed invalid game mode!Please type valid mode.";
	}while(check != true);
	return mode;
}

/* This function for game mode 2(user vs computer).Takes color information from user and returns it to main.
 * The working principle is very similar to previous functions. */
int get_user_color(){

	string input_color;
	int color;
	bool check = false;

	do{
	cout << endl << "Please choose which side you want to play as a user." << endl
				 << "1 for Blue side(x)" << endl
				 << "2 for Red side(o)        :";
	cin >> input_color;
	color = input_color[0] -'0';
	if(color == 1 || color == 2)
		check = true;
	else
		cerr << "You typed invalid input.Please try again!" << endl;
	}while(check != true);

	return color;
}

/* This is game on function. This function continues the game. Function calls the proper function according the mode information. */
void game_on(char map[12][12],int size,int mode){

	int user_color;

	if(mode == 1){						// for user vs user mode
		cout << endl <<"User1 is playing on Blue side(x)." << endl
					 <<"User2 is playing on Red side(o)."  << endl;
		cout << endl << "Initial map is printing.." << endl;
		print_map(map,size);  			// printing initial map
		game_on_mode1(map,size);

	}
	else{								// for user vs computer mode
		user_color = get_user_color();  // determining user's side
		cout << endl << "Initial map is printing.." << endl;
		print_map(map,size);
		if(user_color == 1)				// if user's color is blue, the following function will call
			game_on_mode2_user_blue(map,size);
		else
			game_on_mode2_user_red(map,size);
	}
}

/* This function for playing first game mode(user vs user) */
void game_on_mode1(char map[12][12],int size){

	int row,column;
	int turn=0;			// Since this is turn base game,this variable for determining who will be make a move
	bool check = false;

	do{		// There is loop thats continues until one side wins
		if(turn%2 == 0){	 // if the turn is even number,it is turn of user1(blue side)
			cout << endl << "User1's turn(Blue Side)" << endl;
			get_move_from_user(map,size,&row,&column);	// getting move from user(coordinates)
			map[row][column] = 'x';	// editing map
			print_map(map,size);	// printing map
			if(win_check_for_blue(map,size) == true){	// checking the if the blue side wins or not. If blue side wins,check variable will
				cout << endl <<"!Game Over! The Blue Side(User1) Won!!" << endl;               	   // be true end loop ends.
				check = true;
			}
			turn++;
		}
		// very similar to blue side
		else if(turn%2 == 1){ // if the turn is odd number,it is turn of user2(red side)
			cout << endl << "User2's turn(Red Side)" << endl;
			get_move_from_user(map,size,&row,&column);	// getting move from user(coordinates)
			map[row][column] = 'o';
			print_map(map,size);
			if(win_check_for_red(map,size) == true){
				cout << endl <<"!Game Over! The Red Side(User2) Won!!" << endl;
				check = true;
			}
			turn++;
		}
	}while(check!= true);
}

/* This function for playing second game mode(user vs computer).Very similar to game_on_mode1() function.
 * In this situation, user is playing on blue side,computer is playing on red side.*/
void game_on_mode2_user_blue(char map[12][12],int size){

	int row,column;
	int turn = 0;
	bool check = false;

	do{
		if(turn%2 == 0){
			cout << endl << "User's turn(Blue Side)" << endl;
			get_move_from_user(map,size,&row,&column);
			map[row][column] = 'x';
			print_map(map,size);
			if(win_check_for_blue(map,size) == true){
				cout << endl <<"!Game Over! The Blue Side(User1) Won!!" << endl;
				check = true;
			}
			turn++;
		}
		else if(turn%2 == 1){
			cout << endl << "Computer is making move as a Red side" << endl;
			cout << "Computer move is: ";
			make_computer_move_red(map,size,row,column);	// computer makes move
			print_map(map,size);
			if(win_check_for_red(map,size) == true){
				cout << endl <<"!Game Over! The Red Side(Computer) Won!!" << endl;
				check = true;
			}
			turn++;
		}
	}while(check!= true);
}

/* Very similar to game_on_mode2_user_blue() function. Only difference is, user playing on red side, computer
 * playing on blue side. And computer starts first. */
void game_on_mode2_user_red(char map[12][12],int size){

	int row,column;
	int turn = 1;		// variable initially equals 1 in order to start the computer first.(because computer is blue side)
	bool check = false;

	do{
		if(turn%2 == 0){
			cout << endl << "User's turn(Red Side)" << endl;
			get_move_from_user(map,size,&row,&column);
			map[row][column] = 'o';
			print_map(map,size);
			if(win_check_for_red(map,size) == true){
				cout << endl <<"!Game Over! The Red Side(User1) Won!!" << endl;
				check = true;
			}
			turn++;
		}
		else if(turn%2 == 1){
			cout << endl << "Computer is making move as a Blue side" << endl;
			make_computer_move_blue(map,size,row,column);
			print_map(map,size);
			if(win_check_for_blue(map,size) == true){
				cout << endl <<"!Game Over! The Blue Side(Computer) Won!!" << endl;
				check = true;
			}
			turn++;
		}
	}while(check!= true);
}

/* This function gets valid move from user and returns it to called function with simulated references. */
void get_move_from_user(char map[12][12],int size,int *row,int *column){

	bool check = false;	// check variable for receive correct input(for loop)
	char temp_c;	   // temporary char variable for receiving  char from user

	do{
		cout << "Please make your move (as an example F5): ";
		cin.clear(); 			// clear the buffer
		cin >> temp_c >> *row;	// first received is column value second one is row value(letter is column, number is row)

		// when user types 5F instead of F5 loop goes crazy. To prevent this, this condition checking that cin operator fails or not
		if(cin.fail())
			cerr << "Please first type letter then number for example F5." << endl;
		else{
			*column = char_to_int(temp_c);	// converting char to corresponding integer value
			*row -=1;// removing 1 from row value because array is starting from 0
			if(check_validity_of_move(map,size,*row,*column) == true) // if is move valid, check variable will be true and loop ends.
				check = true;
			else
				cerr << "You typed invalid move.Typed cell is already occupied or you cross the board size."
				     <<	"Try again please" << endl;
		}

	}while(check != true);

}

/* This converts char to integer. */
int char_to_int(char c){
	return c - 'A';
}

/* This function checks that is move valid or not. It checks the cell is occupied or not and the given coordinates is in board or not. */
bool check_validity_of_move(char map[12][12],int size,int row, int column){

	// checking the cell is occupied or not and the given coordinates is in board or not
	if(map[row][column] == '.' && row < size && column < size)
		return  true;
	else
		return false;
}

/* This function checks the blue side win or not.
 * At least one cell must be occupied by blue side('x') in first column of board, in order to the winning condition.
 * Therefore, firstly program seeking this cell.If the cell is not found, program not interest with other cells and returns false.
 * When the cell is found, program starts from this cell and tries to reach other side(in other words win).Program does this reaching thing
 * recursively. When the blue side won, the connected cells will be upper case. */
bool win_check_for_blue(char map[12][12],int size){

	int i;
	bool check = false;

	for(i=0;i<size;++i){	// finding occupied cell in first column
		if(map[i][0]=='x')
			// checking whether is cell reach other side or not
			if(recursive_check_blue(map,size-1,i,0,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
				map[i][0] ='X';									// will be true.
				recursive_capital_blue(map,size,i,0);
				print_map(map,size);
				check = true;
			}
	}
	return check;
}

/* This function tries to reach other side recursively starting from given cell.It seek for occupied(with 'x') cell in the neighbors of given cell.
 * There is max 6 possible neighbors of cells. This function tries every possible neighbor.
 *
 * Also there is a counter variable for preventing infinite loops(segmentation faults).
 * This function max continues(call each other) (size+1)*(size+1) times.
 *
 * Function ends when there is no occupied neighbor or counter cross its limits.And returns false.
 * On the other hand,function ends when the opposite sites of map linked.The function can determined the opposite sites of map is linked or not
 * by looking the column number. If column number of last cell equals the size of map, the sites linked.And (in this case its blue) blue sides won.
 * And function returns true.
 */
bool recursive_check_blue(char map[12][12],int size,int r,int c,int counter){

		if(c==size)
			return true;
		else if(counter > (size+1)*(size+1))
			return false;
		else if(map[r][c+1] == 'x')
			return recursive_check_blue(map,size,r,c+1,++counter);
		else if(map[r+1][c] == 'x')
			return recursive_check_blue(map,size,r+1,c,++counter);
		else if(map[r-1][c+1] == 'x')
			return recursive_check_blue(map,size,r-1,c+1,++counter);
		else if(map[r-1][c] == 'x')
			return recursive_check_blue(map,size,r-1,c,++counter);
		else if(map[r+1][c-1] == 'x')
			return recursive_check_blue(map,size,r+1,c-1,++counter);
		else if(map[r][c-1] == 'x')
			return recursive_check_blue(map,size,r,c-1,++counter);
		else
			return false;
}

/* Very similar to win_check_for_blue() function. Only difference is,this function starts to seek from first row of board. */
bool win_check_for_red(char map[12][12],int size){

	int i;
	bool check = false;

	for(i=0;i<size;++i){
		if(map[0][i]=='o')
			if(recursive_check_red(map,size-1,0,i,0)==true){
				map[0][i]='O';
				recursive_capital_red(map,size,0,i);
				print_map(map,size);
				check = true;
			}
	}
	return check;
}

/* Very similar to recursive_check_blue() function. Only difference is, function returns true when the row number of cell equals the size of map. */
bool recursive_check_red(char map[12][12],int size,int r,int c,int counter){

		if(r==size)
			return true;
		else if(counter > (size+1)*(size+1))
			return false;
		else if(map[r+1][c] == 'o')
			return recursive_check_red(map,size,r+1,c,++counter);
		else if(map[r+1][c-1] == 'o')
			return recursive_check_red(map,size,r+1,c-1,++counter);
		else if(map[r][c+1] == 'o')
			return recursive_check_red(map,size,r,c+1,++counter);
		else if(map[r][c-1] == 'o')
			return recursive_check_red(map,size,r,c-1,++counter);
		else if(map[r-1][c+1] == 'o')
			return recursive_check_red(map,size,r-1,c+1,++counter);
		else if(map[r-1][c] == 'o')
			return recursive_check_red(map,size,r-1,c,++counter);
		else
			return false;
}

/* This function for making move for computer on red side.
 * The working principle is that, it receives the user's last moves coordinates(last occupied cell).
 * Then,tries to occupy it's(last occupied cell) neighbors(all 6 possible neighbors).
 * When there is no available cell on user's neighbor, then function tries to find available cell starting from top of the map(0,0 point).
 * And when function found available cell, occupy that cell and printing the coordinates of that cell to the screen.
 */
void make_computer_move_red(char map[12][12],int size,int user_r,int user_c){

	char c='A';
	int i,j,k;

	// checking all 6 possible neighbor of cell. Also checking that the possible cells is in board or not( -1 index of array or crossing size)
	if(user_c+1 <size && map[user_r][user_c+1] == '.'){
		map[user_r][user_c+1] = 'o';
		for(i=0;i<(user_c+1);++i)	// for printing letter of coordinate, incrementing 'A'.
			c++;
		cout << c << user_r+1 << endl;	// printing coordinate.
	}
	else if(user_r+1 <size && map[user_r+1][user_c] == '.'){
		map[user_r+1][user_c] = 'o';
		for(i=0;i<user_c;++i)
			c++;
		cout << c << user_r+2 << endl;
	}
	else if(user_r-1 >= 0 && user_c+1 <size && map[user_r-1][user_c+1] == '.'){
		map[user_r-1][user_c+1] = 'o';
		for(i=0;i<(user_c+1);++i)
			c++;
		cout << c << user_r << endl;
	}
	else if(user_r-1 >= 0 && map[user_r-1][user_c] == '.'){
		map[user_r-1][user_c] = 'o';
		for(i=0;i<(user_c);++i)
			c++;
		cout << c << user_r << endl;
	}
	else if(user_c-1 >= 0 && user_r+1 <size && map[user_r+1][user_c-1] == '.'){
		map[user_r+1][user_c-1] = 'o';
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+2 << endl;
	}
	else if(user_c-1 >= 0 && map[user_r][user_c-1] == '.'){
		map[user_r][user_c-1] = 'o';
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+1 << endl;
	}
	else{
		for(i=0;i<size;++i)
			for(j=0;j<size;++j)
				if(map[i][j] == '.'){
					map[i][j] = 'o';
					for(k=0;k<j;++k)
						c++;
					cout << c << i+1 << endl;
					return;
				}
	}
}

/* Very similar to make_computer_move_red() function.Only difference is for making moves on blue side. */
void make_computer_move_blue(char map[12][12],int size,int user_r,int user_c){

	char c = 'A';
	int i,j,k;

	if(user_r+1 <size && map[user_r+1][user_c] == '.'){
		map[user_r+1][user_c] = 'x';
		for(i=0;i<user_c;++i)
			c++;
		cout << c << user_r+1+1 << endl;
	}
	else if(user_r+1 < size && user_c-1 >=0 && map[user_r+1][user_c-1] == '.'){
		map[user_r+1][user_c-1] = 'x';
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+1+1 << endl;
	}
	else if(user_c+1 < size && map[user_r][user_c+1] == '.'){
		map[user_r][user_c+1] = 'x';
		for(i=0;i<(user_c+1);++i)
			c++;
		cout << c << user_r+1 << endl;
	}
	else if(user_c-1 >=0 && map[user_r][user_c-1] == '.'){
		map[user_r][user_c-1] = 'x';
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+1 << endl;
	}
	else if(user_r-1 >=0 && user_c+1 < size && map[user_r-1][user_c+1] == '.'){
		map[user_r-1][user_c+1] = 'x';
		for(i=0;i<(user_c+1);++i)
			c++;
		cout << c << user_r-1+1 << endl;
	}
	else if(user_r-1 >=0 && map[user_r-1][user_c] == '.'){
		map[user_r-1][user_c] = 'x';
		for(i=0;i<user_c;++i)
			c++;
		cout << c << user_r-1+1 << endl;
	}
	else{
		for(i=0;i<size;++i)
			for(j=0;j<size;++j)
				if(map[i][j] == '.'){
					map[i][j] = 'x';
					for(k=0;k<user_c;++k)
						c++;
					cout << c << i+1 << endl;
					return;
				}
	}
}

/* This function is very similar to recursive_check_blue() function.
 * Only difference is this function make upper case of occupied cells on blue side.
 * In order to print the final map. */
bool recursive_capital_blue(char map[12][12],int size,int r,int c){

		if(c==size)
			return true;
		else if(map[r][c+1] == 'x'){
			map[r][c+1]='X';
			return recursive_capital_blue(map,size,r,c+1);
		}
		else if(map[r+1][c] == 'x'){
			map[r+1][c]='X';
			return recursive_capital_blue(map,size,r+1,c);
		}
		else if(map[r-1][c+1] == 'x'){
			map[r-1][c+1]='X';
			return recursive_capital_blue(map,size,r-1,c+1);
		}
		else if(map[r-1][c] == 'x'){
			map[r-1][c]='X';
			return recursive_capital_blue(map,size,r-1,c);
		}
		else if(map[r+1][c-1] == 'x'){
			map[r+1][c-1]='X';
			return recursive_capital_blue(map,size,r+1,c-1);
		}
		else if(map[r][c-1] == 'x'){
			map[r][c-1]='X';
			return recursive_capital_blue(map,size,r,c-1);
		}
		else
			return false;
}

/* Very similar to recursive_capital_red function() function .Only difference is this function make upper case of occupied cells on red side */
bool recursive_capital_red(char map[12][12],int size,int r,int c){

		if(r==size)
			return true;
		else if(map[r+1][c] == 'o'){
			map[r+1][c] = 'O';
			return recursive_capital_red(map,size,r+1,c);
		}
		else if(map[r+1][c-1] == 'o'){
			map[r+1][c-1] = 'O';
			return recursive_capital_red(map,size,r+1,c-1);
		}
		else if(map[r][c+1] == 'o'){
			map[r][c+1] = 'O';
			return recursive_capital_red(map,size,r,c+1);
		}
		else if(map[r][c-1] == 'o'){
			map[r][c-1] = 'O';
			return recursive_capital_red(map,size,r,c-1);
		}
		else if(map[r-1][c+1] == 'o'){
			map[r-1][c+1] = 'O';
			return recursive_capital_red(map,size,r-1,c+1);
		}
		else if(map[r-1][c] == 'o'){
			map[r-1][c] = 'O';
			return recursive_capital_red(map,size,r-1,c);
		}
		else
			return false;
}











