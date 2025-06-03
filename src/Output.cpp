#include "Output.hpp"

std::string Output::abilityStatusToString(AbilityStatus status) {
    switch (status) {
    case AbilityStatus::SUCCESS:
        return "SUCCESS";
    case AbilityStatus::DESTROYED:
        return "DESTROYED";
    case AbilityStatus::EMPTY:
        return "EMPTY";
    case AbilityStatus::NOT_DESTROYED:
        return "NOT_DESTROYED";
    case AbilityStatus::SHIP:
        return "SHIP";
    default:
        return "Unknown Status";
    }
}

void Output::printString(std::string msg)
{
    std::cout << msg;
}

void Output::printAbilityResult(AbilityStatus abilityStatus)
{
    std::cout << "Using ability result: " << abilityStatusToString(abilityStatus) << std::endl;
}

void Output::printError(std::string msg)
{
    std::cerr << msg << '\n';
}

void Output::printPlayerField(GameField gameField)
{
    outputConsole->printField(gameField, OutputStatus::OPENED);
}

void Output::printEnemyField(GameField gameField)
{
    outputConsole->printField(gameField, OutputStatus::HIDDEN);
}