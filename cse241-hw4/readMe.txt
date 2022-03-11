This homework i used menu to make things much easy clear(testing the class).
I create 5 Hex object(in vector).So there will be max 5 games playable at the same time.
There are 8 options in menu( one is exit).
1-is creating new game.
2-is switching game among current games.
3-is load the game. User load games with menu. However save command is still in input line(like homework2).
4-is undo operation(user can select pre or post decrement operator) 
5-is print all marked cells.
6-is compare two games.
7-is prints the current(online games).
and 8 is exit. 


NOTE: The warning message received from compiler when trying to overload << operator for file with ofstream object( detailed description in cpp file)


hexclass.cpp: In function ‘std::ofstream& operator<<(std::ofstream&, const Hex&)’:
hexclass.cpp:269:51: warning: ISO C++ says that these are ambiguous, even though the worst conversion for the first is better than the worst conversion for the second: [enabled by default]
     outputStream << object.hexCells[i][j].getData();
                                                   ^
In file included from /usr/include/c++/4.8/iostream:39:0,
                 from hexclass.cpp:1:
/usr/include/c++/4.8/ostream:482:5: note: candidate 1: std::basic_ostream<char, _Traits>& std::operator<<(std::basic_ostream<char, _Traits>&, char) [with _Traits = std::char_traits<char>]
     operator<<(basic_ostream<char, _Traits>& __out, char __c)
     ^
hexclass.cpp:259:11: note: candidate 2: std::ofstream& operator<<(std::ofstream&, const Hex&)
 ofstream& operator <<(ofstream& outputStream, const Hex& object){

