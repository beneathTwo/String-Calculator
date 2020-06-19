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

mTerm_t stringToTerm(std::string uString, std::size_t pA, std::size_t pB, bool dec)
{
	mTerm_t gTerm{};
	gTerm.ePos = pB;
	if (dec)
	{
		gTerm.uFTerm = std::stod(uString.substr(pA, pB));
		gTerm.eCode = sCode_t::CHANGE_TYPE;
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
			gTerm.eCode = sCode_t::CHANGE_TYPE;
		}
	}

	return gTerm;
}

mTerm_t getTerms(std::string uString, std::size_t sPos)
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
		mTerm_t gTerm{ 0, stringPositions::start, sCode_t::INVALID_INPUT };
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

mOp_t getOperator(std::string uString, std::size_t termAEnd)
{
	// Delete what's before so the wrong operation isn't grabbed.
	uString.erase(stringPositions::start, termAEnd);

	// Go through the list until the operation is found.
	using defaultValue::listO;
	mOp_t opA{};
	for (std::size_t checkChar{}; checkChar < sizeof(listO); ++checkChar)
		if (uString.find(listO[checkChar]) != std::string::npos)
		{
			opA.ePos = uString.find(listO[checkChar]) + termAEnd;
			opA.uOp = listO[checkChar];
			return opA;
		}

	opA.eCode = sCode_t::INVALID_OPERATION;
	return opA;
}

mTerm_t evaluateEquation(mTerm_t a, mTerm_t b, mOp_t opA) 
{
	mTerm_t answer{};
	if (a.eCode < sCode_t::VALID || b.eCode < sCode_t::VALID)
	{
		if (!(a.eCode < sCode_t::VALID))
			a.uFTerm = static_cast<double>(a.uTerm);
		if (!(b.eCode < sCode_t::VALID))
			b.uFTerm = static_cast<double>(b.uTerm);

		if (opA.uOp == MUL)
			answer.uFTerm = a.uFTerm * b.uFTerm;
		else if (opA.uOp == DIV)
			if (b.uFTerm == 0)
				answer.eCode = sCode_t::DIVISION_BY_ZERO;
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
				answer.eCode = sCode_t::DIVISION_BY_ZERO;
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
bool catchError(sCode_t eCode)
{
	if (eCode > sCode_t::VALID)
	{
		std::cerr << "error: ";
		std::cerr << defaultValue::errorString[static_cast<int>(eCode)] << "\n\n";
		return true;
	}

	return false;
}


bool catchError(sCode_t eCodeVals[])
{
	int eCodeN{};
	for (eCodeN; eCodeN < sizeof(eCodeVals); ++eCodeN)
		if (eCodeVals[eCodeN] > sCode_t::VALID)
		{
			std::cerr << "error: ";
			std::cerr << defaultValue::errorString[static_cast<int>(eCodeVals[eCodeN])];
			std::cerr << "\n\n";
			return true;
		}

	return false;
}

void answerString(std::string uString)
{
	mTerm_t termA{ getTerms(uString, stringPositions::start) };

	mOp_t opA{ getOperator(uString, termA.ePos) };

	mTerm_t termB{ getTerms(uString, ++opA.ePos) };

	sCode_t eList[]{ termA.eCode, opA.eCode, termB.eCode };
	if (catchError(eList))
		return;

	mTerm_t answer{ evaluateEquation(termA, termB, opA) };
	if (catchError(answer.eCode))
		return;

	if (opA.uOp == DIV || termA.eCode < sCode_t::VALID 
		|| termB.eCode < sCode_t::VALID)
		std::cout << "= " << answer.uFTerm << "\n\n";
	else
		std::cout << "= " << answer.uTerm << "\n\n";
}