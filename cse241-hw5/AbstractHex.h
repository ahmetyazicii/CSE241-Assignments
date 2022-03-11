#ifndef ABSTRACTHEX_H_
#define ABSTRACTHEX_H_

#include<iostream>
#include<string>

using namespace std;

namespace AYaziciHexGame{

	class Cell{
        
        public:
       		Cell();
          	Cell(int r,int c,char d);
                                        
          	// getters
			char getData() const;
			int getRow() const;
			int getColumn() const;

			//setters
			void setRow(int r);
			void setColumn(int c);
			void setData(char d) ;
                                        
  	private:
			int row;
			int column;
			char data;
  	};
                  

        class AbstractHex{

        public:
			// constructors
			AbstractHex();

			// setters
			virtual bool setSize(int size);
			bool setGameMode(int mode);
			void setInputRow(int r);
			void setInputColumn(char c);
			void setOperation(int oprt);
			bool setFileName(string str);
			void setTurn(int t);
			void increaseTurn();
			void decreaseTurn();
			void setNumOfMoves(int n);
			void increaseNumOfMoves();

			// getters
			int getBoardSize() const;
			int getGameMode() const;
			int getInputRow() const;
			int getInputColumn() const;
			int getOperation() const;
			int getTurn() const;
			string getFileName() const;
			int numberOfMoves() const ;


			void playGame();
    		void playGameModes();
    		void playGMode1();
    		void playGMode2();
    		void getInput();
    		bool checkValidInputMove();
    		virtual void play() = 0;	// plays for computer
    		virtual void play(Cell position) = 0;	// plays for user


    		virtual void writeToFile(string fName) = 0;
    		virtual void readFromFile(string fName) = 0;
    
    		void continueGame();
    		void printLoadedGameInfo();
    		void LOADoperation(string str);

			void parseString(string str);
    	
			virtual void print() const = 0;
			virtual void reset() = 0;
			virtual bool isEnd() = 0;
			virtual char operator()(int indexr,int indexc) const = 0;
			virtual Cell lastMove() = 0;
			virtual bool operator==(const AbstractHex* other) = 0;

			bool recCheckBlue(int r, int c,int counter) ;
			bool recCheckRed(int r, int c,int counter) ;

			// virtual destructor
			virtual ~AbstractHex();
        protected:
			int boardSize;
			int gameMode;
			int inputRow;
			int inputColumn;
			string fileName;
			int turn;
			int operation;
			int numOfMoves;

        };

} // AYaziciHexGame

#endif /* ABSTRACTHEX_H_ */
