#include<iostream>
#include<string>
#include<fstream>
#include"functions.h"
using namespace std;

enum cell_states{ notOccupied = '.', occupiedBlue = 'x', occupiedRed = 'o',winBlue  = 'X', winRed = 'O'};
enum user_operations{ loadOperation = 1, saveOperation = 2, moveOperation = 0, errorOperation = -1};
enum GameInfo{ sizeInfo = 0, modeInfo = 1, turnInfo = 2};


// printing the rules of game
void rules_of_game(){
	cout << "The Hex Rules:" << endl
		 << "1-Players choose a colour and take turns.On each turn one counter is placed in an hexagonal cell." << endl
		 << "2-The Blue side always starts first. " << endl
		 << "3-The first player to form a connected path of their counters linking the opposing sides of board marked by their colour wins." << endl
		 << "4-The four corner hexagons belong to both adjacent sides " << endl;
}

/* This function creates initial map (clean board). It fills every cells with notOccupied */
void create_initial_map(char map[12][12],int size){

	int i,j;

	for(i=0;i<size;++i)
		for(j=0;j<size;++j)
			map[i][j] = notOccupied;

}

/* This function prints the game map with the given size */
void print_map(const char map[12][12],const int size){

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
	string input_size;	//
	int size;			// integer size variable for return
	bool check = false; // variable for condition

	do{
		cout << endl << "Please type the board size(for 8x8 board,type 8)(from 6x6 to 12x12) : ";
		getline(cin,input_size);	// receiving input with getline.because '\n' remains otherwise.
		size = stoi(input_size);	// converting number string to int type with stoi() function(c++11 feature)

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
		getline(cin,input_mode);	// receiving input with getline.because '\n' remains otherwise.
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
	getline(cin,input_color);		// receiving input with getline.because '\n' remains otherwise.
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

	int user_color = 1;
	int game_continue = 0;		// variable for loaded game info. When the game is loaded this variable will be 1.
	int gameInfo[3];			// gameInfo array for saving and loading game from file.Holds size,game mode and turn informations.
	gameInfo[sizeInfo] = size;
	gameInfo[modeInfo] = mode;

	do{
	if(mode == 1 && game_continue == 0){						// for user vs user mode
		cout << endl <<"User1 is playing on Blue side(x)." << endl
					 <<"User2 is playing on Red side(o)."  << endl;
		cout << endl << "Initial map is printing.." << endl;
		print_map(map,size);  			// printing initial map
		game_on_mode1(map,gameInfo,game_continue);

	}
	if(mode == 2 && game_continue == 0){								// for user vs computer mode
		user_color = get_user_color();  // determining user's side
		cout << endl << "Initial map is printing.." << endl;
		print_map(map,size);
		if(user_color == 1)				// if user's color is blue, the following function will call
			game_on_mode2_user_blue(map,gameInfo,game_continue);
		else
			game_on_mode2_user_red(map,gameInfo,game_continue);
	}
	if(game_continue == 1){		// condition for loaded game.
		game_continue = 0;		// resetting variable
		print_saved_game(map,gameInfo);	// printing loaded game informations and map.
		if(gameInfo[modeInfo] == 1)
			game_on_mode1(map,gameInfo,game_continue,gameInfo[turnInfo]);
		if(gameInfo[modeInfo] == 2 && gameInfo[turnInfo] == 0)
			game_on_mode2_user_blue(map,gameInfo,game_continue,gameInfo[turnInfo]);
		if(gameInfo[modeInfo] == 2 && gameInfo[turnInfo] == 1)
			game_on_mode2_user_red(map,gameInfo,game_continue,gameInfo[turnInfo]);
	}
	}while(game_continue!=2);	// this is end condition. when some game(loaded or created) finishes, program ends.
}

/* This function for printing loaded game informations and map to the terminal. */
void print_saved_game(const char map[12][12],const int gameInfo[3]){

	cout << endl << "Game is successfully loaded from save file." << endl;
	cout << "Loaded Game Stats is:" << endl;
	cout << "Board Size: " << gameInfo[sizeInfo] << endl;
	cout << "Game Mode: ";
	if(gameInfo[modeInfo] == 1)
		cout << "User vs User" << endl;
	else
		cout << "User vs Computer" << endl;
	cout << "Turn: ";
	if(gameInfo[turnInfo] == 0)
		cout << "Blue Side Turn" << endl;
	else
		cout << "Red Side Turn" << endl;
	cout << "Saved game loading..." << endl;

	print_map(map,gameInfo[sizeInfo]);

}

/* This function for playing first game mode(user vs user) */
void game_on_mode1(char map[12][12],int gameInfo[3],int &game_continue,int turn){
	// Since this is turn base game,this variable for determining who will be make a move
	// note that turn is a default parameter. When the program works normally(not load game), its value will be 0 by default.
	int row,column;
	bool check = false;

	do{		// There is loop thats continues until one side wins
		if(turn%2 == 0){	 // if the turn is even number,it is turn of user1(blue side)
			cout << endl << "User1's turn(Blue Side)" << endl;
			gameInfo[turnInfo] = 0;	 // saving turn info.
			get_move_from_user(map,gameInfo[sizeInfo],row,column,gameInfo,game_continue);	// getting move from user(coordinates)
			if(game_continue == 1)	return;		  // when the user select LOAD operation. Function ends here.
			map[row][column] = occupiedBlue;	 // editing map
			print_map(map,gameInfo[sizeInfo]);	// printing map
			if(win_check_for_blue(map,gameInfo[sizeInfo]) == true){	// checking the if the blue side wins or not. If blue side wins,check variable will
				cout << endl <<"!Game Over! The Blue Side(User1) Won!!" << endl;               	   // be true end loop ends.
				game_continue = 2;				// end condition for program.
				check = true;
			}
			turn++;
		}
		// very similar to blue side
		else if(turn%2 == 1){ // if the turn is odd number,it is turn of user2(red side)
			cout << endl << "User2's turn(Red Side)" << endl;
			gameInfo[turnInfo] = 1;
			get_move_from_user(map,gameInfo[sizeInfo],row,column,gameInfo,game_continue);	// getting move from user(coordinates)
			if(game_continue == 1)	return;
			map[row][column] = occupiedRed;
			print_map(map,gameInfo[sizeInfo]);

			if(win_check_for_red(map,gameInfo[sizeInfo]) == true){
				cout << endl <<"!Game Over! The Red Side(User2) Won!!" << endl;
				game_continue = 2;
				check = true;
			}
			turn++;
		}
	}while(check!= true);
}

/* This function for playing second game mode(user vs computer).Very similar to game_on_mode1() function.
 * In this situation, user is playing on blue side,computer is playing on red side.*/
void game_on_mode2_user_blue(char map[12][12],int gameInfo[3],int &game_continue,int turn){

	int row,column;
	bool check = false;

	do{
		if(turn%2 == 0){
			cout << endl << "User's turn(Blue Side)" << endl;
			gameInfo[turnInfo] = 0;
			get_move_from_user(map,gameInfo[sizeInfo],row,column,gameInfo,game_continue);
			if(game_continue == 1)	return;
			map[row][column] = occupiedBlue;
			print_map(map,gameInfo[sizeInfo]);

			if(win_check_for_blue(map,gameInfo[sizeInfo]) == true){
				cout << endl <<"!Game Over! The Blue Side(User1) Won!!" << endl;
				game_continue = 2;
				check = true;
			}
			turn++;
		}
		else if(turn%2 == 1){
			cout << endl << "Computer is making move as a Red side" << endl;
			gameInfo[turnInfo] = 1;
			cout << "Computer move is: ";
			make_computer_move_red(map,gameInfo[sizeInfo],row,column);	// computer makes move
			print_map(map,gameInfo[sizeInfo]);

			if(win_check_for_red(map,gameInfo[sizeInfo]) == true){
				cout << endl <<"!Game Over! The Red Side(Computer) Won!!" << endl;
				game_continue = 2;
				check = true;
			}
			turn++;
		}
	}while(check!= true);
}

/* Very similar to game_on_mode2_user_blue() function. Only difference is, user playing on red side, computer
 * playing on blue side. And computer starts first. */
void game_on_mode2_user_red(char map[12][12],int gameInfo[3],int &game_continue,int turn){

	// turn variable default equals 1 in order to start the computer first.(because computer is blue side)
	int row = 0,column = 0;
	bool check = false;

	do{
		if(turn%2 == 0){
			cout << endl << "User's turn(Red Side)" << endl;
			gameInfo[turnInfo] = 1;
			get_move_from_user(map,gameInfo[sizeInfo],row,column,gameInfo,game_continue);
			if(game_continue == 1)	return;
			map[row][column] = occupiedRed;
			print_map(map,gameInfo[sizeInfo]);

			if(win_check_for_red(map,gameInfo[sizeInfo]) == true){
				cout << endl <<"!Game Over! The Red Side(User1) Won!!" << endl;
				game_continue = 2;
				check = true;
			}
			turn++;
		}
		else if(turn%2 == 1){
			cout << endl << "Computer is making move as a Blue side" << endl;
			gameInfo[turnInfo] = 0;
			make_computer_move_blue(map,gameInfo[sizeInfo],row,column);
			print_map(map,gameInfo[sizeInfo]);

			if(win_check_for_blue(map,gameInfo[sizeInfo]) == true){
				cout << endl <<"!Game Over! The Blue Side(Computer) Won!!" << endl;
				game_continue = 2;
				check = true;
			}
			turn++;
		}
	}while(check!= true);
}

/* This function gets valid move from user and returns it to called function with by reference.Also gets load or save operations */
void get_move_from_user(char map[12][12],int size,int& row,int& column,int gameInfo[3],int& game_continue){

	string fileName;
	bool check = false;	// check variable for receive correct input(for loop)
	char temp_c;	   // temporary char variable for receiving  char from user

	do{

		cout << "Please make your move (as an example F5): ";
		auto operation = getOperationInfo(fileName,row,temp_c);		// receiving operation

		if(operation == loadOperation || operation == saveOperation){

			check = performOperations(map,gameInfo,fileName,operation);	// performing load and save operations
			if(operation == loadOperation)	// condition for load operation
				game_continue = 1;
		}

		else if(operation == moveOperation){		// move operation
			column = char_to_int(temp_c);	// converting char to corresponding integer value
			row -=1;// removing 1 from row value because array is starting from 0
			if(check_validity_of_move(map,size,row,column) == true) // if is move valid, check variable will be true and loop ends.
				check = true;
			else
				cerr << "You typed invalid move.Typed cell is already occupied or you cross the board size."
				     <<	"Try again please" << endl;
		}
		else if(operation == errorOperation)//
			cerr << "Something went wrong.Please try again!!" << endl;

	}while(check != true);
}

/* This function opens files and performs operations(save and load) on them.*/
bool performOperations(char map[12][12],int gameInfo[3],const string& fileName,const int& operation){

	ifstream loadFile;
	ofstream saveFile;

	if(operation == loadOperation){

		loadFile.open(fileName.c_str());
		if(loadFile.fail()){	// when file could not opened.function ends.
			cerr << fileName << " file could not opened. Please try again!" << endl;
		}
		else{
			cout << endl << "Game loading, please wait..." << endl;
			performLoadOperation(loadFile,map,gameInfo);
			loadFile.close();
			return true;
		}
	}
	else if(operation == saveOperation){


		saveFile.open(fileName.c_str());
		cout << endl << "Saving game...Please do no turn off your system.Please wait..." << endl;
		performSaveOperation(saveFile,map,gameInfo);
		cout << endl << "Game has successfully saved." << endl;
		saveFile.close();
	}
	return false;
}

/* This function gets input from user and form it to proper way. */
int getOperationInfo(string& fileName,int& row,char& column){

	string input_str,operation;
	decltype(input_str) temp;
	string space_delimeter = " ";	// delimeter for parsing operation and filename
	string checkTXT = ".TXT";		// delimeter for checking file extension
	string checktxt = ".txt";		// delimeter for checking file extension
	string load_operation = "LOAD";
	string save_operation = "SAVE";
	int rtrn_operation;

		getline(cin,input_str);

	if(input_str.substr(0,input_str.find(space_delimeter)) == load_operation ){	//making first parsing
		fileName = input_str.substr(input_str.find(space_delimeter)+1);			// parsing filename
		if(fileName.find(checkTXT) !=  string::npos || fileName.find(checktxt) !=  string::npos)	// checking that file extension is correct or not
			rtrn_operation = loadOperation;
		else{
			cerr <<"You typed invalid file extension.Please try again!" << endl;
			rtrn_operation = errorOperation;
		}
	}
	else if(input_str.substr(0,input_str.find(space_delimeter)) == save_operation ){
		fileName = input_str.substr(input_str.find(space_delimeter)+1);
		if(fileName.find(checkTXT) !=  string::npos || fileName.find(checktxt) !=  string::npos)
			rtrn_operation = saveOperation;
		else{
			cerr <<"You typed invalid file extension." << endl;
			rtrn_operation = errorOperation;
		}

	}
	else{	 // condition for move operation

		column = input_str[0];
		if(column < 'A')	// condition for handle with invalid input such as  5F instead of F5
			rtrn_operation = errorOperation;
		else{
			temp = input_str.substr(1);
			row    = stoi(temp);
		rtrn_operation = moveOperation;
		}
	}
	return rtrn_operation;
}

/* This function reads from file and save it to gameInfo array and map array. */
void performLoadOperation(ifstream& fileStream,char map[12][12],int gameInfo[3]){

	string temp_str;
	string colon_delimeter = ":";
	string token_str;
	char input_c;

	for(int i=0;i<3;++i){
			getline(fileStream,temp_str);
			token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
			gameInfo[i] = stoi(token_str);
	}
	for(int i=0;i<gameInfo[sizeInfo];++i){	// reading map from file.
		for(int j=0; j<gameInfo[sizeInfo];++j){
			fileStream >> input_c;
			if(input_c != '\n')
				map[i][j] = input_c;
		}
	}
	//fileStream.close();
}

/* This function writes gameInfo array and map array to the file.*/
void performSaveOperation(ofstream& fileStream,char map[12][12],int gameInfo[3]){

	fileStream << "Board Size:" << gameInfo[sizeInfo] << "\n";
	fileStream << "Game Mode:" << gameInfo[modeInfo] << "\n";
	fileStream << "Turn:" << gameInfo[turnInfo] << "\n";
	for(int i=0;i<gameInfo[sizeInfo];++i){	// writing map to the file.
			for(int j=0; j<gameInfo[sizeInfo];++j)
				fileStream << map[i][j];
			fileStream << "\n";
	}
	//fileStream.close();
}

/* This converts char to integer. */
int char_to_int(char c){

	return c - 'A';
}

/* This function checks that is move valid or not. It checks the cell is occupied or not and the given coordinates is in board or not. */
bool check_validity_of_move(const char map[12][12],const int& size,const int& row,const int& column){

	// checking the cell is occupied or not and the given coordinates is in board or not
	if(map[row][column] == notOccupied && row < size && column < size)
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
		if(map[i][0]== occupiedBlue)
			// checking whether is cell reach other side or not
			if(recursive_check_blue(map,size-1,i,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
				map[i][0] = winBlue;									// will be true.
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
		else if(map[r][c+1] == occupiedBlue)
			return recursive_check_blue(map,size,r,c+1,++counter);
		else if(map[r+1][c] == occupiedBlue)
			return recursive_check_blue(map,size,r+1,c,++counter);
		else if(map[r-1][c+1] == occupiedBlue)
			return recursive_check_blue(map,size,r-1,c+1,++counter);
		else if(map[r-1][c] == occupiedBlue)
			return recursive_check_blue(map,size,r-1,c,++counter);
		else if(map[r+1][c-1] == occupiedBlue)
			return recursive_check_blue(map,size,r+1,c-1,++counter);
		else if(map[r][c-1] == occupiedBlue)
			return recursive_check_blue(map,size,r,c-1,++counter);
		else
			return false;
}

/* Very similar to win_check_for_blue() function. Only difference is,this function starts to seek from first row of board. */
bool win_check_for_red(char map[12][12],int size){

	int i;
	bool check = false;

	for(i=0;i<size;++i){
		if(map[0][i]==occupiedRed)
			if(recursive_check_red(map,size-1,0,i,0)==true){
				map[0][i]=winRed;
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
		else if(map[r+1][c] == occupiedRed)
			return recursive_check_red(map,size,r+1,c,++counter);
		else if(map[r+1][c-1] == occupiedRed)
			return recursive_check_red(map,size,r+1,c-1,++counter);
		else if(map[r][c+1] == occupiedRed)
			return recursive_check_red(map,size,r,c+1,++counter);
		else if(map[r][c-1] == occupiedRed)
			return recursive_check_red(map,size,r,c-1,++counter);
		else if(map[r-1][c+1] == occupiedRed)
			return recursive_check_red(map,size,r-1,c+1,++counter);
		else if(map[r-1][c] == occupiedRed)
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
	if(user_c+1 <size && map[user_r][user_c+1] == notOccupied){
		map[user_r][user_c+1] = occupiedRed;
		for(i=0;i<(user_c+1);++i)	// for printing letter of coordinate, incrementing 'A'.
			c++;
		cout << c << user_r+1 << endl;	// printing coordinate.
	}
	else if(user_r+1 <size && map[user_r+1][user_c] == notOccupied){
		map[user_r+1][user_c] = occupiedRed;
		for(i=0;i<user_c;++i)
			c++;
		cout << c << user_r+2 << endl;
	}
	else if(user_r-1 >= 0 && user_c+1 <size && map[user_r-1][user_c+1] == notOccupied){
		map[user_r-1][user_c+1] = occupiedRed;
		for(i=0;i<(user_c+1);++i)
			c++;
		cout << c << user_r << endl;
	}
	else if(user_r-1 >= 0 && map[user_r-1][user_c] == notOccupied){
		map[user_r-1][user_c] = occupiedRed;
		for(i=0;i<(user_c);++i)
			c++;
		cout << c << user_r << endl;
	}
	else if(user_c-1 >= 0 && user_r+1 <size && map[user_r+1][user_c-1] == notOccupied){
		map[user_r+1][user_c-1] = occupiedRed;
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+2 << endl;
	}
	else if(user_c-1 >= 0 && map[user_r][user_c-1] == notOccupied){
		map[user_r][user_c-1] = occupiedRed;
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+1 << endl;
	}
	else{
		for(i=0;i<size;++i)
			for(j=0;j<size;++j)
				if(map[i][j] == notOccupied){
					map[i][j] = occupiedRed;
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

	if(user_r+1 <size && map[user_r+1][user_c] == notOccupied){
		map[user_r+1][user_c] = occupiedBlue;
		for(i=0;i<user_c;++i)
			c++;
		cout << c << user_r+1+1 << endl;
	}
	else if(user_r+1 < size && user_c-1 >=0 && map[user_r+1][user_c-1] == notOccupied){
		map[user_r+1][user_c-1] = occupiedBlue;
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+1+1 << endl;
	}
	else if(user_c+1 < size && map[user_r][user_c+1] == notOccupied){
		map[user_r][user_c+1] = occupiedBlue;
		for(i=0;i<(user_c+1);++i)
			c++;
		cout << c << user_r+1 << endl;
	}
	else if(user_c-1 >=0 && map[user_r][user_c-1] == notOccupied){
		map[user_r][user_c-1] = occupiedBlue;
		for(i=0;i<(user_c-1);++i)
			c++;
		cout << c << user_r+1 << endl;
	}
	else if(user_r-1 >=0 && user_c+1 < size && map[user_r-1][user_c+1] == notOccupied){
		map[user_r-1][user_c+1] = occupiedBlue;
		for(i=0;i<(user_c+1);++i)
			c++;
		cout << c << user_r-1+1 << endl;
	}
	else if(user_r-1 >=0 && map[user_r-1][user_c] == notOccupied){
		map[user_r-1][user_c] = occupiedBlue;
		for(i=0;i<user_c;++i)
			c++;
		cout << c << user_r-1+1 << endl;
	}
	else{
		for(i=0;i<size;++i)
			for(j=0;j<size;++j)
				if(map[i][j] == notOccupied){
					map[i][j] = occupiedBlue;
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
		else if(map[r][c+1] == occupiedBlue){
			map[r][c+1]=winBlue;
			return recursive_capital_blue(map,size,r,c+1);
		}
		else if(map[r+1][c] == occupiedBlue){
			map[r+1][c]=winBlue;
			return recursive_capital_blue(map,size,r+1,c);
		}
		else if(map[r-1][c+1] == occupiedBlue){
			map[r-1][c+1]=winBlue;
			return recursive_capital_blue(map,size,r-1,c+1);
		}
		else if(map[r-1][c] == occupiedBlue){
			map[r-1][c]=winBlue;
			return recursive_capital_blue(map,size,r-1,c);
		}
		else if(map[r+1][c-1] == occupiedBlue){
			map[r+1][c-1]=winBlue;
			return recursive_capital_blue(map,size,r+1,c-1);
		}
		else if(map[r][c-1] == occupiedBlue){
			map[r][c-1]=winBlue;
			return recursive_capital_blue(map,size,r,c-1);
		}
		else
			return false;
}

/* Very similar to recursive_capital_red function() function .Only difference is this function make upper case of occupied cells on red side */
bool recursive_capital_red(char map[12][12],int size,int r,int c){

		if(r==size)
			return true;
		else if(map[r+1][c] == occupiedRed){
			map[r+1][c] = winRed;
			return recursive_capital_red(map,size,r+1,c);
		}
		else if(map[r+1][c-1] == occupiedRed){
			map[r+1][c-1] = winRed;
			return recursive_capital_red(map,size,r+1,c-1);
		}
		else if(map[r][c+1] == occupiedRed){
			map[r][c+1] = winRed;
			return recursive_capital_red(map,size,r,c+1);
		}
		else if(map[r][c-1] == occupiedRed){
			map[r][c-1] = winRed;
			return recursive_capital_red(map,size,r,c-1);
		}
		else if(map[r-1][c+1] == occupiedRed){
			map[r-1][c+1] = winRed;
			return recursive_capital_red(map,size,r-1,c+1);
		}
		else if(map[r-1][c] == occupiedRed){
			map[r-1][c] = winRed;
			return recursive_capital_red(map,size,r-1,c);
		}
		else
			return false;
}


