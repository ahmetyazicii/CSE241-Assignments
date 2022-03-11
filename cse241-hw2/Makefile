CFLAGS=-c -Wall -Wextra -std=c++11

all: program

program: main.o functions.o 
	g++ main.o functions.o  -o program
	
main.o: main.cpp
	g++ $(CFLAGS) main.cpp

functions.o: functions.cpp
	g++ $(CFLAGS) functions.cpp
	
clean:
	rm -rf *o program