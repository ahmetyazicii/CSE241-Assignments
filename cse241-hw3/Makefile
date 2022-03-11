CFLAGS=-c -Wall -Wextra -std=c++11

all: program

program: main.o hexClass.o 
	g++ main.o hexClass.o  -o program
	
main.o: main.cpp hexClass.cpp
	g++ $(CFLAGS) main.cpp hexClass.cpp

hexClass.o: hexClass.cpp
	g++ $(CFLAGS) hexClass.cpp
	
clean:
	rm -rf *o program
