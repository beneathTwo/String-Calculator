#include "constants.h"
#include "mathtypes.h"
#include "stringtranslate.h"

#include <iostream>

void printError(sCode_t eCode)
{
	if (eCode > sCode_t::VALID)
	{
		std::cerr << "error: ";

		using presets::errorString;
		std::cerr << errorString[static_cast<int>(eCode)] << "\n\n";
	}
}

void evaluateEquation(mTerm_t a, mTerm_t b, mOp_t opA)
{
	double termC{};
	if (opA.uOp == MUL)
		termC = a.uTerm * b.uTerm;
	else if (opA.uOp == DIV)
		if (a.uTerm == 0)
			throw sCode_t::DIVISION_BY_ZERO;
		else
			termC = a.uTerm / b.uTerm;
	else if (opA.uOp == ADD)
		termC = a.uTerm + b.uTerm;
	else if (opA.uOp == SUB)
		termC = a.uTerm - b.uTerm;

	std::cout << "= " << termC << "\n\n";
}

void answerString(std::string uString)
{
	try
	{
		mTerm_t termA{ getTerms(uString, stringPositions::start) };

		mOp_t opA{ getOperator(uString, termA.ePos) };

		// Move up 1 from the op position to avoid an invalid input
		// if subtraction.
		mTerm_t termB{ getTerms(uString, opA.ePos + 1) };

		evaluateEquation(termA, termB, opA);
	}
	catch (sCode_t& oops)
	{
		printError(oops);
	}
}