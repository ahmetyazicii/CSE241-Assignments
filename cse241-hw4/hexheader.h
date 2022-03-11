#ifndef HEXHEADER_H_
#define HEXHEADER_H_

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
using std::ostream;
using std::string;
using std::ofstream;
using std::ifstream;


class Hex{

public:

	explicit Hex(int size,int mode);
	Hex(int size);
	Hex();

	// Big three provided.
	Hex(const Hex& hexObject);
	Hex& operator =(const Hex& rightSide);
	~Hex();

	class Cell;


	inline int getSize() const;
	inline int getMode() const;
	inline int getInputRow() const;
	inline int getInputColumn() const;
	inline int getOperation() const;
	inline int getTurn() const;
	inline int getScoreRed() const;
	inline int getScoreBlue() const;
	inline string getFileName() const;
	int getMarkedCells() const;
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
	inline void decreaseMarkedCells();
	inline void decreaseTurn();
	inline void increaseTurn();
	inline void setScoreBlue(int score);
	inline void setScoreRed(int score);
	void setHexCells();
	void setMoveHistory();

	friend ostream& operator <<(ostream& outputStream,const Hex& object);
	//friend ofstream& operator <<(ofstream& outputStream,const Hex& object);
	friend istream& operator >>(istream& outputStream,Hex& object);
	void playGame();
	void playGameModes();
	void playMode1();
	void playMode2();

	void loadFile(string str);
	void continueGame();
	void printGameInfo();


	string getInput();
	bool checkValidMove();
	Cell play();
	Cell play(int row,int column);


	void findScoreRed();
	void findScoreBlue();

	bool isGameEnd();
	bool isBlueWin();
	bool isRedWin();
	bool recCheckBlue(int r,int c,int counter) const;
	bool recCheckRed(int r,int c,int counter) const;
	bool recCapitalBlue(int r,int c);
	bool recCapitalRed(int r,int c);

	Hex& operator--();
	Hex operator--(int empty);
	friend bool operator==(const Hex& object1,const Hex& object2);
	friend bool operator<(const Hex& object1,const Hex& object2);
	friend bool operator>(const Hex& object1,const Hex& object2);



private:
	int boardSize;
	int markedCells;
	int operation;
	int scoreRed;
	int scoreBlue;
	int gameMode;
	int inputRow;
	int inputColumn;
	int turn;
	static int allMarked;
	string fileName;

	int **moveHistory;
	Cell ** hexCells;

	void parseString(string str);

};



#endif /* HEXHEADER_H_ */
