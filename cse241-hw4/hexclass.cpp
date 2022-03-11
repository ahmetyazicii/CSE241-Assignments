#include<iostream>
#include<string>
#include<fstream>
using namespace std;
using std::ostream;
using std::istream;
using std::string;
using std::ofstream;
using std::ifstream;

#include"hexheader.h"
#include"cellheader.h"

enum cell_states{ notOccupied = '.', occupiedBlue = 'x', occupiedRed = 'o',winBlue  = 'X', winRed = 'O'};
enum user_operations{scoreOperation =4,saveOperation = 2, menuOperation = 3, moveOperation = 1, errorOperation = -1};
enum player_turns{BlueTurn = 0, RedTurn = 1};


/* constructors */
Hex::Hex(int size,int mode)
		:markedCells(0),operation(0),scoreRed(0),scoreBlue(0),inputRow(0),inputColumn('A'),turn(0),moveHistory(nullptr),hexCells(nullptr)
{
	setSize(size);
	setMode(mode);
	setHexCells();
	setMoveHistory();
}
Hex::Hex(int size) : Hex(size,1)
{/* Intentionally empty */}
Hex::Hex() : Hex(5,1)
{/* Intentionally empty */}


/* Big Three */
/* copy constructor */
Hex::Hex(const Hex& hexObject){
	// copying member variables
	boardSize = hexObject.getSize();
	markedCells = hexObject.getMarkedCells();
	operation = hexObject.getOperation();
	scoreRed = hexObject.getScoreRed();
	scoreBlue = hexObject.getScoreBlue();
	gameMode = hexObject.getMode();
	turn = hexObject.getTurn();
	inputRow = hexObject.getInputRow();
	inputColumn = hexObject.getInputColumn();
	fileName = hexObject.getFileName();

	moveHistory = new int*[getSize()*getSize()];		// copying history of moves
	for(int i=0;i<getSize()*getSize();++i){
		moveHistory[i] = new int [2];
		for(int j=0;j<2;++j)
			moveHistory[i][j] = hexObject.moveHistory[i][j];
	}

	hexCells = new Cell*[getSize()];				// copying board
	for(int i=0;i<getSize();++i){
		hexCells[i] = new Cell[getSize()];
		for(int j=0;j<getSize();++j)
			hexCells[i][j].setData(hexObject.hexCells[i][j].getData());
	}
}

/* destructor */
Hex::~Hex(){

	for(int i=0;i<getSize()*getSize();++i)		// deleting history of moves
		delete[] moveHistory[i];
	delete[] moveHistory;
	moveHistory = nullptr;

	for(int i=0;i<getSize();++i)				// deleting board
		delete[] hexCells[i];
	delete[] hexCells;
	hexCells = nullptr;

}

/* assignment operator */
Hex& Hex::operator =(const Hex& rightSide ){
	if(this == &rightSide)
		return *this;
	else{
		int tempSize = getSize();
		// copying member variables
		boardSize = rightSide.getSize();
		markedCells = rightSide.getMarkedCells();
		operation = rightSide.getOperation();
		scoreRed = rightSide.getScoreRed();
		scoreBlue = rightSide.getScoreBlue();
		gameMode = rightSide.getMode();
		turn = rightSide.getTurn();
		inputRow = rightSide.getInputRow();
		inputColumn = rightSide.getInputColumn();
		fileName = rightSide.getFileName();

		for(int i=0;i<tempSize*tempSize;++i)		// deleting history of moves
			delete[] moveHistory[i];
		delete[] moveHistory;
		moveHistory = nullptr;

		moveHistory = new int*[getSize()*getSize()];	// copying history of moves
		for(int i=0;i<getSize()*getSize();++i){
			moveHistory[i] = new int [2];
			for(int j=0;j<2;++j)
				moveHistory[i][j] = rightSide.moveHistory[i][j];
		}

		for(int i=0;i<tempSize;++i)		// deleting board
			delete[] hexCells[i];
		delete[] hexCells;
		hexCells = nullptr;

		hexCells = new Cell*[getSize()];		// copying board
		for(int i=0;i<getSize();++i){
			hexCells[i] = new Cell[getSize()];
			for(int j=0;j<getSize();++j)
				hexCells[i][j].setData(rightSide.hexCells[i][j].getData());
		}
		return *this;
	}
}


/* getters */
inline int Hex::getSize() const {return boardSize;}
inline int Hex::getMode() const {return gameMode;}
inline int Hex::getInputRow()  const {return inputRow;}
inline int Hex::getInputColumn() const {return inputColumn;}
inline int Hex::getOperation() const {return operation;}
inline int Hex::getTurn() const {return turn;}
inline int Hex::getScoreRed() const {return scoreRed;}
inline int Hex::getScoreBlue() const {return scoreBlue;}
inline string Hex::getFileName()const{ return fileName;}
inline int Hex::getMarkedCells() const {return markedCells;}


/* setters and etc */
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
inline void Hex::setScoreBlue(int score){ scoreBlue = score;}
inline void Hex::setScoreRed(int score){ scoreRed = score;}

inline void Hex::increaseMarkedCells(){
	markedCells++;
	allMarked++;
}
inline void Hex::decreaseMarkedCells(){
	markedCells--;
	allMarked--;
}

void Hex::setHexCells(){
	if(hexCells != nullptr){	// deleting default constructors dynamic array.
		for(int i=0;i<5;++i)
			delete[] hexCells[i];
		delete[] hexCells;
		hexCells = nullptr;

	}
	hexCells = new Cell*[getSize()];
	for(int i=0;i<getSize();++i){
		hexCells[i] = new Cell[getSize()];
		for(int j=0;j<getSize();++j)
			hexCells[i][j].setData(notOccupied);
	}
}

void Hex::setMoveHistory(){		// creating moveHistory of  square of size element because there max be that much move
	if(moveHistory != nullptr){	// deleting default constructors dynamic array.
		for(int i=0;i<5*5;++i)
			delete[] moveHistory[i];
		delete[] moveHistory;
		moveHistory = nullptr;
	}
	moveHistory = new int*[getSize()*getSize()];
	for(int i=0;i<getSize()*getSize();++i)
		moveHistory[i] = new int[2];
}



/* This function is overloaded version of << operator for printing board to screen and also writing terminal. */
/* In this overload, i  confused.Because the overloading for << operator is same for both cout and file stream. I tried overload it with
 * ofstream object( the code in below in comment line), but i got several warning messages from compiler(warning messages attached to the readMe file).
 * Therefore i found out this solution.Checking the type of given stream, then perform suitable tasks for file(writing file) or terminal(printing terminal).
 */

ostream& operator <<(ostream& outputStream,const Hex& object){

	if(&outputStream == &cout){		// determining given ostream object is terminal(cout) object or file object. If cout then performs printing stuff.
		char c= 'a';
		int i,j,k;

		outputStream << endl << ' ';

		for(i=0;i<object.getSize();++i,++c)	// printing the letter(rows)
			outputStream << c << ' ';

		outputStream << endl;

		for(i=0;i<object.getSize();++i){
			outputStream << i+1;		// printing numbers(columns)
			if(i>=9)				// when the number is 10 or greater than 10,there must be one less whitespace, because 10 has two digit.
				for(k=0;k<i;k++)	// printing white spaces
					outputStream << ' ';
			else
				for(k=0;k<=i;k++)	// printing white spaces
					outputStream << ' ';
			for(j=0;j<object.getSize();++j){	// printing board
				outputStream << object.hexCells[i][j].getData() << ' ';
			}
			outputStream << endl;
		}
		return outputStream;
	}
	else{
		outputStream << "Board Size:" << object.getSize() << "\n";
		outputStream << "Game Mode:" << object.getMode() << "\n";
		outputStream << "Turn:" << object.getTurn()%2 << "\n";
		outputStream << "Marked Cells:" << object.getMarkedCells() << "\n";
		outputStream << "Score Blue:" 	<< object.getScoreBlue() << "\n";
		outputStream << "Score Red:" 	<< object.getScoreRed() << "\n";
		for(int i=0;i<object.getSize();++i){	// writing map to the file.
				for(int j=0; j<object.getSize();++j)
					outputStream << object.hexCells[i][j].getData();

				outputStream << "\n";
		}
		cout << "Game successfully saved." << endl;

		return outputStream;
	}
}


/* overload << with ofstream for file
ofstream& operator <<(ofstream& outputStream, const Hex& object){

	outputStream << "Board Size:" << object.getSize() << "\n";
	outputStream << "Game Mode:" << object.getMode() << "\n";
	outputStream << "Turn:" << object.getTurn()%2 << "\n";
	outputStream << "Marked Cells:" << object.getMarkedCells() << "\n";
	outputStream << "Score Blue:" 	<< object.getScoreBlue() << "\n";
	outputStream << "Score Red:" 	<< object.getScoreRed() << "\n";
	for(int i=0;i<object.getSize();++i){	// writing map to the file.
			for(int j=0; j<object.getSize();++j)
				outputStream << object.hexCells[i][j].getData();

			outputStream << "\n";
	}
	cout << "Game successfully saved." << endl;

	return outputStream;
}
*/


/* for reading from file.*/
istream& operator >>(istream& outputStream, Hex& object){


	string temp_str;
	string colon_delimeter = ":";
	string token_str;
	char input_c;

	/* setting game stats. */
	getline(outputStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	object.setSize(stoi(token_str));

	getline(outputStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	object.setMode(stoi(token_str));

	getline(outputStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	object.setTurn(stoi(token_str)%2);

	getline(outputStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	object.setMarkedCells(stoi(token_str));

	getline(outputStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	object.setScoreBlue(stoi(token_str));

	getline(outputStream,temp_str);
	token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
	object.setScoreRed(stoi(token_str));

	object.setMoveHistory();	// set the move history
	object.setHexCells();	// set the board
	for(int i=0;i<object.getSize();++i){	// reading board from file.
		for(int j=0; j<object.getSize();++j){
			outputStream >> input_c;
			if(input_c != '\n')
			object.hexCells[i][j].setData(input_c);
		}
	}

	return outputStream;
}

void Hex::loadFile(string str){

	if(setFileName(str)){
		ifstream fileStream;
		fileStream.open(getFileName().c_str());
		fileStream >> *this;
		fileStream.close();
		continueGame();
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
	setMoveHistory();	// rearrange history of moves
	playGameModes();

}


/* This function plays game. Very similar to playGame function. However this function for games that loaded or switched. */
void Hex::playGameModes(){
	if(getMode() == 1){
		cout << endl <<"User1 is playing on Blue side(x)." << endl
				     <<"User2 is playing on Red side(o)."  << endl;
		cout << endl << "Board is printing.." << endl;
		cout << *this;
		do{
			playMode1();
		}while(!isGameEnd() && getOperation() != menuOperation);

	}
	if(getMode()==2){
		cout << endl <<"User1 is playing on Blue side(x)." << endl
					 <<"Computer is playing on Red side(o)."  << endl;
		cout << endl << "Board is printing.." << endl;
		cout << *this;
		do{
			playMode2();
		}while(!isGameEnd() && getOperation() != menuOperation);
	}
}
/* Function for UservsUser mode. Very similar to playMode2 function. */
void Hex::playMode1(){

		if(getTurn()%2 == 0){
			cout << endl << "User1's turn(Blue Side)" << endl;
			getInput();
			increaseTurn();

			findScoreBlue();	//finding scores
			findScoreRed();
			switch(getOperation()){
				case menuOperation: {// if the input is "MENU" function ends and returns menu
					decreaseTurn();	// decrease turn in order to play correct side when switch back to game
					return;
					break;
				}
				case saveOperation:{	// for save operation
					decreaseTurn();

					ofstream fileStream;	// opening file
					fileStream.open(getFileName().c_str());
					fileStream << *this;	// writing to the file
					fileStream.close();		//closeing file

					return;
					break;
				}
				case scoreOperation: {	//  printing scores of  both players.
					decreaseTurn();		// decrease turn in order to play correct side when switch back to game
					cout << "BlueSide('x') score is: " << getScoreBlue()
						 << "---RedSide('o') score is: " << getScoreRed() << endl;
					return;
					break;
				}
			}
			play(getInputRow(),getInputColumn());
			cout << *this;

		}
		else if(getTurn()%2 == 1){
			cout << endl << "User2's turn(Red Side)" << endl;
			getInput();
			increaseTurn();
			findScoreRed();
			findScoreBlue();
			switch(getOperation()){
				case menuOperation: {
					decreaseTurn();
					return;
					break;
				}
				case saveOperation:{
					decreaseTurn();

					ofstream fileStream;
					fileStream.open(getFileName().c_str());
					fileStream << *this;
					fileStream.close();

					return;
					break;
				}
				case scoreOperation: {
					decreaseTurn();
					cout << "BlueSide('x') score is: " << getScoreBlue()
						 << "---RedSide('o') score is: " << getScoreRed() << endl;
					return;
					break;
				}

			}
			play(getInputRow(),getInputColumn());
			cout << *this;
		}
}

/* Function for UservsComputer mode. */
void Hex::playMode2(){
	if(getTurn()%2 == 0){	// blue side turn
		cout << endl << "User1's turn(Blue Side)" << endl;
		getInput();
		increaseTurn();
		findScoreBlue();
		findScoreRed();
		switch(getOperation()){
			case menuOperation: {	// if the input is "MENU" function ends and returns menu
				decreaseTurn();		// decrease turn in order to play correct side when switch back to game
				return;
				break;
			}
			case saveOperation:{	// if the input is "SAVE" function performs save operation and ends
				decreaseTurn();		// decrease the turn in order to make move after save operation

				ofstream fileStream;
				fileStream.open(getFileName().c_str());
				fileStream << *this;
				fileStream.close();

				return;
				break;
			}
			case scoreOperation: {
				decreaseTurn();
				cout << "BlueSide('x') score is: " << getScoreBlue()
					 << "---RedSide('o') score is: " << getScoreRed() << endl;
				return;
				break;
			}
		}
		play(getInputRow(),getInputColumn());
		cout << *this;
	}
	else if(getTurn()%2 == 1){	// red side turn
			cout << endl << "Computer's turn(Red Side)" << endl;
			cout << "Computer's move is: ";
			increaseTurn();
			play();
			cout << *this;
	}
}

/* This function make moves for players according to turn info. And returns the cell */
Hex::Cell Hex::play(int row,int column){
	// saving moves to the moveHistory array
	moveHistory[getMarkedCells()][0] = row;
	moveHistory[getMarkedCells()][1] = column;
	increaseMarkedCells();

	if(getTurn()%2 == 1)
		hexCells[row][column].setData(occupiedBlue);
	else
		hexCells[row][column].setData(occupiedRed);
	return hexCells[row][column];
}




/* This function make moves for computer. The algorithm very similar to hw1.And returns the cell  */
Hex::Cell Hex::play(){

	Cell rtrn;
	char c='A';
	int i,j,k;

	// checking all 6 possible neighbor of cell. Also checking that the possible cells is in board or not( -1 index of array or crossing size)
	if(getInputColumn()+1 <getSize() && hexCells[getInputRow()][getInputColumn()+1].getData() == notOccupied){
		hexCells[getInputRow()][getInputColumn()+1].setData(occupiedRed);

		// saving moves to the moveHistory array
		moveHistory[getMarkedCells()][0] = getInputRow();
		moveHistory[getMarkedCells()][1] = getInputColumn()+1;

		rtrn = hexCells[getInputRow()][getInputColumn()+1];
		for(i=0;i<(getInputColumn()+1);++i)	// for printing letter of coordinate, incrementing 'A'.
			c++;
		cout << c << getInputRow()+1 << endl;	// printing coordinate.
	}
	else if(getInputRow()+1 <getSize() && hexCells[getInputRow()+1][getInputColumn()].getData() == notOccupied){
		hexCells[getInputRow()+1][getInputColumn()].setData(occupiedRed);

		moveHistory[getMarkedCells()][0] = getInputRow()+1;
		moveHistory[getMarkedCells()][1] = getInputColumn();

		rtrn = hexCells[getInputRow()+1][getInputColumn()];
		for(i=0;i<getInputColumn();++i)
			c++;
		cout << c << getInputRow()+2 << endl;
	}
	else if(getInputRow()-1 >= 0 && getInputColumn()+1 <getSize() && hexCells[getInputRow()-1][getInputColumn()+1].getData() == notOccupied){
		hexCells[getInputRow()-1][getInputColumn()+1].setData(occupiedRed);

		moveHistory[getMarkedCells()][0] = getInputRow()-1;
		moveHistory[getMarkedCells()][1] = getInputColumn()+1;

		rtrn = hexCells[getInputRow()-1][getInputColumn()+1];
		for(i=0;i<(getInputColumn()+1);++i)
			c++;
		cout << c << getInputRow() << endl;
	}
	else if(getInputRow()-1 >= 0 && hexCells[getInputRow()-1][getInputColumn()].getData() == notOccupied){
		hexCells[getInputRow()-1][getInputColumn()].setData(occupiedRed);

		moveHistory[getMarkedCells()][0] = getInputRow()-1;
		moveHistory[getMarkedCells()][1] = getInputColumn();

		rtrn = hexCells[getInputRow()-1][getInputColumn()];
		for(i=0;i<(getInputColumn());++i)
			c++;
		cout << c << getInputRow() << endl;
	}
	else if(getInputColumn()-1 >= 0 && getInputRow()+1 <getSize() && hexCells[getInputRow()+1][getInputColumn()-1].getData() == notOccupied){
		hexCells[getInputRow()+1][getInputColumn()-1].setData(occupiedRed);

		moveHistory[getMarkedCells()][0] = getInputRow()+1;
		moveHistory[getMarkedCells()][1] = getInputColumn()-1;

		rtrn = hexCells[getInputRow()+1][getInputColumn()-1];
		for(i=0;i<(getInputColumn()-1);++i)
			c++;
		cout << c << getInputRow()+2 << endl;
	}
	else if(getInputColumn()-1 >= 0 && hexCells[getInputRow()][getInputColumn()-1].getData() == notOccupied){
		hexCells[getInputRow()][getInputColumn()-1].setData(occupiedRed);

		moveHistory[getMarkedCells()][0] = getInputRow();
		moveHistory[getMarkedCells()][1] = getInputColumn()-1;

		rtrn = hexCells[getInputRow()][getInputColumn()-1];
		for(i=0;i<(getInputColumn()-1);++i)
			c++;
		cout << c << getInputRow()+1 << endl;
	}
	else{
		for(i=0;i<getSize();++i)
			for(j=0;j<getSize();++j)
				if(hexCells[i][j].getData() == notOccupied){
					hexCells[i][j].setData(occupiedRed);

					moveHistory[getMarkedCells()][0] = i;
					moveHistory[getMarkedCells()][1] = j;

					rtrn = hexCells[i][j];
					for(k=0;k<j;++k)
						c++;
					cout << c << i+1 << endl;
					// return;
					break;
				}
	}
	increaseMarkedCells();
	return rtrn;
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
	cout << "BlueSide('x') score is: " << getScoreBlue() << endl;
	cout << "RedSide('o') score is: " << getScoreRed() << endl;
	cout << "Saved game loading..." << endl;
}


/* This function gets input from user and parse it properly. */
string Hex::getInput(){

	bool check=false;
	string input;
	do{
		cout << "Please make your move (as an example F5)(MENU for return menu)(SAVE filename.txt for save game)(SCORE for players score): ";
		getline(cin,input);
		parseString(input);	// parsing string
		if(getOperation() == saveOperation || getOperation() == menuOperation || getOperation() == scoreOperation)
			check = true;
		else if(getOperation() == moveOperation)
			if(checkValidMove())
				check = true;
	}while(!check);
	return input;
}



/* This function checks that given coordinate is valid or not .*/
bool Hex::checkValidMove(){

	if(getInputRow() < getSize() && getInputColumn() < 'A'+getSize() && hexCells[getInputRow()][getInputColumn()].getData() ==  notOccupied )
		return true;
	else{
		cerr << "You typed invalid move.Typed cell is already occupied or you cross the board size."
			 <<	"Try again please" << endl;
		return false;
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
				cout << *this;
				cout << endl <<"!Game Over! The Blue Side Won!!" << endl;
				setScoreBlue(100*getSize());	// if the user won makes the score highest
				// printing scores end of the game
				findScoreRed();
				cout << "BlueSide('x') score is: " << getScoreBlue()
					 << "---RedSide('o') score is: " << getScoreRed() << endl;
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
				cout << *this;
				cout << endl <<"!Game Over! The Red Side Won!!" << endl;
				setScoreRed(100*getSize());
				findScoreBlue();
				cout << "BlueSide('x') score is: " << getScoreBlue()
					 << "---RedSide('o') score is: " << getScoreRed() << endl;
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


/* overloading pre decrement operator. */
Hex& Hex::operator--(){

	if(getMarkedCells()==0){	// when there is no move */
		cout << "There is not any move.Undo operation can not performs." << endl;
	}
	else{
		hexCells[moveHistory[getMarkedCells()-1][0]][moveHistory[getMarkedCells()-1][1]] = notOccupied;	// deleting last move
		decreaseTurn();
		decreaseMarkedCells();

		if(getMode()==2){	// when game mode is 2(user vs pc) we need to delete 2 move because pc will make same move and it is pointless.
			hexCells[moveHistory[getMarkedCells()-1][0]][moveHistory[getMarkedCells()-1][1]] = notOccupied;
			decreaseTurn();
			decreaseMarkedCells();
		}
		cout << "UNDO operation successfully completed." << endl ;
	}
	return *this;
}

/* overloading post decrement operator .*/
Hex Hex::operator--(int empty){

	Hex temp = *this;

	--*this;
	return temp;
}

/* overloading equal to operator */
bool operator==(const Hex& object1,const Hex& object2){
	return(object1.getMarkedCells() == object2.getMarkedCells());
}
/* overloading less than operator */
bool operator <(const Hex& object1,const Hex& object2){
	return(object1.getMarkedCells() < object2.getMarkedCells());
}
/* overloading greater than operator */
bool operator >(const Hex& object1,const Hex& object2){
	return(object1.getMarkedCells() > object2.getMarkedCells());
}

/*This function finds the score of blue side.The algorithm is: there is 3 correct way for blue side.However the most correct one direct way.
 * The scoring is done accordingly this information. If the user makes connection in direct way gets (size*2) point.If makes connection in other two ways gets (size*1) point
 */
void Hex::findScoreBlue(){

	int tempScore=0;

	for(int i=0;i<getSize();++i){
			for(int j=0;j<getSize();++j){
				if(hexCells[i][j].getData() == occupiedBlue){
					if(j+1 < getSize() && hexCells[i][j+1].getData() == occupiedBlue)
						tempScore += getSize()*2;
					if(i+1 < getSize() && j+1 < getSize() && hexCells[i+1][j+1].getData() == occupiedBlue)
						tempScore += getSize();
					if(i-1 >= 0 && j+1 < getSize() && hexCells[i-1][j+1].getData() == occupiedBlue)
						tempScore += getSize();
				}
			}
	}
	setScoreBlue(tempScore);
}

/* This function finds the score of red side. Very similar to findScoreBlue() function. */
void Hex::findScoreRed(){

	int tempScore=0;

	for(int i=0;i<getSize();++i){
			for(int j=0;j<getSize();++j){
				if(hexCells[i][j].getData() == occupiedRed){
					if(i+1 < getSize() && hexCells[i+1][j].getData() == occupiedRed)
						tempScore += getSize()*2;
					if(i+1 < getSize() && j-1 >=0 && hexCells[i+1][j-1].getData() == occupiedRed)
						tempScore += getSize();
					if(j+1 < getSize() && hexCells[i][j+1].getData() == occupiedRed)
						tempScore += getSize();
				}
			}
	}
	setScoreRed(tempScore);
}


/* This function parses input string.This is a private member function. */
void Hex::parseString(string str){
	string spaceDelimeter = " ";
	string save_operation = "SAVE";
	string menu_operation = "MENU";
	string score_operation = "SCORE";
	string fileName;

	if(str == menu_operation )	// condition for menu operation
			setOperation(menuOperation);

	else if(str.substr(0,str.find(spaceDelimeter)) == save_operation ){	 // condition for save operation
		fileName = str.substr(str.find(spaceDelimeter)+1);
		if(setFileName(fileName))
			setOperation(saveOperation);

	}
	else if(str == score_operation)
			setOperation(scoreOperation);

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



