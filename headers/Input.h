#ifndef INPUT_HPP
#define INPUT_HPP
#pragma once
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include "Output.hpp"
#include "Exceptions.h"
#include "json.hpp"

enum Commands
{
    START_GAME,
    SAVE_GAME,
    LOAD_GAME,
    END,
    ATTACK,
    USE_ABILITY
};


class Input
{
private:
    Output output;
    std::istream &inputStream;
    std::unordered_map<char, Commands> commands;
    std::unordered_map<char, Commands> shortCommands = {
        {'g', START_GAME},
        {'s', SAVE_GAME},
        {'l', LOAD_GAME},
        {'e', END},
        {'a', ATTACK},
        {'u', USE_ABILITY}};
    std::unordered_map<std::string, Commands> stringCommands = {
        {"game_start", START_GAME},
        {"save", SAVE_GAME},
        {"load", LOAD_GAME},
        {"end", END},
        {"attack", ATTACK},
        {"use_ability", USE_ABILITY}};

public:
    Input(std::istream &inputStream = std::cin) : inputStream(inputStream) {};
    int inputNumber();
    std::vector<int> inputCoordinates();
    std::string inputString();
    Commands inputCommand();
    void checkCommands();        
    void loadCommandsFromJson();
};

#endif