CFLAGS=-c -Wall -Wextra -std=c++11

all: program

program: main.o hexclass.o 
	g++ main.o hexclass.o  -o program
	
main.o: main.cpp hexclass.cpp
	g++ $(CFLAGS) main.cpp hexclass.cpp

hexclass.o: hexclass.cpp
	g++ $(CFLAGS) hexclass.cpp
	
clean:
	rm -rf *o program
