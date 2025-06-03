#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Game.h"

template <typename InputMethod>
class GameController
{
public:
    GameController(InputMethod *inputMethod, Game &game) : game(game), inputMethod(inputMethod)
    {
        inputMethod->loadCommandsFromJson();
        inputCommand();
    }

    void inputCommand()
    {
        bool flag = false;
        while (!flag)
        {
            Commands command = inputMethod->inputCommand();
            processCommand(command);
            if (command == END)
            {
                flag = true;
            }
        }
    }

    void processCommand(Commands command)
    {
        switch (command)
        {
        case START_GAME:
            game.beginGame();
            break;
        case SAVE_GAME:
            game.save();
            break;
        case LOAD_GAME:
            game.load();
            break;
        case END:
            game.endGame();
            break;
        case ATTACK:
            game.TurnUser();
            break;
        case USE_ABILITY:
            game.useAbility();
            break;
        }
    }

private:
    Game &game;
    InputMethod *inputMethod;
};

#endif