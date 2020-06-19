#ifndef STRING_TRANSLATE_H
#define STRING_TRANSLATE_H
#include "constants.h"
#include "usertypes.h"

#include <string>

std::string removeJunkCharacters(std::string uString, std::size_t sPos);

bool checkListWNum(std::string uString, size_t cPos, const char sChars[]);

bool checkList(std::string uString, size_t cPos, const char sChars[]);

mTerm_t stringToTerm(std::string uString, std::size_t pA, std::size_t pB, bool dec);

mTerm_t getTerms(std::string uString, std::size_t sPos);

mOp_t getOperator(std::string uString, std::size_t termAEnd);

mTerm_t evaluateEquation(mTerm_t a, mTerm_t b, mOp_t opA);

bool catchError(sCode_t eCode);

bool catchError(sCode_t eCodeVals[]);

void answerString(std::string uString);

#endif