#include "constants.h"
#include "stringtranslate.h"
#include "mathtypes.h"

#include <cctype>
#include <iostream>
#include <string>

using std::size_t;

// These just run through a list of characters if one is the same to the input.
bool checkListWNum(std::string uString, size_t pPos, const char sChars[])
{
	for (int countChar{}; countChar < sizeof(sChars); ++countChar)
		if (uString.at(pPos) == sChars[countChar])
			return true;

	return false;
}

bool checkList(std::string uString, size_t pPos, const char sChars[])
{
	for (int countChar{}; countChar < sizeof(sChars); ++countChar)
		if (uString.at(pPos) == sChars[countChar] || std::isdigit(uString.at(pPos)))
			return true;

	return false;
}

//	Characters that have no signification to the operation are skipped over and deleted.
std::string removeJunkCharacters(std::string uString, size_t sPos)
{
	// Not a digit or char in the list, then continue to scan for the wanted chars.
	// If it comes up on a negative sign It'll check for a number infront of it.
	// If a missing term is detected the string is cleared to throw an invalid input.
	char listT[]{ '-', '.' };
	size_t pPos{ sPos };
	for (pPos; pPos < uString.size() && !std::isdigit(uString.at(pPos))
		&& !(checkListWNum(uString, pPos, listT) 
		&& std::isdigit(uString.at(pPos + 1))); ++pPos)
		if (checkListWNum(uString, pPos, presets::listO))
			return uString.erase(sPos, uString.size());
			
	return uString.erase(sPos, pPos);
}

mTerm_t stringToTerm(std::string uString, size_t posA, size_t posB)
{
	mTerm_t gotTerm{};
	gotTerm.ePos = posB;
	gotTerm.uTerm = std::stod(uString.substr(posA, posB));

	return gotTerm;
}

mTerm_t getTerms(std::string uString, size_t sPos)
{
	// Clean up unnecessary data based on the starting pos.
	if (sPos > stringPositions::start)
	{
		uString.erase(stringPositions::start, sPos);
		sPos = stringPositions::start;
		uString = removeJunkCharacters(uString, sPos);
	}
	else
		uString = removeJunkCharacters(uString, sPos);

	if (uString.size() == stringSize::empty)
		throw sCode_t::INVALID_INPUT;

	// Grab the term from the string.
	char listT[]{ '-', '.' };
	size_t pPos{};
	for (int decCount{}; pPos < uString.size() && checkList(uString, pPos, listT); ++pPos)
	{
		if (uString.at(pPos) == '-' && pPos != stringPositions::start 
			|| decCount > 1)
			break;

		(uString.at(pPos) == '.') ? ++decCount : decCount;
	}

	return stringToTerm(uString, sPos, pPos);
}

mOp_t getOperator(std::string uString, size_t termAEnd)
{
	// Delete what's before so the wrong operation isn't grabbed.
	uString.erase(stringPositions::start, termAEnd);

	// Go through the list of operations until the operation is found.
	using presets::listO;
	for (size_t checkChar{}; checkChar < sizeof(listO); ++checkChar)
		if (uString.find(listO[checkChar]) != std::string::npos)
		{
			mOp_t opA{};
			opA.ePos = uString.find(listO[checkChar]) + termAEnd;
			opA.uOp = listO[checkChar];
			return opA;
		}

	throw sCode_t::INVALID_OPERATION;
}