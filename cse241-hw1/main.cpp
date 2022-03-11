#include<iostream>
#include<string>
#include"functions.h"
using namespace std;

int main(){

	char game_map[12][12];
	int board_size,game_mode;

	cout << "\t\t\t---Welcome to the Hex Game---" << endl;

	rules_of_game();							// printing rules of game
	board_size = get_board_size();				// receiving board size from user
	create_initial_map(game_map,board_size);	// creating initial map according the board size
	game_mode  = get_game_mode();				// receiving game mode info from user

	game_on(game_map,board_size,game_mode);		// starting game
	return 0;
}



