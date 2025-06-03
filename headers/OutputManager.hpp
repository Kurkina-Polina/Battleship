#ifndef OUTPUT_MANAGER_HPP
#define OUTPUT_MANAGER_HPP

#include "Output.hpp"

template <typename OutputMethod>
class OutputManager
{
public:
    OutputManager(OutputMethod output) : output(output) {}

    void printString(std::string msg)
    {
        output.printString(msg);
    }

    void printAbilityResult(AbilityStatus abilityStatus)
    {
        output.printAbilityResult(abilityStatus);
    }

    void printError(std::string msg)
    {
        output.printError(msg);
    }

    void printPlayerField(GameField field)
    {
        output.printPlayerField(field);
    }

    void printEnemyField(GameField field)
    {
        output.printEnemyField(field);
    }

private:
    OutputMethod output;
};

#endif
