#include<iostream>
#include<vector>
#include"header.h"
#include<string>
#include<fstream>
using namespace std;
using std::string;
using std::ofstream;
using std::ifstream;


enum cell_states{ notOccupied = '.', occupiedBlue = 'x', occupiedRed = 'o',winBlue  = 'X', winRed = 'O'};
enum user_operations{saveOperation = 2, menuOperation=3,moveOperation = 1, errorOperation = -1};


/* constructors */

Hex::Hex(int size,int mode)
		:inputRow(0),inputColumn('A'),markedCells(0),operation(0),turn(0),hexCells(size,vector<Cell>(size))
{
	setSize(size);
	setMode(mode);
}
Hex::Hex(int size) : Hex(size,1)
{/* Intentionally empty */}

Hex::Hex() : Hex(5,1)
{/* Intentionally empty */}

/* getters functions */

inline int Hex::getTurn() const {return turn;}
inline int Hex::getSize() const {return boardSize;}
inline int Hex::getMode() const {return gameMode;}
inline int Hex::getInputRow()  const {return inputRow;}
inline int Hex::getInputColumn() const {return inputColumn;}
inline int Hex::getMarkedCells() const {return markedCells;}
inline int Hex::getOperation() const {return operation;}
inline string Hex::getFileName()const{ return fileName;}


/* setter functions. */

bool Hex::setSize(int size){
	if(size < 5){
		cerr << endl << "You have typed invalid board size";
		return false;
	}
	boardSize = size;
	return true;
}
bool Hex::setMode(int mode){

	if(mode != 1 && mode!= 2){
		cerr << endl << "You have typed invalid game mode";
		return false;
	}
	gameMode = mode;
	return true;
}
inline void Hex::setTurn(int t){ turn = t;}
inline void Hex::decreaseTurn(){turn--;}
inline void Hex::increaseTurn() { turn++;}
inline void Hex::setOperation(int oprt) { operation = oprt;}
inline void Hex::setInputRow(int row){ inputRow = row-1; }
inline void Hex::setInputColumn(char column){inputColumn = column-'A';}
void Hex::setMarkedCells(int value){ markedCells = value; }
inline void Hex::increaseMarkedCells(){
	markedCells++;
	allMarked++;
}

bool Hex::setFileName(string str){
	string checktxt = ".txt";
	string checkTXT = ".TXT";
	if(str.find(checkTXT) !=  string::npos || str.find(checktxt) !=  string::npos){
		fileName = str;
		return true;
	}
	else{
		cerr <<"You typed invalid file extension.Please try again!" << endl;
		return false;
	}
}

/* This function resize the board(vector) according to input size(user determined). Also print board with '.' . */
void Hex::setHexCells(){
	hexCells = vector< vector<Cell> >(getSize(),vector<Cell>(getSize()));

	for(int i=0;i < getSize();++i)
		for(int j=0;j <getSize();++j)
			hexCells[i][j].setData(notOccupied);
}

/* This function prints the board to the screen. */
void Hex::displayBoard()const{

	char c= 'a';
	int i,j,k;

	cout << endl << ' ';

	for(i=0;i<getSize();++i,++c)	// printing the letter(rows)
		cout << c << ' ';

	cout << endl;

	for(i=0;i<getSize();++i){
		cout << i+1;		// printing numbers(columns)
		if(i>=9)				// when the number is 10 or greater than 10,there must be one less whitespace, because 10 has two digit.
			for(k=0;k<i;k++)	// printing white spaces
				cout << ' ';
		else
			for(k=0;k<=i;k++)	// printing white spaces
				cout << ' ';
		for(j=0;j<getSize();++j){	// printing board
			cout << hexCells[i][j].getData() << ' ';
		}
		cout << endl;
	}
}

/* This is function that plays game. It takes board size and game mode from user.*/
void Hex::playGame(){
	string input;
	do{
		cout << endl << "Please type the board size(for 8x8 board,type 8)(min 5x5) : ";
		getline(cin,input);
	}while(!setSize(stoi(input)));	//for receive valid input
	do{
		cout << endl << "1-User vs User"
			 << endl << "2-User vs Computer"
			 << endl << "Please select the game mode: ";
		getline(cin,input);
	}while(!setMode(stoi(input))); //for receive valid input
	setHexCells();	// resizeing board
	playGameModes();

}

/* Function for UservsUser mode. Very similar to playMode2 function. */
void Hex::playMode1(){

		if(getTurn()%2 == 0){
			cout << endl << "User1's turn(Blue Side)" << endl;
			getInput();
			increaseTurn();
			switch(getOperation()){
				case menuOperation: {
					decreaseTurn();
					return;
					break;
				}
				case saveOperation:{
					saveFile();
					decreaseTurn();
					return;
					break;
				}
			}
			play(getInputRow(),getInputColumn());
			displayBoard();
		}
		else if(getTurn()%2 == 1){
			cout << endl << "User2's turn(Red Side)" << endl;
			getInput();
			increaseTurn();
			switch(getOperation()){
				case menuOperation: {
					decreaseTurn();
					return;
					break;
				}
				case saveOperation:{
					decreaseTurn();
					saveFile();
					return;
					break;
				}
			}
			play(getInputRow(),getInputColumn());
			displayBoard();
		}
}

/* Function for UservsComputer mode. */
void Hex::playMode2(){
	if(getTurn()%2 == 0){	// blue side turn
		cout << endl << "User1's turn(Blue Side)" << endl;
		getInput();
		increaseTurn();
		switch(getOperation()){
			case menuOperation: {	// if the input is "MENU" function ends and returns menu
				decreaseTurn();		// decrease turn in order to play correct side when switch back to game
				return;
				break;
			}
			case saveOperation:{	// if the input is "SAVE" function performs save operation and ends
				decreaseTurn();		// decrease the turn in order to make move after save operation
				saveFile();
				return;
				break;
			}
		}
		play(getInputRow(),getInputColumn());
		displayBoard();
	}
	else if(getTurn()%2 == 1){	// red side turn
			cout << endl << "Computer's turn(Red Side)" << endl;
			cout << "Computer's move is: ";
			increaseTurn();
			play();
			displayBoard();
	}
}


/* This function gets input from user and parse it properly. */
string Hex::getInput(){

	bool check=false;
	string input;
	do{
		cout << "Please make your move (as an example F5)(MENU for return menu)(SAVE filename.txt for save game): ";
		getline(cin,input);
		parseString(input);	// parsing string
		if(getOperation() == saveOperation || getOperation() == menuOperation)
			check = true;
		else if(getOperation() == moveOperation)
			if(checkValidMove())
				check = true;
	}while(!check);
	return input;
}

/* This function checks that given coordinate is valid or not .*/
bool Hex::checkValidMove(){

	if(hexCells[getInputRow()][getInputColumn()].getData() ==  notOccupied && getInputRow() < getSize() && getInputColumn() < ('A'+getSize()))
		return true;
	else{
		cerr << "You typed invalid move.Typed cell is already occupied or you cross the board size."
			 <<	"Try again please" << endl;
		return false;
	}
}

/* This is user play function.It makes move according to given coordinates.When the turn % 2 == 1 it is blue sides turn.
 * Otherwise red sides turn. */
void Hex::play(int row,int column){
	increaseMarkedCells();
	if(getTurn()%2 == 1)
		hexCells[row][column].setData(occupiedBlue);
	else
		hexCells[row][column].setData(occupiedRed);
}

/* This function make moves for computer. The algorithm very similar to hw1. */
void Hex::play(){

	char c='A';
	int i,j,k;
	increaseMarkedCells();
	// checking all 6 possible neighbor of cell. Also checking that the possible cells is in board or not( -1 index of array or crossing size)
	if(getInputColumn()+1 <getSize() && hexCells[getInputRow()][getInputColumn()+1].getData() == notOccupied){
		hexCells[getInputRow()][getInputColumn()+1].setData(occupiedRed);
		for(i=0;i<(getInputColumn()+1);++i)	// for printing letter of coordinate, incrementing 'A'.
			c++;
		cout << c << getInputRow()+1 << endl;	// printing coordinate.
	}
	else if(getInputRow()+1 <getSize() && hexCells[getInputRow()+1][getInputColumn()].getData() == notOccupied){
		hexCells[getInputRow()+1][getInputColumn()].setData(occupiedRed);
		for(i=0;i<getInputColumn();++i)
			c++;
		cout << c << getInputRow()+2 << endl;
	}
	else if(getInputRow()-1 >= 0 && getInputColumn()+1 <getSize() && hexCells[getInputRow()-1][getInputColumn()+1].getData() == notOccupied){
		hexCells[getInputRow()-1][getInputColumn()+1].setData(occupiedRed);
		for(i=0;i<(getInputColumn()+1);++i)
			c++;
		cout << c << getInputRow() << endl;
	}
	else if(getInputRow()-1 >= 0 && hexCells[getInputRow()-1][getInputColumn()].getData() == notOccupied){
		hexCells[getInputRow()-1][getInputColumn()].setData(occupiedRed);
		for(i=0;i<(getInputColumn());++i)
			c++;
		cout << c << getInputRow() << endl;
	}
	else if(getInputColumn()-1 >= 0 && getInputRow()+1 <getSize() && hexCells[getInputRow()+1][getInputColumn()-1].getData() == notOccupied){
		hexCells[getInputRow()+1][getInputColumn()-1].setData(occupiedRed);
		for(i=0;i<(getInputColumn()-1);++i)
			c++;
		cout << c << getInputRow()+2 << endl;
	}
	else if(getInputColumn()-1 >= 0 && hexCells[getInputRow()][getInputColumn()-1].getData() == notOccupied){
		hexCells[getInputRow()][getInputColumn()-1].setData(occupiedRed);
		for(i=0;i<(getInputColumn()-1);++i)
			c++;
		cout << c << getInputRow()+1 << endl;
	}
	else{
		for(i=0;i<getSize();++i)
			for(j=0;j<getSize();++j)
				if(hexCells[i][j].getData() == notOccupied){
					hexCells[i][j].setData(occupiedRed);
					for(k=0;k<j;++k)
						c++;
					cout << c << i+1 << endl;
					return;
				}
	}

}

/* This function plays game. Very similar to playGame function. However this function for games that loaded or switched. */
void Hex::playGameModes(){
	if(getMode() == 1){
		cout << endl <<"User1 is playing on Blue side(x)." << endl
				     <<"User2 is playing on Red side(o)."  << endl;
		cout << endl << "Board is printing.." << endl;
		displayBoard();
		do{
			playMode1();
		}while(!isGameEnd() && getOperation() != menuOperation);

	}
	if(getMode()==2){
		cout << endl <<"User1 is playing on Blue side(x)." << endl
					 <<"Computer is playing on Red side(o)."  << endl;
		cout << endl << "Board is printing.." << endl;
		displayBoard();
		do{
			playMode2();
		}while(!isGameEnd() && getOperation() != menuOperation);
	}
}

/* This function reads from file and sets variables such as size,mode,turn etc. Also reprint the board according to file. */
void Hex::setLoadFile(){

	ifstream fileStream;
	fileStream.open(getFileName().c_str());

	string temp_str;
	string colon_delimeter = ":";
	string token_str;
	char input_c;

	/* setting game stats. */
	getline(fileStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	setSize(stoi(token_str));
	getline(fileStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	setMode(stoi(token_str));
	getline(fileStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	setTurn(stoi(token_str)%2);
	getline(fileStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	setMarkedCells(stoi(token_str));

	setHexCells();	// set the board
	for(int i=0;i<getSize();++i){	// reading board from file.
		for(int j=0; j<getSize();++j){
			fileStream >> input_c;
			if(input_c != '\n')
			hexCells[i][j].setData(input_c);
		}
	}
	fileStream.close();
}

/* This function continues the game.usage: loaded games or switching games. */
void Hex::continueGame(){
	cout << endl << "The Game Continues" << endl;
	printGameInfo();	// printing game infos.
	playGameModes();	// continue the playing game
}

/* This function prints the loaded game stats to the screen. */
void Hex::printGameInfo(){

	cout << endl << "Game Stats is:" << endl;
	cout << "Board Size: " << getSize() << endl;
	cout << "Game Mode: ";
	if(getMode()== 1)
		cout << "User vs User" << endl;
	else
		cout << "User vs Computer" << endl;
	cout << "Turn: ";
	if(getTurn() == 0)
		cout << "Blue Side Turn" << endl;
	else
		cout << "Red Side Turn" << endl;
	cout << "Saved game loading..." << endl;
}

/* This function saves the current game to the file . */
void Hex::saveFile(){

	ofstream fileStream;
	fileStream.open(getFileName().c_str());

	fileStream << "Board Size:" << getSize() << "\n";
	fileStream << "Game Mode:" << getMode() << "\n";
	fileStream << "Turn:" << getTurn()%2 << "\n";
	fileStream << "Marked Cells:" << getMarkedCells() << "\n";
	for(int i=0;i<getSize();++i){	// writing map to the file.
			for(int j=0; j<getSize();++j)
				fileStream << hexCells[i][j].getData();
			fileStream << "\n";
	}
	cout << "Game successfully saved." << endl;
	fileStream.close();
}

/* This function loads game according to given string. If string not valid, function ends. Otherwise loads the saved game. */
void Hex::loadFile(string str){

	if(setFileName(str)){
		setLoadFile();
		continueGame();
	}
}


/* This function checks that is game end or not .If game ends, returns true otherwise returns false. */
bool Hex::isGameEnd(){
	if(getTurn()%2 == 1)
		return isBlueWin();
	else
		return isRedWin();

}

/* This function checks that is blue side('x') won or not. If blue side won, makes winning path to capital letter . */
bool Hex::isBlueWin() {
	bool check = false;

	for(int i=0;i<getSize();++i){	// finding occupied cell in first column
		if(hexCells[i][0].getData() == occupiedBlue)
			// checking whether is cell reach other side or not
			if(recCheckBlue(i,0,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
				hexCells[i][0].setData(winBlue);									// will be true.
				recCapitalBlue(i,0);
				displayBoard();
				cout << endl <<"!Game Over! The Blue Side Won!!" << endl;
				check = true;
			}
	}
	return check;
}

/* This function recursively checks that whether blue side wins or not */
bool Hex::recCheckBlue(int r, int c,int counter) const {

	if(c == getSize()-1)
		return true;
	else if(counter > (getSize())*(getSize()))
		return false;
	else if(c+1 < getSize() && hexCells[r][c+1].getData() == occupiedBlue)
		return recCheckBlue(r,c+1,++counter);
	else if(r+1 < getSize() && hexCells[r+1][c].getData() == occupiedBlue)
		return recCheckBlue(r+1,c,++counter);
	else if(r-1 >=0 && c+1 < getSize() && hexCells[r-1][c+1].getData()  == occupiedBlue)
		return recCheckBlue(r-1,c+1,++counter);
	else if(r-1 >=0 && hexCells[r-1][c].getData()  == occupiedBlue)
		return recCheckBlue(r-1,c,++counter);
	else if(r+1 < getSize() && c-1 >=0 && hexCells[r+1][c-1].getData()  == occupiedBlue)
		return recCheckBlue(r+1,c-1,++counter);
	else if(c-1 >=0 && hexCells[r][c-1].getData()  == occupiedBlue)
		return recCheckBlue(r,c-1,++counter);
	else
		return false;
}

/* This function recursively make winning path to capital when the game ends. */
bool Hex::recCapitalBlue(int r,int c){

	if(c==getSize())
		return true;
	else if(c+1 < getSize() && hexCells[r][c+1].getData() == occupiedBlue){
		hexCells[r][c+1].setData(winBlue);
		return recCapitalBlue(r,c+1);
	}
	else if(r+1 < getSize() && hexCells[r+1][c].getData() == occupiedBlue){
		hexCells[r+1][c].setData(winBlue);
		return recCapitalBlue(r+1,c);
	}
	else if(r-1 >=0 && c+1 < getSize() && hexCells[r-1][c+1].getData()  == occupiedBlue){
		hexCells[r-1][c+1].setData(winBlue);
		return recCapitalBlue(r-1,c+1);
	}
	else if(r-1 >=0 && hexCells[r-1][c].getData()  == occupiedBlue){
		hexCells[r-1][c].setData(winBlue);
		return recCapitalBlue(r-1,c);
	}
	else if(r+1 < getSize() && c-1 >=0 && hexCells[r+1][c-1].getData()  == occupiedBlue){
		hexCells[r+1][c-1].setData(winBlue);
		return recCapitalBlue(r+1,c-1);
	}
	else if(c-1 >=0 && hexCells[r][c-1].getData()  == occupiedBlue){
		hexCells[r][c-1].setData(winBlue);
		return recCapitalBlue(r,c-1);
	}
	else
		return false;
}

/* This function checks that is red side('o') won or not. If red side won, makes winning path to capital letter . */
bool Hex::isRedWin(){
	bool check = false;

	for(int i=0;i<getSize();++i){	// finding occupied cell in first column
		if(hexCells[0][i].getData() == occupiedRed)
			// checking whether is cell reach other side or not
			if(recCheckRed(0,i,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
				hexCells[0][i].setData(winRed);									// will be true.
				recCapitalRed(0,i);
				displayBoard();
				cout << endl <<"!Game Over! The Red Side Won!!" << endl;
				check = true;
			}
	}
	return check;
}

/* This function recursively checks that whether red side wins or not */
bool Hex::recCheckRed(int r,int c,int counter) const{

	if(r==getSize()-1)
		return true;
	else if(counter > (getSize()+1)*(getSize()+1))
		return false;
	else if(r+1 < getSize() && hexCells[r+1][c].getData() == occupiedRed)
		return recCheckRed(r+1,c,++counter);
	else if(r+1 < getSize() && c-1 >= 0 && hexCells[r+1][c-1].getData() == occupiedRed)
		return recCheckRed(r+1,c-1,++counter);
	else if(c+1 < getSize() && hexCells[r][c+1].getData() == occupiedRed)
		return recCheckRed(r,c+1,++counter);
	else if(c-1 >= 0 && hexCells[r][c-1].getData() == occupiedRed)
		return recCheckRed(r,c-1,++counter);
	else if(r-1 >=0 && c+1 < getSize() && hexCells[r-1][c+1].getData() == occupiedRed)
		return recCheckRed(r-1,c+1,++counter);
	else if(r-1 >=0 && hexCells[r-1][c].getData() == occupiedRed)
		return recCheckRed(r-1,c,++counter);
	else
		return false;
}

/* This function recursively make winning path to capital when the game ends. */
bool Hex::recCapitalRed(int r,int c){

	if(r==getSize())
		return true;
	else if(r+1 < getSize() && hexCells[r+1][c].getData() == occupiedRed){
		hexCells[r+1][c].setData(winRed);
		return recCapitalRed(r+1,c);
	}
	else if(r+1 < getSize() && c-1 >= 0 && hexCells[r+1][c-1].getData() == occupiedRed){
		hexCells[r+1][c-1].setData(winRed);
		return recCapitalRed(r+1,c-1);
	}
	else if(c+1 < getSize() && hexCells[r][c+1].getData() == occupiedRed){
		hexCells[r][c+1].setData(winRed);
		return recCapitalRed(r,c+1);
	}
	else if(c-1 >= 0 && hexCells[r][c-1].getData() == occupiedRed){
		hexCells[r][c-1].setData(winRed);
		return recCapitalRed(r,c-1);
	}
	else if(r-1 >=0 && c+1 < getSize() && hexCells[r-1][c+1].getData() == occupiedRed){
		hexCells[r-1][c+1].setData(winRed);
		return recCapitalRed(r-1,c+1);
	}
	else if(r-1 >=0 && hexCells[r-1][c].getData() == occupiedRed){
		hexCells[r-1][c].setData(winRed);
		return recCapitalRed(r-1,c);
	}
	else
		return false;
}

/* This function compares two games(objects) marked cells . Returns true when called object is greater*/
bool Hex::compareBoards(const Hex& other) const{
	return (getMarkedCells() > other.getMarkedCells());
}

/* This function parses input string.This is a private member function. */
void Hex::parseString(string str){
	string spaceDelimeter = " ";
	string save_operation = "SAVE";
	string menu_operation = "MENU";
	string fileName;

	if(str == menu_operation )	// condition for menu operation
			setOperation(menuOperation);

	else if(str.substr(0,str.find(spaceDelimeter)) == save_operation ){	 // condition for save operation
		fileName = str.substr(str.find(spaceDelimeter)+1);
		if(setFileName(fileName))
			setOperation(saveOperation);

	}
	else{	 // condition for move operation

		setInputColumn(str[0]);
		if(getInputColumn()+'A' < 'A')	// condition for handle with invalid input such as  5F instead of F5
			setOperation(errorOperation);
		else{
			decltype(str) temp;
			temp = str.substr(1);
			setInputRow(stoi(temp));
		setOperation(moveOperation);;
		}
	}
}



inline char Hex::Cell::getData() const {return data;}	// getters
inline void Hex::Cell::setData(char data_value){ data = data_value;}	// setters

/* constructors */

Hex::Cell::Cell(char data_value)
				: data(data_value)
{/* Intentionally empty */}
Hex::Cell::Cell()
				: Cell(notOccupied)
{/* Intentionally empty */}

