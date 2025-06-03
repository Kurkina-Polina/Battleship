#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "Field.h"
#include "OutputConsole.hpp"
#include "AbilityStatus.h"



class Output
{
public:
    Output() = default;
    std::string abilityStatusToString(AbilityStatus status);
    void printString(std::string msg);
    void printAbilityResult(AbilityStatus abilityStatus);
    void printError(std::string msg);

    void printPlayerField(GameField gameField);
    void printEnemyField(GameField gameField);

private:
    OutputConsole *outputConsole;
};

#endif
