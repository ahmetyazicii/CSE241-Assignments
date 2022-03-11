#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include<string>
#include<fstream>
using std::string;
using std::ofstream;
using std::ifstream;

void rules_of_game();
void create_initial_map(char map[12][12],int size);
void print_map(const char map[12][12],const int size);
int get_board_size();
int get_game_mode();
int get_user_color();
void game_on(char map[12][12],int size,int mode);
void print_saved_game(const char map[12][12],const int gameInfo[3]);
void get_move_from_user(char map[12][12],int size,int& row,int& column,int gameInfo[3],int& game_continue);
int getOperationInfo(string& fileName,int& row,char& column);
bool performOperations(char map[12][12],int gameInfo[3],const string& fileName,const int& operation);
void game_on_mode1(char map[12][12],int gameInfo[3],int &game_continue,int turn=0);
void game_on_mode2_user_blue(char map[12][12],int gameInfo[3],int &game_continue,int turn=0);
void game_on_mode2_user_red(char map[12][12],int gameInfo[3],int &game_continue,int turn=1);
void performLoadOperation(ifstream& fileStream,char map[12][12],int gameInfo[3]);
void performSaveOperation(ofstream& fileStream,char map[12][12],int gameInfo[3]);
int char_to_int(char c);
bool check_validity_of_move(const char map[12][12],const int& size,const int& row,const int& column);
bool recursive_check_blue(char map[12][12],int size,int r,int c,int counter=0);
bool win_check_for_blue(char map[12][12],int size);
bool win_check_for_red(char map[12][12],int size);
bool recursive_check_red(char map[12][12],int size,int r,int c,int counter=0);
void make_computer_move_red(char map[12][12],int size,int user_r,int user_c);
void make_computer_move_blue(char map[12][12],int size,int user_r,int user_c);
bool recursive_capital_blue(char map[12][12],int size,int r,int c);
bool recursive_capital_red(char map[12][12],int size,int r,int c);

#endif /* FUNCTIONS_H_ */
