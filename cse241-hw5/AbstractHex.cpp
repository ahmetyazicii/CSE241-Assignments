#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include"AbstractHex.h"
#include"My_Exceptions.h"

using namespace std;


namespace AYaziciHexGame{

	enum cell_states{ notOccupied = '.', occupiedBlue = 'x', occupiedRed = 'o',winBlue  = 'X', winRed = 'O'};
	enum user_operations{resetOperation = 5,lastMoveOperation = 4, saveOperation = 2, menuOperation=3,moveOperation = 1, errorOperation = -1};

	// implementation for Cell class
	Cell::Cell() : Cell(0,0,'.'){
		/* Intentionally empty */
	}
	Cell::Cell(int r,int c,char d) : row(r),column(c),data(d) {
		/* Intentionally empty */
	}
	char Cell::getData() const { return data; }
	int Cell::getRow() const { return row; }
	int Cell::getColumn() const { return column; }

	void Cell::setRow(int r) { row = r; }
	void Cell::setColumn(int c) { column =  c; }
	void Cell::setData(char d){ data = d; }


	// implementation for AbstractHex class

	AbstractHex::AbstractHex()
				: inputRow(0),inputColumn(0),turn(0),operation(0),numOfMoves(0){
		/* Intentionally empty */
	}

	// setters
	bool AbstractHex::setSize(int size){
		if(size < 5){
			cerr << endl << "You have typed invalid board size";
			return false;
		}
		boardSize = size;
		return true;
	}
	bool AbstractHex::setGameMode(int mode){
		if(mode != 1 && mode!= 2){
			cerr << endl << "You have typed invalid game mode";
			return false;
		}
		gameMode = mode;
		return true;
	}

	void AbstractHex::setInputRow(int r) { inputRow = r-1; }
	void AbstractHex::setInputColumn(char c) { inputColumn = c-'A'; }
	void AbstractHex::setOperation(int oprt) { operation = oprt; }
	bool AbstractHex::setFileName(string str){
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
	void AbstractHex::increaseTurn() { turn++; }
	void AbstractHex::decreaseTurn() { turn--; }
	void AbstractHex::increaseNumOfMoves() { numOfMoves++; }
	void AbstractHex::setTurn(int t){ turn = t; }
	void AbstractHex::setNumOfMoves(int n) { numOfMoves = n; }

	//getters
	int AbstractHex::getBoardSize() const { return boardSize; }
	int AbstractHex::getGameMode() const { return gameMode; }
	int AbstractHex::getInputRow() const { return inputRow; }
	int AbstractHex::getInputColumn() const { return inputColumn; }
	int AbstractHex::getOperation() const { return operation; }
	int AbstractHex::getTurn() const { return turn; }
	string AbstractHex::getFileName() const { return fileName; }
	int AbstractHex::numberOfMoves() const { return numOfMoves; }

	void AbstractHex::playGame(){
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
		}while(!setGameMode(stoi(input))); //for receive valid input
		playGameModes();
	}

	void AbstractHex::playGameModes(){
		if(getGameMode() == 1){
			cout << endl <<"User1 is playing on Blue side(x)." << endl
					     <<"User2 is playing on Red side(o)."  << endl;
			cout << endl << "Board is printing.." << endl;
			print();
			do{
				playGMode1();
			}while(!isEnd() && getOperation() != menuOperation);

		}
		if(getGameMode()==2){
			cout << endl <<"User1 is playing on Blue side(x)." << endl
						 <<"Computer is playing on Red side(o)."  << endl;
			cout << endl << "Board is printing.." << endl;
			print();
			do{
				playGMode2();
			}while(!isEnd() && getOperation() != menuOperation);
		}
	}

	void AbstractHex::playGMode1(){

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
				case lastMoveOperation:{
					decreaseTurn();
					try{
						Cell temp = lastMove();
						char temp_c = 'A'+temp.getColumn();
						cout << "The last move is:"
							 << temp_c << temp.getRow()+1
							 << "-'" << temp.getData() <<"'" << endl;
					}
					catch(NoLastMove& exc1){
						cout << exc1.what();
					}
					return;
					break;
				}
				case resetOperation:{
					cout << "Map reset.\n";
					reset();
					setTurn(0);
					print();
					return;
					break;
				}
				case saveOperation:{
					decreaseTurn();
					writeToFile(getFileName());
					return;
					break;
				}
			}
			Cell tempCell(getInputRow(),getInputColumn(),occupiedBlue);
			play(tempCell);
			print();
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
				case lastMoveOperation:{
					decreaseTurn();
					try{
						Cell temp = lastMove();
						char temp_c = 'A'+temp.getColumn();
						cout << "The last move is:"
							 << temp_c << temp.getRow()+1
							 << "-'" << temp.getData() <<"'" << endl;
					}
					catch(NoLastMove& exc2){
						cout << exc2.what();
					}
					return;
					break;
				}
				case resetOperation:{
					cout << "Map reset.\n";
					reset();
					setTurn(0);
					print();
					return;
					break;
				}
				case saveOperation:{
					decreaseTurn();
					writeToFile(getFileName());
					return;
					break;
				}
			}
			Cell tempCell(getInputRow(),getInputColumn(),occupiedRed);
			play(tempCell);
			print();
		}
	}

	void AbstractHex::playGMode2(){
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
				case lastMoveOperation:{
					decreaseTurn();
					try{
						Cell temp = lastMove();
						char temp_c = 'A'+temp.getColumn();
						cout << "The last move is:"
							 << temp_c << temp.getRow()+1
							 << "-'" << temp.getData() <<"'" << endl;
					}
					catch(NoLastMove& exc1){
						cout << exc1.what();
					}
					return;
					break;
				}
				case resetOperation:{
					cout << "Map reset.\n";
					reset();
					setTurn(0);
					print();
					return;
					break;
				}
				case saveOperation:{	// if the input is "SAVE" function performs save operation and ends
					decreaseTurn();		// decrease the turn in order to make move after save operation
					writeToFile(getFileName());
					return;
					break;
				}
			}
			Cell tempCell(getInputRow(),getInputColumn(),occupiedBlue);
			play(tempCell);
			print();
		}
		else if(getTurn()%2 == 1){	// red side turn
				cout << endl << "Computer's turn(Red Side)" << endl;
				cout << "Computer's move is: ";
				increaseTurn();
				play();
				print();
		}
	}

	void AbstractHex::getInput(){
		bool check=false;
		string input;
		do{
			cout << "Please make your move (as an example F5)(MENU for return menu)(SAVE filename.txt for save game)(LASTMOVE for print the last move)(RESET for reset the map): ";
			getline(cin,input);
			parseString(input);	// parsing string
			if(getOperation() == saveOperation || getOperation() == menuOperation || getOperation() == lastMoveOperation || getOperation() == resetOperation)
				check = true;
			else if(getOperation() == moveOperation)
				if(checkValidInputMove())
					check = true;
		}while(!check);
	}

	void AbstractHex::continueGame(){

		if(isEnd() == false){
			cout << endl << "The Game Continues" << endl;
			printLoadedGameInfo();	// printing game infos.
			playGameModes();	// continue the playing game
		}
		else{
			cout << "The Game that opened is a end game.The final map is printing..." << endl;
			print();
		}
	}

	void AbstractHex::printLoadedGameInfo(){

		cout << endl << "Game Stats is:" << endl;
		cout << "Board Size: " << getBoardSize() << endl;
		cout << "Game Mode: ";
		if(getGameMode()== 1)
			cout << "User vs User" << endl;
		else
			cout << "User vs Computer" << endl;
		cout << "Turn: ";
		if(getTurn() == 0)
			cout << "Blue Side Turn" << endl;
		else
			cout << "Red Side Turn" << endl;
		cout << "Number of Moves:" << numberOfMoves() << endl;
		cout << "Saved game loading..." << endl;

	}

	void AbstractHex::LOADoperation(string str){

		if(setFileName(str)){
			readFromFile(getFileName());
			continueGame();
		}
	}

	void AbstractHex::parseString(string str){
		string spaceDelimeter = " ";
		string save_operation = "SAVE";
		string menu_operation = "MENU";
		string lastmove_operation = "LASTMOVE";
		string reset_operation = "RESET";
		string fileName;

		if(str == menu_operation )	// condition for menu operation
				setOperation(menuOperation);
		else if(str == lastmove_operation)
			setOperation(lastMoveOperation);
		else if(str == reset_operation)
			setOperation(resetOperation);
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

	bool AbstractHex::checkValidInputMove(){

		if(getInputRow() < getBoardSize() && getInputColumn() < 'A'+getBoardSize() && operator()(getInputRow(),getInputColumn()) ==  notOccupied )
			return true;
		else{
			cerr << "You typed invalid move.Typed cell is already occupied or you cross the board size."
				 <<	"Try again please" << endl;
			return false;
		}
	}

	// check functions

	bool AbstractHex::recCheckBlue(int r, int c,int counter) {

		if(c == getBoardSize()-1)
			return true;
		else if(counter > (getBoardSize())*(getBoardSize()))
			return false;
		else if(c+1 < getBoardSize() && operator()(r,c+1) == occupiedBlue)
			return recCheckBlue(r,c+1,++counter);
		else if(r+1 < getBoardSize() && operator()(r+1,c) == occupiedBlue)
			return recCheckBlue(r+1,c,++counter);
		else if(r-1 >=0 && c+1 < getBoardSize() && operator()(r-1,c+1)  == occupiedBlue)
			return recCheckBlue(r-1,c+1,++counter);
		else if(r-1 >=0 && operator()(r-1,c) == occupiedBlue)
			return recCheckBlue(r-1,c,++counter);
		else if(r+1 < getBoardSize() && c-1 >=0 && operator()(r+1,c-1) == occupiedBlue)
			return recCheckBlue(r+1,c-1,++counter);
		else if(c-1 >=0 && operator()(r,c-1) == occupiedBlue)
			return recCheckBlue(r,c-1,++counter);
		else
			return false;
	}

	bool AbstractHex::recCheckRed(int r,int c,int counter) {

		if(r==getBoardSize()-1)
			return true;
		else if(counter > (getBoardSize()+1)*(getBoardSize()+1))
			return false;
		else if(r+1 < getBoardSize() && operator()(r+1,c) == occupiedRed)
			return recCheckRed(r+1,c,++counter);
		else if(r+1 < getBoardSize() && c-1 >= 0 && operator()(r+1,c+1) == occupiedRed)
			return recCheckRed(r+1,c-1,++counter);
		else if(c+1 < getBoardSize() && operator()(r,c+1) == occupiedRed)
			return recCheckRed(r,c+1,++counter);
		else if(c-1 >= 0 && operator()(r,c-1) == occupiedRed)
			return recCheckRed(r,c-1,++counter);
		else if(r-1 >=0 && c+1 < getBoardSize() && operator()(r-1,c+1) == occupiedRed)
			return recCheckRed(r-1,c+1,++counter);
		else if(r-1 >=0 && operator()(r-1,c) == occupiedRed)
			return recCheckRed(r-1,c,++counter);
		else
			return false;
	}

	AbstractHex::~AbstractHex(){ }

} // AYaziciHexGame







