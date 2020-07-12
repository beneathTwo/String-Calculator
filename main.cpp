#include "mathcalculator.h"

#include <iostream>
#include <string>

std::string userInput()
{
    std::string uString{};
    std::getline(std::cin, uString);
    return uString;
}

int main()
{
    std::cout << "Welcome to Calculator 1.0\n";
    std::cout << "Supports +, -, *, /, to close program type \"exit\"\n\n";

    while (true)
    {
        std::string uString{ userInput() };

        if (uString == "exit" || uString == "Exit")
            break;

        answerString(uString);
    }

    return 0;
}