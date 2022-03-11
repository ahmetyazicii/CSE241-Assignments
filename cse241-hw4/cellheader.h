/*
 * cellheader.h
 *
 *  Created on: Dec 8, 2020
 *      Author: cse312
 */

#ifndef CELLHEADER_H_
#define CELLHEADER_H_

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
using std::ostream;
using std::string;
using std::ofstream;
using std::ifstream;
#include"hexheader.h"

class Hex::Cell{
public:
	Cell (char data_value);
	Cell();
	inline char getData() const;
	inline void setData(char data_value);
private:
	char data;
};






#endif /* CELLHEADER_H_ */
