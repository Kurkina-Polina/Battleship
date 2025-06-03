#pragma once
#include <vector>
#include <iostream>
#include "Ship.h"
#include "ShipManager.h"
class AbilityManager; 


#include "json.hpp"

enum class CellStatus {
    Unknown,
    Empty,
    Ship
};

class Cell {
private:
    CellStatus status = CellStatus::Unknown;
    ShipSegment* shipSegment = nullptr;
    int IndexSegment=-1, IndexShip=-1;
public:
    void SetStatus(CellStatus stutus);
    void SetShipSegment(ShipSegment* shipsegment);
    void SetIndexes(int indSeg, int indShip);
    CellStatus GetStatus();
    ShipSegment* GetShipSegment();
    int GetIndSeg();
    int GetIndShip();

    nlohmann::json to_json() const;

    static Cell from_json(const nlohmann::json& j);

};




class GameField {
private:
    int row;
    int col;
    std::vector<std::vector<Cell>> Field;
    
    void SetCellStatus(int x, int y, CellStatus status);
    void SetShipSegment(int x, int y, ShipSegment* segment);

public:
    GameField(int col, int row);

    CellStatus GetStatus(int x, int y);

    SegmentState GetSegmentState(int x, int y);
    int GetRow();
    int GetCol();

    bool ValidCoordinaties(int x, int y);
    bool IsValidLocation(int x, int y, int len, Orientation orientation);

    GameField(const GameField& other);
    GameField(GameField&& other) noexcept;
    GameField& operator=(const GameField& other);
    GameField& operator=(GameField&& other) noexcept;

    bool AddShip(int x, int y, Ship& ship, int IndexShip);

    int Hit(int x, int y, bool FlagHit);

    void PrintField();

    void PrintFieldComputer();

    nlohmann::json to_json() const;

    static GameField from_json(const nlohmann::json& j);

    void restoreConnection(ShipManager& manager);

};

