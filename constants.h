#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>

using std::size_t;

namespace defaultValue
{
	inline constexpr char noList[]{ 'n','o' };
	inline constexpr char listO[]{ '+', '/', '*', '-' };

	inline constexpr char errorString[][20]
	{
		"none", 
		"division by zero", 
		"invalid operation",
		"invalid input",
		"out of range value"
	};

	inline constexpr bool present{ true };
}

namespace stringPositions
{
	inline constexpr size_t defaultOp{ 3 };
	inline constexpr size_t start{};
}

namespace stringSize
{
	inline constexpr size_t empty{};
}

namespace programStatus
{
	inline constexpr bool run{ true };
	inline constexpr bool exit{ false };
}

#endif
