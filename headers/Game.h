#pragma once
#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "Abilities.h"
#include "AbilityMananger.h"
#include "Exceptions.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <tuple>

#include "State.h"
#include "Input.h"
#include "OutputManager.hpp"
#include "Output.hpp"
#include "OutputConsole.hpp"
#include "InteractionWithFile.h"


class Game {
private:
    GameState state;
    OutputManager<Output>* outputManager;
    Input* input;


public:
    Game(Input* input) : input(input)
    {
        Output output = Output();
        outputManager = new OutputManager<Output>(output);
        state = GameState(5, 5, { 1, 1, 2, 3 });
        state.getUserAbilities().SetInput(input);
    }

    ~Game();

    bool FindCoordinates();

    void SetFieldComputer();

    void SetFieldUser();

    void useAbility();

    void TurnUser();

    void TurnComp();

    void load();


    void save();

    bool checkEnd();

    void endGame();

    void Round();

    void beginGame();


};
