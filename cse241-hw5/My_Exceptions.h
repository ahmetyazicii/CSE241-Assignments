#ifndef MY_EXCEPTIONS_H_
#define MY_EXCEPTIONS_H_

#include<stdexcept>

class InvalidSize : public runtime_error
{
public:
	InvalidSize() : runtime_error("You have typed invalid board size.\n") { }
};

class InvalidIndex : public runtime_error
{
public:
	InvalidIndex() : runtime_error("You are trying to reach invalid index.\n") { }
};

class NoLastMove : public runtime_error
{
public:
	NoLastMove() : runtime_error("There is not any last move.\n") { }
};

class InvalidFile : public runtime_error
{
public:
	InvalidFile() : runtime_error("File can not opened.\n") { }
};

#endif /* MY_EXCEPTIONS_H_ */
