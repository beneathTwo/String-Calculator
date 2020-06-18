#include "constants.h"
#include "stringtranslate.h"
#include "usertypes.h"

#include <cctype>
#include <iostream>
#include <string>

// These just run through a list of characters to allow.
bool checkList(std::string uString, std::size_t pPos, const char sChars[])
{
	for (int countChar{}; countChar < sizeof(sChars); ++countChar)
		if (uString.at(pPos) == sChars[countChar])
			return true;

	return false;
}

bool checkListWNum(std::string uString, std::size_t pPos, const char sChars[])
{
	for (int countChar{}; countChar < sizeof(sChars); ++countChar)
		if (uString.at(pPos) == sChars[countChar] || std::isdigit(uString.at(pPos)))
			return true;

	return false;
}

//	Characters that have no signification to the operation are skipped over and deleted.
std::string removeJunkCharacters(std::string uString, std::size_t sPos)
{
	// Not a digit or char in the list, then continue to scan for the wanted chars.
	// If it comes up on a negative sign It'll check for a number infront of it.
	// If a missing term is detected the whole thing is deleted to throw out an invalid input.
	char listT[]{ '-', '.' };
	std::size_t pPos{ sPos };
	for (pPos; pPos < uString.size() && !std::isdigit(uString.at(pPos))
		&& !(checkList(uString, pPos, listT) && std::isdigit(uString.at(pPos + 1))); ++pPos)
		if (checkList(uString, pPos, defaultValue::listO))
			return uString.erase(sPos, uString.size());
			
	return uString.erase(sPos, pPos);
}

mterm_t stringToTerm(std::string uString, std::size_t pA, std::size_t pB, bool dec)
{
	mterm_t gTerm{};
	gTerm.ePos = pB;
	if (dec)
	{
		gTerm.uFTerm = std::stod(uString.substr(pA, pB));
		gTerm.eCode = StatusCodes::CHANGE_TYPE;
	}
	else
	{
		try
		{
			gTerm.uTerm = std::stol(uString.substr(pA, pB));
		}
		catch (std::out_of_range&)
		{
			gTerm.uFTerm = std::stod(uString.substr(pA, pB));
			gTerm.eCode = StatusCodes::CHANGE_TYPE;
		}
	}

	return gTerm;
}

mterm_t getTerms(std::string uString, std::size_t sPos)
{
	// Clean up depending on position.
	if (sPos > stringPositions::start)
	{
		uString.erase(stringPositions::start, sPos);
		sPos = stringPositions::start;
		uString = removeJunkCharacters(uString, sPos);
	}
	else
		uString = removeJunkCharacters(uString, sPos);

	if (uString.size() == stringSize::empty)
	{
		mterm_t gTerm{ 0, stringPositions::start, StatusCodes::INVALID_INPUT };
		return gTerm;
	}

	// Grab the term.
	char listT[]{ '-', '.' };
	std::size_t pPos{ sPos };
	int decCount{};
	for (pPos; pPos < uString.size() && checkListWNum(uString, pPos, listT); ++pPos)
	{
		if (uString.at(pPos) == '-' && pPos != stringPositions::start 
			|| decCount > 1)
			break;
		if (uString.at(pPos) == '.')
			++decCount;
	}

	// if there's an overflow just give a double.
	return stringToTerm(uString, sPos, pPos, decCount);
}

mop_t getOperator(std::string uString, std::size_t termAEnd)
{
	// Delete what's before so the wrong operation isn't grabbed.
	uString.erase(stringPositions::start, termAEnd);

	// Go through the list until the operation is found.
	using defaultValue::listO;
	mop_t opA{};
	for (std::size_t checkChar{}; checkChar < sizeof(listO); ++checkChar)
		if (uString.find(listO[checkChar]) != std::string::npos)
		{
			opA.ePos = uString.find(listO[checkChar]) + termAEnd;
			opA.uOp = listO[checkChar];
			return opA;
		}

	opA.eCode = StatusCodes::INVALID_OPERATION;
	return opA;
}

mterm_t evaluateEquation(mterm_t a, mterm_t b, mop_t opA) 
{
	mterm_t answer{};
	if (a.eCode < StatusCodes::VALID || b.eCode < StatusCodes::VALID)
	{
		if (!(a.eCode < StatusCodes::VALID))
			a.uFTerm = static_cast<double>(a.uTerm);
		if (!(b.eCode < StatusCodes::VALID))
			b.uFTerm = static_cast<double>(b.uTerm);

		if (opA.uOp == MUL)
			answer.uFTerm = a.uFTerm * b.uFTerm;
		else if (opA.uOp == DIV)
			if (b.uFTerm == 0)
				answer.eCode = StatusCodes::DIVISION_BY_ZERO;
			else
				answer.uFTerm = a.uFTerm / b.uFTerm;
		else if (opA.uOp == ADD)
			answer.uFTerm = a.uFTerm + b.uFTerm;
		else if (opA.uOp == SUB)
			answer.uFTerm = a.uFTerm - b.uFTerm;
	}
	else
	{
		if (opA.uOp == MUL)
			answer.uTerm = a.uTerm * b.uTerm;
		else if (opA.uOp == DIV)
			if (b.uTerm == 0)
				answer.eCode = StatusCodes::DIVISION_BY_ZERO;
			else
				answer.uFTerm = static_cast<double>(a.uTerm) / b.uTerm;
		else if (opA.uOp == ADD)
			answer.uTerm = a.uTerm + b.uTerm;
		else if (opA.uOp == SUB)
			answer.uTerm = a.uTerm - b.uTerm;
	}

	return answer;
}

// Print out any errors
bool catchError(StatusCodes eCode)
{
	
	if (eCode > StatusCodes::VALID)
	{
		std::cerr << "error: ";
		std::cerr << defaultValue::errorString[static_cast<int>(eCode)] << "\n\n";
		return true;
	}

	return false;
}

void answerString(std::string uString)
{
	mterm_t termA{ getTerms(uString, stringPositions::start) };
	if (catchError(termA.eCode))
		return;

	mop_t opA{ getOperator(uString, termA.ePos) };
	if (catchError(opA.eCode))
		return;

	mterm_t termB{ getTerms(uString, ++opA.ePos) };
	if (catchError(termB.eCode))
		return;

	mterm_t answer{ evaluateEquation(termA, termB, opA) };
	if (catchError(answer.eCode))
		return;

	if (opA.uOp == DIV || termA.eCode < StatusCodes::VALID 
		|| termB.eCode < StatusCodes::VALID)
		std::cout << "= " << answer.uFTerm << "\n\n";
	else
		std::cout << "= " << answer.uTerm << "\n\n";
}