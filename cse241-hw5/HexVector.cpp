#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include<vector>
#include"AbstractHex.h"
#include"HexVector.h"
#include"My_Exceptions.h"

using namespace std;

namespace AYaziciHexGame{

	enum cell_states{ notOccupied = '.', occupiedBlue = 'x', occupiedRed = 'o',winBlue  = 'X', winRed = 'O'};
	enum user_operations{lastMoveOperation = 4, saveOperation = 2, menuOperation=3,moveOperation = 1, errorOperation = -1};

	HexVector::HexVector() : AbstractHex(){ }

	HexVector::HexVector(int size,int mode) : AbstractHex(){

		if(size > 4 || mode == 1 || mode == 2){
			setSize(size);
			setGameMode(mode);
		}
		else
			throw InvalidSize();
	}

	// virtual setSize function setting size and creating board
	bool HexVector::setSize(int size){
		if(size < 5){
			cerr << endl << "You have typed invalid board size";
			return false;
		}
		boardSize = size;
		setHexCells();
		reset();
		return true;
	}
	
	void HexVector::setHexCells(){
		hexCells = vector< vector<Cell> >(getBoardSize(),vector<Cell>(getBoardSize()));
	}

	// virtual print function printing the board
	void HexVector::print() const {
		char c= 'a';
		int i,j,k;

		cout << endl << ' ';

		for(i=0;i<getBoardSize();++i,++c)	// printing the letter(rows)
			cout << c << ' ';

		cout << endl;

		for(i=0;i<getBoardSize();++i){
			cout << i+1;		// printing numbers(columns)
			if(i>=9)				// when the number is 10 or greater than 10,there must be one less whitespace, because 10 has two digit.
				for(k=0;k<i;k++)	// printing white spaces
					cout << ' ';
			else
				for(k=0;k<=i;k++)	// printing white spaces
					cout << ' ';
			for(j=0;j<getBoardSize();++j){	// printing board
				cout << hexCells[i][j].getData() << ' ';
			}
			cout << endl;
		}
	}

	// virtual reset function resetting the board to the inital position
	void HexVector::reset(){
		char c='.';
		for(int i=0;i<getBoardSize();++i){
			for(int j=0;j<getBoardSize();++j){
				hexCells[i][j].setData(c);
				hexCells[i][j].setRow(i);
				hexCells[i][j].setColumn(j);
			}
		}
	}

	// virtual play function for users play
	void HexVector::play(Cell position){
		increaseNumOfMoves();
		if(getTurn()%2 == 1)
			hexCells[position.getRow()][position.getColumn()].setData(position.getData());
		else
			hexCells[position.getRow()][position.getColumn()].setData(position.getData());
	}

	// virtual play function for computers play
	void HexVector::play(){

		char c='A';
		int i,j,k;
		increaseNumOfMoves();
		// checking all 6 possible neighbor of cell. Also checking that the possible cells is in board or not( -1 index of array or crossing size)
		if(getInputColumn()+1 <getBoardSize() && hexCells[getInputRow()][getInputColumn()+1].getData() == notOccupied){
			hexCells[getInputRow()][getInputColumn()+1].setData(occupiedRed);

			for(i=0;i<(getInputColumn()+1);++i)	// for printing letter of coordinate, incrementing 'A'.
				c++;
			cout << c << getInputRow()+1 << endl;	// printing coordinate.
		}
		else if(getInputRow()+1 <getBoardSize() && hexCells[getInputRow()+1][getInputColumn()].getData() == notOccupied){
			hexCells[getInputRow()+1][getInputColumn()].setData(occupiedRed);
			for(i=0;i<getInputColumn();++i)
				c++;
			cout << c << getInputRow()+2 << endl;
		}
		else if(getInputRow()-1 >= 0 && getInputColumn()+1 <getBoardSize() && hexCells[getInputRow()-1][getInputColumn()+1].getData() == notOccupied){
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
		else if(getInputColumn()-1 >= 0 && getInputRow()+1 <getBoardSize() && hexCells[getInputRow()+1][getInputColumn()-1].getData() == notOccupied){
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
			for(i=0;i<getBoardSize();++i)
				for(j=0;j<getBoardSize();++j)
					if(hexCells[i][j].getData() == notOccupied){
						hexCells[i][j].setData(occupiedRed);
						for(k=0;k<j;++k)
							c++;
						cout << c << i+1 << endl;
						return;
					}
		}
	}

	char HexVector::operator()(int indexr,int indexc) const{

		if(indexr >=0 && indexr < getBoardSize() && indexc >=0 && indexc < getBoardSize())
			return hexCells[indexr][indexc].getData();
		else
			throw InvalidIndex();
	}

	// virtual funcs for read and write to file
	void HexVector::writeToFile(string fName){

		ofstream fileStream;
		fileStream.open(fName.c_str());

		fileStream << "Board Size:" << getBoardSize() << "\n";
		fileStream << "Game Mode:" << getGameMode() << "\n";
		fileStream << "Turn:" << getTurn()%2 << "\n";
		fileStream << "Number Of Moves:" << numberOfMoves() << "\n";
		for(int i=0;i<getBoardSize();++i){	// writing map to the file.
				for(int j=0; j<getBoardSize();++j)
					fileStream << hexCells[i][j].getData();
				fileStream << "\n";
		}
		cout << "Game successfully saved." << endl;
		fileStream.close();
	}

	void HexVector::readFromFile(string fName){

		ifstream fileStream;
		fileStream.open(fName.c_str());
		if(fileStream.fail())
			throw InvalidFile();
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
		setGameMode(stoi(token_str));
		getline(fileStream,temp_str);
		token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
		setTurn(stoi(token_str)%2);
		getline(fileStream,temp_str);
		token_str = temp_str.substr(temp_str.find(colon_delimeter)+1);
		setNumOfMoves(stoi(token_str));

		for(int i=0;i<getBoardSize();++i){	// reading board from file.
			for(int j=0; j<getBoardSize();++j){
				fileStream >> input_c;
				if(input_c != '\n')
				hexCells[i][j].setData(input_c);
			}
		}
		fileStream.close();
	}

	// virtual equal operator for compare to equalty of two hex game
	bool HexVector::operator==(const AbstractHex* other) {
		bool rtrn = true;
		if(getBoardSize() != other->getBoardSize())
			rtrn = false;
		else{
			for(int i=0;i<getBoardSize();i++)
				for(int j=0;j<getBoardSize();j++)
					if(hexCells[i][j].getData() != other->operator()(i,j) )
						rtrn = false;
		}
		return rtrn;
	}


	bool HexVector::isEnd(){
		if(getTurn()%2 == 1)
			return isBlueWin();
		else
			return isRedWin();

	}

	//funcs for check the win condition
	bool HexVector::isBlueWin() {
		bool check = false;

		for(int i=0;i<getBoardSize();++i){	// finding occupied cell in first column
			if(hexCells[i][0].getData() == occupiedBlue)
				// checking whether is cell reach other side or not
				if(recCheckBlue(i,0,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
					hexCells[i][0].setData(winBlue);									// will be true.
					recCapitalBlue(i,0);
					print();
					cout << endl <<"!Game Over! The Blue Side Won!!" << endl;
					check = true;
				}
		}
		return check;
	}

	bool HexVector::isRedWin(){
		bool check = false;

		for(int i=0;i<getBoardSize();++i){	// finding occupied cell in first column
			if(hexCells[0][i].getData() == occupiedRed)
				// checking whether is cell reach other side or not
				if(recCheckRed(0,i,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
					hexCells[0][i].setData(winRed);									// will be true.
					recCapitalRed(0,i);
					print();
					cout << endl <<"!Game Over! The Red Side Won!!" << endl;
					check = true;
				}
		}
		return check;
	}

	// funcs for making capital the win path
	bool HexVector::recCapitalBlue(int r,int c){

		if(c==getBoardSize())
			return true;
		else if(c+1 < getBoardSize() && hexCells[r][c+1].getData() == occupiedBlue){
			hexCells[r][c+1].setData(winBlue);
			return recCapitalBlue(r,c+1);
		}
		else if(r+1 < getBoardSize() && hexCells[r+1][c].getData() == occupiedBlue){
			hexCells[r+1][c].setData(winBlue);
			return recCapitalBlue(r+1,c);
		}
		else if(r-1 >=0 && c+1 < getBoardSize() && hexCells[r-1][c+1].getData()  == occupiedBlue){
			hexCells[r-1][c+1].setData(winBlue);
			return recCapitalBlue(r-1,c+1);
		}
		else if(r-1 >=0 && hexCells[r-1][c].getData()  == occupiedBlue){
			hexCells[r-1][c].setData(winBlue);
			return recCapitalBlue(r-1,c);
		}
		else if(r+1 < getBoardSize() && c-1 >=0 && hexCells[r+1][c-1].getData()  == occupiedBlue){
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

	bool HexVector::recCapitalRed(int r,int c){

		if(r==getBoardSize())
			return true;
		else if(r+1 < getBoardSize() && hexCells[r+1][c].getData() == occupiedRed){
			hexCells[r+1][c].setData(winRed);
			return recCapitalRed(r+1,c);
		}
		else if(r+1 < getBoardSize() && c-1 >= 0 && hexCells[r+1][c-1].getData() == occupiedRed){
			hexCells[r+1][c-1].setData(winRed);
			return recCapitalRed(r+1,c-1);
		}
		else if(c+1 < getBoardSize() && hexCells[r][c+1].getData() == occupiedRed){
			hexCells[r][c+1].setData(winRed);
			return recCapitalRed(r,c+1);
		}
		else if(c-1 >= 0 && hexCells[r][c-1].getData() == occupiedRed){
			hexCells[r][c-1].setData(winRed);
			return recCapitalRed(r,c-1);
		}
		else if(r-1 >=0 && c+1 < getBoardSize() && hexCells[r-1][c+1].getData() == occupiedRed){
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

	Cell HexVector::lastMove(){

		if(numberOfMoves() == 0)
			throw NoLastMove();
		else{
			if(getTurn()% 2 == 1)
				return Cell(getInputRow(),getInputColumn(),occupiedBlue);
			else
				return Cell(getInputRow(),getInputColumn(),occupiedRed);
		}
	}

	HexVector::~HexVector() { };


} //AYaziciHexGame
