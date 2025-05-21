#pragma once
#include <vector>
#include <iostream>
#include "Ship.h"
#include "ShipManager.h"
class AbilityManager; //предварительное объявление чтобы мы могли добавить способность в hit


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

    

    //// Метод сериализации
    nlohmann::json to_json() const;

    //// Метод десериализации
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

    // дать статус клетки
    CellStatus GetStatus(int x, int y);

    //дфть статус сегмента в клетке
    SegmentState GetSegmentState(int x, int y);

    // дать длину
    int GetRow();

    // дать ширину
    int GetCol();

    //проверка что такие координаты существуют
    bool ValidCoordinaties(int x, int y);
    //проверка что в этой локации корабль не пересекает
    bool IsValidLocation(int x, int y, int len, Orientation orientation);

    //конструктор копирования
    GameField(const GameField& other);

    //конструктор перемещения
    GameField(GameField&& other) noexcept;

    //оператор присваивания копированием
    GameField& operator=(const GameField& other);

    // оператор присваивания перемещением
    GameField& operator=(GameField&& other) noexcept;

    

    //добавить корабль на поле
    bool AddShip(int x, int y, Ship& ship, int IndexShip);

    //атака клетки
    int Hit(int x, int y, bool FlagHit);

    //нарисовать поле
    void PrintField();

    void PrintFieldComputer();

    nlohmann::json to_json() const;

    static GameField from_json(const nlohmann::json& j);

    void restoreConnection(ShipManager& manager);

};

