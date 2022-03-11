#ifndef HEADER_H_
#define HEADER_H_

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;
using std::string;
using std::ofstream;
using std::ifstream;


class Hex{
public:
	Hex(int size,int mode);
	Hex(int size);
	Hex();
	inline int getSize() const;
	inline int getMode() const;
	inline int getInputRow() const;
	inline int getInputColumn() const;
	int getMarkedCells() const;
	inline int getOperation() const;
	inline int getTurn() const;
	inline string getFileName() const;
	static int getAllMarked(){ return allMarked;}

	bool setSize(int size);
	inline void setOperation(int oprt);
	bool setMode(int mode);
	inline void setTurn(int t);
	bool setFileName(string str);
	inline void setInputRow(int row);
	inline void setInputColumn(char column);
	inline void setMarkedCells(int value);
	inline void increaseMarkedCells();
	inline void decreaseTurn();
	inline void increaseTurn();

	void setHexCells();

	void displayBoard() const;
	void playGame();
	void playMode1();
	void playMode2();
	string getInput();
	bool checkValidMove();
	void play();
	void play(int row,int column);

	void playGameModes();
	void setLoadFile();
	void continueGame();
	void printGameInfo();
	void saveFile();
	void loadFile(string str);

	bool isGameEnd() ;
	bool isBlueWin() ;
	bool isRedWin() ;
	bool recCheckBlue(int r,int c,int counter) const;
	bool recCheckRed(int r,int c,int counter) const;
	bool recCapitalBlue(int r,int c);
	bool recCapitalRed(int r,int c);

	bool compareBoards(const Hex& other) const;

private:

	int inputRow;
	int inputColumn;
	int markedCells;
	int operation;
	int turn;
	int boardSize;
	int gameMode;
	static int allMarked;
	void parseString(string str);
	string fileName;

	class Cell{
	public:

		Cell (char data_value);
		Cell();

		inline char getData() const;
		inline void setData(char data_value);
	private:

		char data;

	};
	vector< vector<Cell> > hexCells;




};

#endif /* HEADER_H_ */
