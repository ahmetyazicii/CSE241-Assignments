CFLAGS=-c -Wall -Wextra -std=c++11

all: program

program: main.o AbstractHex.o HexVector.o HexArray1D.o
	g++ main.o AbstractHex.o HexVector.o HexArray1D.o  -o program
	
main.o: main.cpp AbstractHex.cpp HexVector.cpp HexArray1D.cpp
	g++ $(CFLAGS) main.cpp AbstractHex.cpp HexVector.cpp HexArray1D.cpp

HexArray1D.o: HexArray1D.cpp
	g++ $(CFLAGS) HexArray1D.cpp

HexVector.o: AbstractHex.cpp
	g++ $(CFLAGS) HexVector.cpp

AbstractHex.o: AbstractHex.cpp
	g++ $(CFLAGS) AbstractHex.cpp
	
clean:
	rm -rf *o program
