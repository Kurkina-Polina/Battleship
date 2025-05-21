#include "Input.h"
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

#include "Output.hpp"
#include "Exceptions.h"
#include "json.hpp"

int Input::inputNumber()
{
    int x;
    std::string inputString;
    bool inputFlag = false;
    while (!inputFlag)
    {
        try
        {
            std::getline(inputStream, inputString);
            std::stringstream ss(inputString);
            if (!(ss >> x) || ss.fail() || !ss.eof())
            {
                throw InputError("Incorrect data, enter it again!");
            }
            inputFlag = true;
        }
        catch (InputError &e)
        {
            output.printError(e.what());
        }
    }
    return x;
}

std::vector<int> Input::inputCoordinates()
{
    int x, y;
    std::string inputString;
    bool inputFlag = false;
    while (!inputFlag)
    {
        try
        {
            std::getline(inputStream, inputString);
            std::stringstream ss(inputString);
            if (!(ss >> x >> y) || ss.fail() || !ss.eof())
            {
                throw InputError("Incorrect data, enter it again!");
            }
            inputFlag = true;
        }
        catch (InputError &e)
        {
            output.printError(e.what());
        }
    }
    std::vector<int> coordinates = {x, y};
    return coordinates;
}

std::string Input::inputString()
{
    std::string s;
    std::string inputString;
    bool inputFlag = false;
    while (!inputFlag)
    {
        try
        {
            std::getline(inputStream, inputString);
            std::stringstream ss(inputString);
            if (!(ss >> s) || ss.fail() || !ss.eof())
            {
                throw InputError("Incorrect data, enter it again!");
            }
            inputFlag = true;
        }
        catch (InputError &e)
        {
            output.printError(e.what());
        }
    }
    return s;
}

Commands Input::inputCommand()
{
    std::string command;
    bool flag = false;
    while (!flag)
    {
        output.printString("Enter the command: ");
        command = inputString();
        if (command.empty())
        {
            output.printError("Command cannot be empty.");
            continue;
        }
        auto it = commands.find(command[0]);
        if (it != commands.end())
        {
            flag = true;
            return it->second;
        }
        else
        {
            output.printError("The wrong command.");
        }
    }
    auto it = commands.find('a');
    return it->second;
    
}

void Input::checkCommands()
{
    std::vector<char> assigned_keys;
    std::vector<Commands> assigned_commands;
    for (const auto &pair : commands)
    {
        char key = pair.first;
        Commands command = pair.second;

        if (std::find(assigned_keys.begin(), assigned_keys.end(), key) != assigned_keys.end())
        {
            throw FileError("Duplicate keys in the list of commands.");
        }
        assigned_keys.push_back(key);

        if (std::find(assigned_commands.begin(), assigned_commands.end(), command) != assigned_commands.end())
        {
            throw FileError("Duplicate commands in the list of commands.");
        }
        assigned_commands.push_back(command);
    }
}

void Input::loadCommandsFromJson()
{
    int count_commands = 0;
    std::ifstream file("commands.json");
    if (!file) {
        output.printError("The command file cannot be opened.");
        commands = shortCommands;
        return;

    }

    nlohmann::json j;
    try
    {
        //std::string jsonContent((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());

        //j = nlohmann::json::parse(jsonContent); // Парсим JSON из файла
        nlohmann::json j;
        file >> j;
        commands.clear();
        for (auto it = j.begin(); it != j.end(); ++it)
        {
            const std::string &key = it.key();
            const std::string &value = it.value();

            count_commands++;
            auto cmd_it = stringCommands.find(value);
            if (cmd_it != stringCommands.end())
            {
                commands[key[0]] = cmd_it->second;
            }
            else
            {
                std::cout << value << std::endl;
                throw FileError("Invalid command in json.");
            }
        }

        if (count_commands != 6)
        {
            throw FileError("Incorrect number of commands in json.");
        }

        checkCommands();
    }
    catch (const FileError &e)
    {
        output.printError(e.what());
        commands = shortCommands;
    }
}
