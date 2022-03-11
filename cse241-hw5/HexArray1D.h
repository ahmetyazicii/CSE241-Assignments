#ifndef HEXARRAY1D_H_
#define HEXARRAY1D_H_

#include<iostream>
#include<cstdlib>
#include<string>
#include"AbstractHex.h"

using namespace std;

namespace AYaziciHexGame{

	class HexArray1D : public AbstractHex{
		
	public:
		
		HexArray1D();
		HexArray1D(int size,int mode);
		
		HexArray1D(const HexArray1D& other);
		HexArray1D& operator=(const HexArray1D& rightside);

		virtual bool setSize(int size);
		void setHexCells1D();
		
		virtual void print() const;
		virtual void reset();

		virtual char operator()(int indexr,int indexc) const;
		virtual Cell lastMove();
		virtual bool operator==(const AbstractHex* other);
		virtual void play();	// plays for computer
		virtual void play(Cell position);	// plays for user

		virtual void readFromFile(string fName);
		virtual void writeToFile(string fName);

		virtual bool isEnd();
		bool isBlueWin1D();
		bool isRedWin1D();
		bool recCapitalBlue1D(int index1d);
		bool recCapitalRed1D(int index1d);

		 ~HexArray1D();
		
	private:
		Cell *hexCells1D;
		
	};

} //AYaziciHexGame


#endif /* HEXARRAY1D_H_ */
