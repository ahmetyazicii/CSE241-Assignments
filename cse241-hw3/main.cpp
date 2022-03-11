#include<iostream>
#include<vector>
#include"header.h"
#include<string>
#include<fstream>
using namespace std;
using std::string;
using std::ofstream;
using std::ifstream;

int Hex::allMarked = 0;

int main(){

	int index = 0;
	string input;
	int choose;
	int compare1,compare2;
	vector <Hex> games(5);

	cout << "\t\t\t---Welcome to the Hex Game---" << endl;
	do{
		cout << endl << "Please select from menu:" << endl;
		cout <<"1-Create New Game" << endl
		 	 <<"2-Change The Current Game" << endl
			 <<"3-Load Game" << endl
		 	 <<"4-Show Marked Cells in All Games" << endl
			 <<"5-Compare Two Games." << endl
			 <<"6-Show Current Games" << endl
		 	 <<"7-Exit" << endl;
		getline(cin,input);
		choose = stoi(input);

		switch(choose){
			case 1:{
				games[index].playGame();
				index++;
				break;
			}
			case 2:{
				if(index == 0)
					cout << "There are not any available games." << endl;
				else{
					cout << "Type number of game:   ";
					getline(cin,input);
					if(stoi(input) <= index)
						games[stoi(input)-1].continueGame();
					else
						cout <<"Invalid game number." << endl;
				}
				break;
			}
			case 3:{
				cout << "Please write the name of text file(only .txt and .TXT allowed)" << endl;
				getline(cin,input);
				Hex load_game;
				games.push_back(load_game);
				games[index].loadFile(input);
				index++;
				break;
			}
			case 4:{
				for(int i=0; i < index; ++i)
					cout << "Marked Cells in Game " <<i+1 << " is: " << games[i].getMarkedCells() << endl;
				cout << endl << "There are total " <<  Hex::getAllMarked()  <<" marked cells in " << index << " games."<< endl;
				break;
			}
			case 5:{
				cout << endl << "Type 2 game number that you want to compare(ex. 12)" << endl;
				getline(cin,input);
				compare1=(input[0] -'0') - 1;
				compare2=(input[1] -'0') - 1;
				if(compare1 < index && compare2 < index){
					cout << "Marked Cells in Game " << compare1+1 << " is: " << games[compare1].getMarkedCells() << endl;
					cout << "Marked Cells in Game " << compare2+1 << " is: " << games[compare2].getMarkedCells() << endl;
					if(games[compare1].compareBoards(games[compare2]))
						cout << "Game" << compare1+1 << " is > than "  <<  "Game" << compare2+1 << endl;
					else if(games[compare1].getMarkedCells() == games[compare2].getMarkedCells())
						cout << "Game" << compare1+1 << " is = to "  <<  "Game" << compare2+1 << endl;
					else
						cout << "Game" << compare2+1 << " is > than "  <<  "Game" << compare1+1 << endl;

				}
				else
					cout << "Typed invalid games numbers" << endl;
				break;
			}

			case 6:{
				if(index == 0)
					cout << "There are not any available games." << endl;
				else{
					cout << endl << "Available games are:" << endl;
					for(int i=1; i <= index; ++i)
						cout << "Game " << i << endl;
				}
				break;
			}
			case 7:
				cout << endl << "Have a nice day! :)" << endl;
				break;

		}
	}while(choose != 7);

}
