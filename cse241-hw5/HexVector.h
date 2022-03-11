#ifndef HEXVECTOR_H_
#define HEXVECTOR_H_

#include<iostream>
#include<vector>
#include<string>
#include"AbstractHex.h"

using namespace std;

namespace AYaziciHexGame{

	class HexVector : public AbstractHex{
	public:	

		HexVector();
		HexVector(int size,int mode);

		virtual bool setSize(int size);
		void setHexCells();

		virtual void print() const;
		virtual void reset();
		virtual bool isEnd();
		virtual char operator()(int indexr,int indexc) const;
		virtual Cell lastMove();
		virtual bool operator==(const AbstractHex* other);
		virtual void play();	// plays for computer
		virtual void play(Cell position);	// plays for user

		virtual void readFromFile(string fName);
		virtual void writeToFile(string fName);
		
		bool isBlueWin();
		bool isRedWin();
		bool recCapitalBlue(int r,int c);
		bool recCapitalRed(int r,int c);

		~HexVector();

	private:
		vector < vector< Cell > > hexCells;
	};

} //AYaziciHexGame

#endif /* HEXVECTOR_H_ */
