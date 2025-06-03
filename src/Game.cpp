#include "Game.h"


Game::~Game()
{
    delete outputManager;
}

bool Game::FindCoordinates() {
    int col = state.getCol();
    int row = state.getRow();

    srand(time(0)); 
    for (int i = 0; i < state.getSizes().size(); i++) { // it should be func FindCoordinates()

        int rNum = rand();

        int x = rNum % col, y = (rNum + rNum) % row, x_cur = x, y_cur = y;

        bool FLadAddedShip = false;
        while (FLadAddedShip == false) { 
            try
            {
                FLadAddedShip = state.getCompGameField().AddShip(x_cur, y_cur, state.getCompShipManager().GetShip(i), i);

            }
            catch (const std::exception&)
            {
                if (x_cur + 1 < col) {
                    x_cur += 1;
                }
                else if (y_cur + 1 < row) {
                    y_cur += 1;
                    x_cur = 0;
                }
                else {
                    x_cur = 0;
                    y_cur = 0;
                }
                if ((x_cur == x) && (y_cur == y)) {

                    return false;
                    
                }

            }
        }
        
    }
    return true;
}

void Game::SetFieldComputer() { 

    while (FindCoordinates() == false) {
        state.resetCompField();
    }
    state.setComputerScore(state.getSizes().size());
}

void Game::SetFieldUser() {
    int countShips = state.getSizes().size();
    for (int i = 0; i < countShips; i++) {

        outputManager->printString("Enter coordinates to  add ship (x y): ");
        std::vector<int> coordinates = input->inputCoordinates();
        bool FLadAddedShip = false; 
        while (!FLadAddedShip) {
            try
            {
                FLadAddedShip = state.getUserGameField().AddShip(coordinates[0], coordinates[1], state.getUserShipManager().GetShip(i), i);
                break;
            }
            catch (const std::exception& e)
            {
                outputManager->printString("There is a problem: " + std::string(e.what()));
                outputManager->printString("Enter coordinates to  add ship (x y): ");
                coordinates = input->inputCoordinates();
            }

        }
        outputManager->printPlayerField(state.getUserGameField());
    }
}

void Game::useAbility()
{
    
    try
    {
        bool isDestroyed;
        AbilityStatus newAbilityStatus;
        std::tie(isDestroyed, newAbilityStatus) = state.getUserAbilities().applyAbility(state.getCompGameField(), state.getCompShipManager());
        
        outputManager->printAbilityResult(newAbilityStatus);
        if (isDestroyed)
        {
            outputManager->printString("You have received a new ability!\n");
            state.getUserAbilities().getRandomAbility();
            state.setComputerScore(state.getComputerScore() - 1);
        }
    }
    catch (const std::exception& e)
    {
        outputManager->printError(std::string(e.what()) + "Try again");
        return;
    }

    outputManager->printString("Enemy field after your attack: \n");
    outputManager->printEnemyField(state.getCompGameField());
    checkEnd();
    TurnUser(); 

}

void Game::TurnUser() {
    int indShip;
    outputManager->printString("Enter coordinates to attack (x y): ");
    std::vector<int> coordinates = input->inputCoordinates();
    bool flagHit = true;
    while (flagHit) {
        try
        {
            indShip = state.getCompGameField().Hit(coordinates[0], coordinates[1], state.getUserAbilities().GetFlag());
            flagHit = false;
            break;
        }
        catch (const std::exception& e)
        {
            outputManager->printString("There is a problem: " + std::string(e.what()));
            outputManager->printString("Enter coordinates to  hit (x y): ");
            coordinates = input->inputCoordinates();
        }
    }

    if ((indShip >= 0) && (state.getCompShipManager().GetShip(indShip).IsDestroid())) {
        outputManager->printString("New ability!");
        state.getUserAbilities().getRandomAbility();
        state.setComputerScore(state.getComputerScore() - 1);
    }
    outputManager->printString("Enemy field after your attack: \n");
    outputManager->printEnemyField(state.getCompGameField());
    bool flag_comTurn = checkEnd();
    if (!flag_comTurn) {
        TurnComp();
    }

}

void Game::TurnComp() {
    int row = state.getRow();
    int col = state.getCol();
   
    srand(time(0)); 
    int randomNum = rand();
    int X = randomNum % col, Y = randomNum * randomNum % row;
    int indShip = -1;
    
    bool flag_hit = false;
    while (!flag_hit) {
        try
        {
            if ((state.getUserGameField().GetStatus(X, Y) == CellStatus::Ship) && (state.getUserGameField().GetSegmentState(X, Y) == SegmentState::Destroyed)) {
                throw EmptyCell(X, Y);
            }
            indShip = state.getUserGameField().Hit(X, Y, false);
            flag_hit = true;
            break;
        }
        catch (const std::exception& e)
        {
            X = (X + 1);
            if (X >= col) {
                X = 0;
                Y = (Y + 1) % row;
            }
            else if ((X >= col) && (Y >= row)) {
                X = 0;
                Y = 0;
            }

        }

    }
    std::cout << "IndShip= " << indShip << std::endl;
    if ((indShip >= 0) && (state.getCompShipManager().GetShip(indShip).IsDestroid())) {

        state.setUserScore(state.getUserScore() - 1);

    }

    outputManager->printString("Your Field field after comp attack: \n");
    outputManager->printPlayerField(state.getUserGameField());
    checkEnd();
}

void Game::load() {
    try
    {
        InteractionWithFile fileManager("save.json");

        GameState state_new;
        state = fileManager.Loading(state);

        outputManager->printString("The game has been loaded successfully!\n");
        state.getUserAbilities().SetInput(input);
    }
    catch (const std::exception& e)
    {
        outputManager->printError("Failed to load the game: " + std::string(e.what()));
    }

    outputManager->printString("Field of a comp!\n");
    outputManager->printEnemyField(state.getCompGameField());
    outputManager->printString("Your Field\n");
    outputManager->printPlayerField(state.getUserGameField());

}


void Game::save() {
    try
    {
        InteractionWithFile fileManager("save.json");

        if (fileManager.Saving(state)) {
            outputManager->printString("Game state saved successfully \n");
        }
    }
    catch (const std::exception& e)
    {
        outputManager->printError("Failed to save game state to file: " + std::string(e.what()));
    }
}

bool Game::checkEnd()
{
    bool flag_Round_newGame = false;
    
    if (state.getComputerScore() == 0)
    {
        outputManager->printString("Congratulations, you won this round! Starting the next round...\n");
        flag_Round_newGame = true;
        Round();
    }
    else if (state.getUserScore() == 0)
    {
        outputManager->printString("You lost the game. Would you like to start a new game? (y/n): ");
        std::string choice = input->inputString();
        flag_Round_newGame = true;
        if (choice == "y" || choice == "Y")
        {
            beginGame();
        }
        else
        {
            endGame();
        }
    }
    return flag_Round_newGame;
}

void Game::endGame()
{
    outputManager->printString("Exiting the game. Thank you for playing!\n");
    exit(1);
}

void Game::Round() {
    outputManager->printString("Starting a new round!\n");
    SetFieldComputer();

}

void Game::beginGame() {
    outputManager->printString("Do you want to download the previous game? (y/n): ");
    std::string choice = input->inputString();
    if (choice == "y" || choice == "Y")
    {
        try
        {
            load();

        }
        catch (const std::exception& e)
        {
            std::cout << "Failed to load game state to file " << e.what() << std::endl;
        }

    }
    else
    {
        outputManager->printString("Starting a new game!\n");

        outputManager->printString("Type coloumns and rows\n");
        std::vector<int> sizeOfField = input->inputCoordinates(); 

        outputManager->printString("Type Count of Ships\n");
        int countShips = input->inputNumber(); 

        std::vector<int> sizeOfShips;
        for (int i = 0; i < countShips; i++) {
            outputManager->printString("Type size of Ship \n");
            sizeOfShips.push_back(input->inputNumber()); 
        }


        state = GameState(sizeOfField[0], sizeOfField[1], sizeOfShips);

        SetFieldUser();
        Round();
    }

}
