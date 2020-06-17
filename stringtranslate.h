#ifndef STRING_TRANSLATE_H
#define STRING_TRANSLATE_H
#include "constants.h"
#include "usertypes.h"

#include <string>

std::string removeJunkCharacters(std::string uString, std::size_t sPos);

bool checkListWNum(std::string uString, size_t cPos, const char sChars[]);

bool checkList(std::string uString, size_t cPos, const char sChars[]);

mterm_t getTerms(std::string uString, std::size_t sPos);

mop_t getOperator(std::string uString, std::size_t termAEnd);

mterm_t evaluateEquation(mterm_t a, mterm_t b, mop_t opA);

bool catchError(StatusCodes eCode);

void answerString(std::string uString);

#endif