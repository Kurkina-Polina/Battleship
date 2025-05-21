#include <iostream>
#include <limits>
#include <sstream>

#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "Abilities.h"
#include "AbilityMananger.h"
#include "Exceptions.h"
#include "Game.h"
#include "GameController.hpp"

int main()
{
    srand(time(0));

    Input* input = new Input(std::cin);
    Game game(input);
    GameController<Input> gameController{ input, game };

    return 0;
}