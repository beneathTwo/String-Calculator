#ifndef MATH_TYPES_H
#define MATH_TYPES_H
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
	VALID,
	DIVISION_BY_ZERO,
	INVALID_OPERATION,
	INVALID_INPUT,
	OUT_OF_RANGE,
};

using sCode_t = StatusCodes;

struct MathOperator
{
	char uOp{};
	std::size_t ePos{};
};

using mOp_t = MathOperator;

struct MathTerm
{
	double uTerm{};
	std::size_t ePos{};
};

using mTerm_t = MathTerm;

#endif
