#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <iostream>
#include <string>

using std::size_t;

namespace presets
{
	inline constexpr char listO[]{ '*', '/', '+', '-' };

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
	inline constexpr size_t start{};
}

namespace stringSize
{
	inline constexpr size_t empty{};
}

#endif
