#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include<cstdlib>
#include"AbstractHex.h"
#include"HexArray1D.h"
#include"My_Exceptions.h"



using namespace std;

namespace AYaziciHexGame{

	enum cell_states{ notOccupied = '.', occupiedBlue = 'x', occupiedRed = 'o',winBlue  = 'X', winRed = 'O'};
	enum user_operations{lastMoveOperation = 4, saveOperation = 2, menuOperation=3,moveOperation = 1, errorOperation = -1};


	HexArray1D::HexArray1D() : AbstractHex() , hexCells1D(nullptr) { }

	HexArray1D::HexArray1D(int size,int mode) : AbstractHex() ,hexCells1D(nullptr) {
		
		if(size > 4 || mode == 1 || mode == 2){
			setSize(size);
			setGameMode(mode);
		}
		else
			throw InvalidSize();
	}

	// copy constructor
	HexArray1D::HexArray1D(const HexArray1D& other) : AbstractHex(){
		setSize(other.boardSize);
		setGameMode(other.gameMode);
		numOfMoves = other.numOfMoves;
		turn = other.turn;
		operation = other.operation;
		numOfMoves = other.numOfMoves;

		for(int i=0;i<getBoardSize()*getBoardSize();++i){
			hexCells1D[i].setRow(other.hexCells1D[i].getRow());
			hexCells1D[i].setColumn(other.hexCells1D[i].getColumn());
			hexCells1D[i].setData(other.hexCells1D[i].getData());
		}
	}

	// assigment operator
	HexArray1D& HexArray1D::operator=(const HexArray1D& rightside){

		if(this == &rightside)
			return *this;
		else{
			boardSize = rightside.boardSize;
			setGameMode(rightside.gameMode);
			numOfMoves = rightside.numOfMoves;
			turn = rightside.turn;
			operation = rightside.operation;
			numOfMoves = rightside.numOfMoves;

			free(hexCells1D);
			hexCells1D = nullptr;

			setHexCells1D();

			for(int i=0;i<getBoardSize()*getBoardSize();++i){
				hexCells1D[i].setRow(rightside.hexCells1D[i].getRow());
				hexCells1D[i].setColumn(rightside.hexCells1D[i].getColumn());
				hexCells1D[i].setData(rightside.hexCells1D[i].getData());
			}
			return *this;
		}
	}

	// virtual setSize function setting size and creating board
	bool HexArray1D::setSize(int size){
		if(size < 5){
			cerr << endl << "You have typed invalid board size";
			return false;
		}
		boardSize = size;
		if(hexCells1D == nullptr)
			setHexCells1D();
		reset();
		return true;
	}
	
	void HexArray1D::setHexCells1D(){
		hexCells1D = (Cell*) malloc(sizeof(Cell)*getBoardSize()*getBoardSize());
	}
	
	// virtual print function printing the board
	void HexArray1D::print() const {
		char c= 'a';
		int i,j,k;
		int counter = 0;

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
			for(j=0;j<getBoardSize();++j,counter++){	// printing board
				cout << hexCells1D[counter].getData() << ' ';
			}
			cout << endl;
		}
	}

	// virtual reset function resetting the board to the inital position
	void HexArray1D::reset(){
		char c=notOccupied;
		for(int i=0;i<getBoardSize()*getBoardSize();++i){
				hexCells1D[i].setData(c);
				hexCells1D[i].setRow(i);
				hexCells1D[i].setColumn(i);
		}
	}

	char HexArray1D::operator()(int indexr,int indexc) const{

		int index1d = indexr * getBoardSize() + indexc;

		if(indexr >=0 && indexr < getBoardSize()*getBoardSize() && indexc >=0 && indexc < getBoardSize())
			return hexCells1D[index1d].getData();
		else
			throw InvalidIndex();
	}

	bool HexArray1D::isEnd(){
		if(getTurn()%2 == 1)
			return isBlueWin1D();
		else
			return isRedWin1D();
	}

	Cell HexArray1D::lastMove(){
		if(numberOfMoves() == 0)
			throw NoLastMove();
		else{
			if(getTurn()% 2 == 1)
				return Cell(getInputRow(),getInputColumn(),occupiedBlue);
			else
				return Cell(getInputRow(),getInputColumn(),occupiedRed);
		}
	}

	// virtual play function for computers play
	void HexArray1D::play(){

		int index1d = getInputRow() * getBoardSize() + getInputColumn();

		char c='A';
		int i,k;
		increaseNumOfMoves();
		// checking all 6 possible neighbor of cell. Also checking that the possible cells is in board or not( -1 index of array or crossing size)
		if(getInputColumn()+1 <getBoardSize() && hexCells1D[index1d+1].getData() == notOccupied){
			hexCells1D[index1d+1].setData(occupiedRed);

			for(i=0;i<(getInputColumn()+1);++i)	// for printing letter of coordinate, incrementing 'A'.
				c++;
			cout << c << getInputRow()+1 << endl;	// printing coordinate.
		}
		else if(getInputRow()+1 <getBoardSize() && hexCells1D[index1d +getBoardSize() ].getData() == notOccupied){
			hexCells1D[index1d +getBoardSize()].setData(occupiedRed);
			for(i=0;i<getInputColumn();++i)
				c++;
			cout << c << getInputRow()+2 << endl;
		}
		else if(getInputRow()-1 >= 0 && getInputColumn()+1 <getBoardSize() && hexCells1D[index1d - getBoardSize()+1].getData() == notOccupied){
			hexCells1D[index1d - getBoardSize()+1].setData(occupiedRed);
			for(i=0;i<(getInputColumn()+1);++i)
				c++;
			cout << c << getInputRow() << endl;
		}
		else if(getInputRow()-1 >= 0 && hexCells1D[index1d - getBoardSize()].getData() == notOccupied){
			hexCells1D[index1d - getBoardSize()].setData(occupiedRed);
			for(i=0;i<(getInputColumn());++i)
				c++;
			cout << c << getInputRow() << endl;
		}
		else if(getInputColumn()-1 >= 0 && getInputRow()+1 <getBoardSize() && hexCells1D[index1d + getBoardSize() -1].getData() == notOccupied){
			hexCells1D[index1d + getBoardSize() -1].setData(occupiedRed);
			for(i=0;i<(getInputColumn()-1);++i)
				c++;
			cout << c << getInputRow()+2 << endl;
		}
		else if(getInputColumn()-1 >= 0 && hexCells1D[index1d-1].getData() == notOccupied){
			hexCells1D[index1d-1].setData(occupiedRed);
			for(i=0;i<(getInputColumn()-1);++i)
				c++;
			cout << c << getInputRow()+1 << endl;
		}
		else{
			for(i=0;i<getBoardSize()*getBoardSize();++i)
				if(hexCells1D[i].getData() == notOccupied){
					hexCells1D[i].setData(occupiedRed);
					for(k=0;k<i % getBoardSize();++k)
						c++;
					cout << c << i+1 << endl;
					return;
				}
		}
	}

	// virtual play function for users play
	void HexArray1D::play(Cell position){
		increaseNumOfMoves();
		int index1d = position.getRow() * getBoardSize() + position.getColumn();
		if(getTurn()%2 == 1)
			hexCells1D[index1d].setData(position.getData());
		else
			hexCells1D[index1d].setData(position.getData());
	}

	// virtual equal operator for compare to equalty of two hex game
	bool HexArray1D::operator ==(const AbstractHex* other){
		bool rtrn = true;
		if(getBoardSize() != other->getBoardSize())
			rtrn = false;
		else{
			for(int i=0;i<getBoardSize();i++)
				for(int j=0;j<getBoardSize();j++)
					if(operator()(i,j) != other->operator()(i,j))
						rtrn = false;
		}
		return rtrn;
	}

	// virtual funcs for read and write to file
	void HexArray1D::readFromFile(string fName){

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

		for(int i=0;i<getBoardSize()*getBoardSize();++i){	// reading board from file.
				fileStream >> input_c;
				if(input_c != '\n')
					hexCells1D[i].setData(input_c);
				else
					i--;
		}
		fileStream.close();
	}

	void HexArray1D::writeToFile(string fName){
		ofstream fileStream;
		fileStream.open(fName.c_str());

		fileStream << "Board Size:" << getBoardSize() << "\n";
		fileStream << "Game Mode:" << getGameMode() << "\n";
		fileStream << "Turn:" << getTurn()%2 << "\n";
		fileStream << "Number Of Moves:" << numberOfMoves();
		for(int i=0;i<getBoardSize()*getBoardSize();++i){	// writing map to the file.
			if(i % getBoardSize() == 0)
				fileStream << "\n";
			fileStream << hexCells1D[i].getData();
		}
		cout << "Game successfully saved." << endl;
		fileStream.close();
	}

	//funcs for check the win condition
	bool HexArray1D::isBlueWin1D(){
		bool check = false;

		for(int i=0;i<getBoardSize();++i){	// finding occupied cell in first column
			if(hexCells1D[i*getBoardSize()].getData() == occupiedBlue)
				// checking whether is cell reach other side or not
				if(recCheckBlue(static_cast<int>(i/getBoardSize()),0,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
					hexCells1D[i*i].setData(winBlue);									// will be true.
					recCapitalBlue1D(i*i);
					print();
					cout << endl <<"!Game Over! The Blue Side Won!!" << endl;
					check = true;
				}
		}
		return check;
	}

	bool HexArray1D::isRedWin1D(){
		bool check = false;

		for(int i=0;i<getBoardSize();++i){	// finding occupied cell in first row
			if(hexCells1D[i].getData() == occupiedRed)
				// checking whether is cell reach other side or not
				if(recCheckRed(0,i,0)==true){	// if the answer yes, the connected cells will be upper case. and check variable
					hexCells1D[i].setData(winRed);									// will be true.
					recCapitalRed1D(i);
					print();
					cout << endl <<"!Game Over! The Red Side Won!!" << endl;
					check = true;
				}
		}
		return check;
	}

	// funcs for making capital the win path
	bool HexArray1D::recCapitalBlue1D(int index1d){

		if(index1d !=0 && index1d%getBoardSize() == 0)
			return true;
		else if(index1d+1 < getBoardSize() && hexCells1D[index1d+1].getData() == occupiedBlue){
			hexCells1D[index1d+1].setData(winBlue);
			return recCapitalBlue1D(index1d+1);
		}
		else if(index1d+1+getBoardSize() < getBoardSize()*getBoardSize() && hexCells1D[index1d+getBoardSize()].getData() == occupiedBlue){
			hexCells1D[index1d+getBoardSize()].setData(winBlue);
			return recCapitalBlue1D(index1d+getBoardSize());
		}
		else if(index1d-getBoardSize() >=0 && index1d+1 < getBoardSize() && hexCells1D[index1d-getBoardSize()+1].getData()  == occupiedBlue){
			hexCells1D[index1d-getBoardSize()+1].setData(winBlue);
			return recCapitalBlue1D(index1d-getBoardSize()+1);
		}
		else if(index1d-getBoardSize() >=0 && hexCells1D[index1d-getBoardSize()].getData()  == occupiedBlue){
			hexCells1D[index1d-getBoardSize()].setData(winBlue);
			return recCapitalBlue1D(index1d-getBoardSize());
		}
		else if(index1d+getBoardSize() < getBoardSize() && index1d-1 >=0 && hexCells1D[index1d+getBoardSize()-1].getData()  == occupiedBlue){
			hexCells1D[index1d+getBoardSize()-1].setData(winBlue);
			return recCapitalBlue1D(index1d+getBoardSize()-1);
		}
		else if(index1d-1 >=0 && hexCells1D[index1d-1].getData()  == occupiedBlue){
			hexCells1D[index1d-1].setData(winBlue);
			return recCapitalBlue1D(index1d-1);
		}
		else
			return false;
	}

	bool HexArray1D::recCapitalRed1D(int index1d){

		if(index1d !=0 && index1d%getBoardSize() == 0)
			return true;
		else if(index1d + getBoardSize() < getBoardSize()*getBoardSize() && hexCells1D[index1d + getBoardSize()].getData() == occupiedRed){
			hexCells1D[index1d + getBoardSize()].setData(winRed);
			return recCapitalRed1D(index1d + getBoardSize());
		}
		else if(index1d + getBoardSize() < getBoardSize()*getBoardSize() && index1d-1 >= 0 && hexCells1D[index1d + getBoardSize()-1].getData() == occupiedRed){
			hexCells1D[index1d + getBoardSize()-1].setData(winRed);
			return recCapitalRed1D(index1d + getBoardSize()-1);
		}
		else if(index1d+1 < getBoardSize() && hexCells1D[index1d+1].getData() == occupiedRed){
			hexCells1D[index1d+1].setData(winRed);
			return recCapitalRed1D(index1d+1);
		}
		else if(index1d-1 >= 0 && hexCells1D[index1d-1].getData() == occupiedRed){
			hexCells1D[index1d-1].setData(winRed);
			return recCapitalRed1D(index1d-1);
		}
		else if(index1d-getBoardSize() >=0 && index1d+1 < getBoardSize() && hexCells1D[index1d-getBoardSize()].getData() == occupiedRed){
			hexCells1D[index1d-getBoardSize()+1].setData(winRed);
			return recCapitalRed1D(index1d-getBoardSize()+1);
		}
		else if(index1d-getBoardSize() >=0 && hexCells1D[index1d-getBoardSize()].getData() == occupiedRed){
			hexCells1D[index1d-getBoardSize()].setData(winRed);
			return recCapitalRed1D(index1d-getBoardSize());
		}
		else
			return false;
	}

	HexArray1D::~HexArray1D(){
		free(hexCells1D);
		hexCells1D = nullptr;
	}

} /* AYaziciHexGame */
