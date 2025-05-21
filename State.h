#pragma once

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
//
// ����������� ����� ��������� ����, � �������������� ��������� ����� � ������ � ����� ��� ��������� ����. ����������� ���������� � �������� ����. 
// ����������� � ����������� ����� � ����� ������, ����� � ������������ ��������� � ����.
//  ������ ���� ����������� ��������� ���������� ����� ����������� ���� ���������.
//


class GameState {
private:
    int currentRound = 0;
    int col, row;
    std::vector<int> sizes;// ������� ��������

    int computerScore; // ���-�� ����� ��������
    int userScore;// ���-�� ����� ��������

    ShipManager compShipManager;// ������� ����������
    ShipManager userShipManager;// ������� ������������

    GameField compGameField;// ������� ���� ����������
    GameField userGameField;// ������� ���� ������������

    AbilityManager userAbilities; // ����������� ������������

public:
    // �����������
    GameState(int col, int row, const std::vector<int>& sizes);
    GameState();
    GameState(const GameState& other);
    GameState& operator=(const GameState& other);

    GameState& operator=(GameState&& other) noexcept;

    // ������� � �������
    int getCurrentRound() const;
    void setCurrentRound(int currentRound);

    int getCol() const;
    void setCol(int col);

    int getRow() const;
    void setRow(int row);

    std::vector<int> getSizes() const;
    void setSizes(std::vector<int> sizes);

    int getComputerScore() const;
    void setComputerScore(int computerScore);

    int getUserScore() const;
    void setUserScore(int userScore);

    
    GameField& getCompGameField();
    ShipManager& getCompShipManager();

    AbilityManager& getUserAbilities();
    ShipManager& getUserShipManager();
    GameField& getUserGameField();


    void resetCompField();
    
    nlohmann::json to_json() const;

    static GameState from_json(const nlohmann::json& j);

    // �������� ������ � �����
    friend std::ostream& operator<<(std::ostream& os, const GameState& state) {
        os << state.to_json().dump(4);
        return os;
    }

    // �������� ���������� �� ������
    friend std::istream& operator>>(std::istream& is, GameState& state) {
        nlohmann::json j;
        is >> j;  // ��������� JSON �� ������
        state = from_json(j);  // ����������� JSON � ������ GameState
        return is;
    }

    //// ������� ��� ���������� GameState � ����
    //static bool Saving(const GameState& state) {
    //    const std::string filename = "save.json";
    //    std::ofstream outFile(filename);

    //    // ���������, ������� �� ������� ����
    //    if (!outFile) {
    //        throw GameException("Error saving: ");

    //    }

    //    // ���������� GameState � ����
    //    outFile << state;

    //    // ��������� ����
    //    outFile.close();

    //    // ���������, ��� ���� ��� ������� �������
    //    std::ifstream inFile(filename);
    //    if (inFile) {
    //        inFile.close();
    //        return true;
    //    }
    //    else {
    //        throw GameException("Error saving: ");
    //    }
    //}

    // ������� ��� �������� GameState �� �����
    //static GameState& Loading(GameState& state) {
    //    const std::string filename = "save.json";
    //    std::ifstream inFile(filename);

    //    // ���������, ������� �� ������� ����
    //    if (!inFile) {
    //        throw GameException("Error loading: File not found.");
    //    }
    //    
    //    // ��������� GameState �� �����
    //    inFile >> state;

    //    // ��������� ����
    //    inFile.close();
    //    
    //    state.compGameField.restoreConnection(state.compShipManager);
    //    state.userGameField.restoreConnection(state.userShipManager);

    //    //state.getCompGameField().PrintField();
    //    return state;
    //}
    //
};