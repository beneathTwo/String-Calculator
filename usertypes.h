#ifndef USER_TYPES_H
#define USER_TYPES_H
#include <iostream>

enum MathOperations : char
{
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
};

enum class StatusCodes
{
	CHANGE_TYPE = -1,
	VALID,
	DIVISION_BY_ZERO,
	INVALID_OPERATION,
	INVALID_INPUT,
	OUT_OF_RANGE,
};

struct MathOperator
{
	char uOp{};
	std::size_t ePos{};
	StatusCodes eCode{};
};

using mop_t = MathOperator;

struct MathTerm
{
	long uTerm{};
	std::size_t ePos{};
	StatusCodes eCode{};
	double uFTerm{};
};

using mterm_t = MathTerm;

#endif
