#ifndef STRING_TRANSLATE_H
#define STRING_TRANSLATE_H
#include "constants.h"
#include "mathtypes.h"

#include <string>

bool checkListWNum(std::string uString, size_t cPos, const char sChars[], int len);

bool checkList(std::string uString, size_t cPos, const char sChars[], int len);

std::string removeJunkCharacters(std::string uString, std::size_t sPos);

mTerm_t stringToTerm(std::string uString, std::size_t pA, std::size_t pB);

mTerm_t getTerms(std::string uString, std::size_t sPos);

mOp_t getOperator(std::string uString, std::size_t termAEnd);

#endif