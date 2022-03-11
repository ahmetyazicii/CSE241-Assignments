#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

void rules_of_game();
void create_initial_map(char map[12][12],int size);
void print_map(char map[12][12],int size);
int get_board_size();
int get_game_mode();
int get_user_color();
void game_on(char map[12][12],int size,int mode);
void get_move_from_user(char map[12][12],int size,int *row,int *column);
void game_on_mode1(char map[12][12],int size);
void game_on_mode2_user_blue(char map[12][12],int size);
void game_on_mode2_user_red(char map[12][12],int size);
int char_to_int(char c);
bool check_validity_of_move(char map[12][12],int size,int row, int column);
bool recursive_check_blue(char map[12][12],int size,int r,int c,int counter);
bool win_check_for_blue(char map[12][12],int size);
bool win_check_for_red(char map[12][12],int size);
bool recursive_check_red(char map[12][12],int size,int r,int c,int counter);
void make_computer_move_red(char map[12][12],int size,int user_r,int user_c);
void make_computer_move_blue(char map[12][12],int size,int user_r,int user_c);
bool recursive_capital_blue(char map[12][12],int size,int r,int c);
bool recursive_capital_red(char map[12][12],int size,int r,int c);

#endif /* FUNCTIONS_H_ */
