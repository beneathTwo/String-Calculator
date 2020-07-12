#ifndef MATH_CALCULATOR_H
#define MATH_CALCULATOR_H

#include "mathtypes.h"

void evaluateEquation(mTerm_t a, mTerm_t b, mOp_t opA);

void answerString(std::string uString);

void printError(sCode_t eCode);

#endif
