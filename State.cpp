
#include <vector>
#include <iostream>
#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "Abilities.h"
#include "AbilityMananger.h"
#include "Exceptions.h"
#include "json.hpp"
#include <fstream>
#include <string>
#include "Input.h"
#include "State.h"


int GameState::getCurrentRound() const { return currentRound; }

// Конструктор
GameState::GameState()
    : col(2),
    row(2),
    sizes({1}),
    userScore(sizes.size()),
    computerScore(sizes.size()),
    currentRound(0),
    compGameField(col, row),
    userGameField(col, row),
    compShipManager(sizes.size(), sizes),
    userShipManager(sizes.size(), sizes)
{}

// Конструктор
GameState::GameState(int col, int row, const std::vector<int>& sizes)
    : col(col),
    row(row),
    sizes(sizes),
    userScore(sizes.size()),
    computerScore(sizes.size()),
    currentRound(0),
    compGameField(col, row),
    userGameField(col, row),
    compShipManager(sizes.size(), sizes),
    userShipManager(sizes.size(), sizes)
{}

GameState::GameState(const GameState& other)
    : currentRound(other.currentRound)
    , col(other.col)
    , row(other.row)
    , sizes(other.sizes)
    , computerScore(other.computerScore)
    , userScore(other.userScore)
    , compShipManager(other.compShipManager)
    , userShipManager(other.userShipManager)
    , compGameField(other.compGameField)
    , userGameField(other.userGameField)

{
    int sizeAbilities = other.userAbilities.GetSize();
    while (sizeAbilities > 3) {
        userAbilities.getRandomAbility();
        sizeAbilities -= 1;
    }
    while (sizeAbilities < 3) {
        userAbilities.removeAbility();
        sizeAbilities += 1;
    }
}

GameState& GameState::operator=(const GameState& other) {
    if (this != &other) {
        currentRound = other.currentRound;
        col = other.col;
        row = other.row;
        sizes = other.sizes;
        computerScore = other.computerScore;
        userScore = other.userScore;
        compShipManager = other.compShipManager;
        userShipManager = other.userShipManager;
        compGameField = other.compGameField;
        userGameField = other.userGameField;
    }
    int sizeAbilities = other.userAbilities.GetSize();
    while (sizeAbilities > 3) {
        userAbilities.getRandomAbility();
        sizeAbilities -= 1;
    }
    while (sizeAbilities < 3) {
        userAbilities.removeAbility();
        sizeAbilities += 1;
    }
    return *this;
}

GameState& GameState::operator=(GameState&& other) noexcept {
    if (this != &other) {
        currentRound = other.currentRound;
        col = other.col;
        row = other.row;
        sizes = std::move(other.sizes);
        computerScore = other.computerScore;
        userScore = other.userScore;
        compShipManager = std::move(other.compShipManager);
        userShipManager = std::move(other.userShipManager);
        compGameField = std::move(other.compGameField);
        userGameField = std::move(other.userGameField);
        userAbilities = std::move(other.userAbilities);
    }
    return *this;
}

nlohmann::json GameState::to_json() const {
    nlohmann::json j;
    j["currentRound"] = currentRound;
    j["col"] = col;
    j["row"] = row;
    j["sizes"] = sizes;
    j["computerScore"] = computerScore;
    j["userScore"] = userScore;
    j["compShipManager"] = compShipManager.to_json();
    j["userShipManager"] = userShipManager.to_json();
    j["compGameField"] = compGameField.to_json();
    j["userGameField"] = userGameField.to_json();
    j["Abilities"] = userAbilities.GetSize();
    return j;
}


void GameState::setCurrentRound(int currentRound) { this->currentRound = currentRound; }

int GameState::getCol() const { return col; }
void GameState::setCol(int col) { this->col = col; }

int GameState::getRow() const { return row; }
void GameState::setRow(int row) { this->row = row; }

std::vector<int> GameState::getSizes() const { return sizes; }
void GameState::setSizes(std::vector<int> sizes) { this->sizes = sizes; }

int GameState::getComputerScore() const { return computerScore; }
void GameState::setComputerScore(int computerScore) { this->computerScore = computerScore; }

int GameState::getUserScore() const { return userScore; }
void GameState::setUserScore(int userScore) { this->userScore = userScore; }


GameField& GameState::getCompGameField() { return compGameField; }
ShipManager& GameState::getCompShipManager() { return compShipManager; }

AbilityManager& GameState::getUserAbilities() { return userAbilities; }
ShipManager& GameState::getUserShipManager() { return userShipManager; }
GameField& GameState::getUserGameField() { return userGameField; }


void GameState::resetCompField() {
    // Пересоздание поля и менеджера кораблей
    compGameField = GameField(col, row);
    compShipManager = ShipManager(sizes.size(), sizes);
}

GameState GameState::from_json(const nlohmann::json& j) {
    GameState state(j["col"].get<int>(), j["row"].get<int>(), j["sizes"].get<std::vector<int>>());
    state.currentRound = j["currentRound"];
    state.computerScore = j["computerScore"];
    state.userScore = j["userScore"];
    state.compShipManager = ShipManager::from_json(j["compShipManager"]);
    state.userShipManager = ShipManager::from_json(j["userShipManager"]);
    state.compGameField = GameField::from_json(j["compGameField"]);
    state.userGameField = GameField::from_json(j["userGameField"]);
    //state.compGameField.restoreConnection(state.compShipManager);
    //state.userGameField.restoreConnection(state.userShipManager);

    int sizeAbilities = j["Abilities"].get<int>();
    while (sizeAbilities > 3) {
        state.userAbilities.getRandomAbility();
        sizeAbilities -= 1;
    }
    while (sizeAbilities < 3) {
        state.userAbilities.removeAbility();
        sizeAbilities += 1;
    }


    return state;
}