#include<iostream>
#include<string>
#include<vector>
#include<stdexcept>
#include"AbstractHex.h"
#include"HexVector.h"
#include"HexArray1D.h"
#include"My_Exceptions.h"

using namespace std;
using namespace AYaziciHexGame;


bool checkValidGameGlobal(AbstractHex* obj){
	bool check = true;

	if(obj->getBoardSize() < 5)
		check = false;

	else{
		if(obj->isEnd() != true){
			for(int i=0;i<obj->getBoardSize();++i){
				for(int j=0;j<obj->getBoardSize(); ++j){
					if(obj->operator()(i,j) == '.' || obj->operator()(i,j) == 'x' || obj->operator()(i,j) == 'o' )
						{   /* deliberately empty */   }
					else
						check = false;
					}
				}
			}
		else
			cout << "The Game is end game.\n";
	}
	return check;
}

int main(){
	int index = 0;
	string input;
	int choose,gamechoose;
	int compare1,compare2;
	vector <AbstractHex*> games(5);

	cout << "\t\t\t---Welcome to the Hex Game---" << endl;
	do{
		cout << endl << "Please select from menu:" << endl;
		cout <<"1-Create New Game" << endl
		 	 <<"2-Change The Current Game" << endl
			 <<"3-Load Game" << endl
		 	 <<"4-Number of Moves in Each Game" << endl
			 <<"5-Compare Two Games." << endl
			 <<"6-Show Current Games." << endl
		 	 <<"7-Check The Validity of Game." << endl
			 <<"8-Exit" << endl;
		getline(cin,input);
		choose = stoi(input);

		switch(choose){
			case 1:{
				cout << "Selecet Board Type:" << endl
					 << "1-HexVector" << endl
					 << "2-HexArray1D" << endl;
				getline(cin,input);
				gamechoose = stoi(input);
				if(gamechoose == 1){
					games[index] = new HexVector();
					games[index]->playGame();
				}
				if(gamechoose == 2){
					games[index] = new HexArray1D();
					games[index]->playGame();
				}
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
						games[stoi(input)-1]->continueGame();
					else
						cout <<"Invalid game number." << endl;
				}
				break;
			}
			case 3:{
				cout << "Please write the name of text file(only .txt and .TXT allowed)" << endl;
				getline(cin,input);
				try {
					games[index] = new HexArray1D();
					games[index]->readFromFile(input);
					games[index]->continueGame();
					index++;
				}
				catch(InvalidFile& excp){
					cerr << excp.what();
				}
				break;
			}
			case 4:{
				try{
					for(int i=0; i < index; ++i)
						cout << "Number Of Moves in Game " <<i+1 << " is: " << games[i]->numberOfMoves() << endl;
				}
				catch(NoLastMove& excp2){
					cerr << excp2.what();
				}
				break;
			}
			case 5:{
				cout << endl << "Type 2 game number that you want to compare(ex. 12)" << endl;
				getline(cin,input);
				compare1=(input[0] -'0') - 1;
				compare2=(input[1] -'0') - 1;
				if(compare1 < index && compare2 < index){
					if(games[compare1]->operator==(games[compare2])){
						cout << "Games are equal each other and common map is printing...\n";
						games[compare1]->print();
					}
					else
						cout << "Games are not equal each other.\n";
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
			case 7:{
				cout << endl << "Type the game number that you want to check validity" << endl;
				getline(cin,input);
				int validitygame =(input[0] -'0') - 1;

				if(validitygame < index){
					if(checkValidGameGlobal(games[validitygame]) == true){
						cout << "Game is Valid.Board of game is printing..\n";
						games[validitygame]->print();
					}
					else
						cout <<"Game is not valid.\n";
				}
				else
					cout << "Typed invalid games numbers" << endl;
				break;
			}
			case 8:
				cout << endl << "Have a nice day! :)" << endl;
				break;

		}
	}while(choose != 8);


	for(int i=0;i< index;i++)
		delete games[i];

	return 0;
}
