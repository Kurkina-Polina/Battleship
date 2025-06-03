#include <vector>
#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "Exceptions.h"
#include "AbilityMananger.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <tuple>



void Cell::SetStatus(CellStatus status_) { status = status_; }
void Cell::SetShipSegment(ShipSegment* shipsegment_) { shipSegment = shipsegment_; }
void Cell::SetIndexes(int indSeg, int indShip) { IndexSegment = indSeg; IndexShip = indShip; }
int Cell::GetIndSeg() { return IndexSegment; }
int Cell::GetIndShip() { return IndexShip; }
CellStatus Cell::GetStatus() { return status; }
ShipSegment* Cell::GetShipSegment() { return shipSegment; }

nlohmann::json Cell::to_json() const {
    nlohmann::json j;
    switch (status) {
    case CellStatus::Ship: j["status"] = "Ship"; break;
    case CellStatus::Unknown: j["status"] = "Unknown"; break;
    case CellStatus::Empty: j["status"] = "Empty"; break;
    }
    j["IndexSegment"] = IndexSegment;
    j["IndexShip"] = IndexShip;
    return j;
}

Cell Cell::from_json(const nlohmann::json& j) {
    Cell cell;
    std::string statusStr = j["status"].get<std::string>();
    if (statusStr == "Ship") { cell.SetStatus(CellStatus::Ship); }
    else if (statusStr == "Empty") { cell.SetStatus(CellStatus::Empty); }
    else if (statusStr == "Unknown") { cell.SetStatus(CellStatus::Unknown); }
    else { throw std::invalid_argument("Missing or invalid CellStatus in JSON: "); }

    if (!j.contains("IndexSegment") || !j.contains("IndexShip")) { throw std::invalid_argument("Missing or invalid IndexSegment or IndexShip in JSON: "); }

    cell.IndexSegment = j["IndexSegment"].get<int>();
    cell.IndexShip = j["IndexShip"].get<int>();
    return cell;
}


GameField::GameField(int x, int y) :col(x), row(y){
    if (x < 1 || y < 1) {
        throw OutofField(x, y);
    }
    Field.resize(row, std::vector<Cell>(col));
}


void GameField::SetCellStatus(int x, int y, CellStatus status) {
    Field[y][x].SetStatus(status);
}

void  GameField::SetShipSegment(int x, int y, ShipSegment* segment) {
    Field[y][x].SetShipSegment(segment);
}


CellStatus GameField::GetStatus(int x, int y) {
    return Field[y][x].GetStatus();
}

SegmentState GameField::GetSegmentState(int x, int y) {
    ShipSegment* segment = Field[y][x].GetShipSegment();
    return (segment->GetState());
}
 
GameField::GameField(const GameField& other) : row(other.row), col(other.col) {
    Field.resize(row, std::vector<Cell>(col));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            Field[i][j] = other.Field[i][j];
        }
    }
}

GameField::GameField(GameField&& other) noexcept
    : col(other.col), row(other.row), Field(std::move(other.Field)) {
    other.col = 0;
    other.row = 0;
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        col = other.col;
        row = other.row;
        Field.resize(row, std::vector<Cell>(col));
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                Field[i][j] = other.Field[i][j];
            }
        }
    }
    return *this;
}

GameField& GameField::operator=(GameField&& other) noexcept {
    if (this != &other) {
        col = other.col;
        row = other.row;
        Field = std::move(other.Field);
        other.col = 0;
        other.row = 0;
    }
    return *this;
}

bool GameField::ValidCoordinaties(int X, int Y) {
    if (X < 0 || X >= col || Y < 0 || Y >= row) {
        throw OutofField(X, Y);
    }
    return true;
}

bool GameField::IsValidLocation(int x, int y, int len, Orientation orientation) {
    if ((orientation == Orientation::Horizontal) && (x + len > col)) {
        throw ShipOutofbyX(x, y);
    }
    if ((orientation == Orientation::Vertical) && (y + len > row)) {
        throw ShipOutofbyY(x, y);
    }
   
    int min_j = std::max(0, x - 1);
    int min_i = std::max(0, y - 1);
    int max_j = std::min(col - 1, x + ((orientation == Orientation::Horizontal) ? len : 1));
    int max_i = std::min(row - 1, y + ((orientation == Orientation::Vertical) ? len : 1));
    
    for (int i = min_i; i <= max_i; i++) {
        for (int j = min_j; j <= max_j; j++) {
            if (GetStatus(j, i) == CellStatus::Ship) {
                throw IntersectShip(x, y);
            }
        }
    }
    
    return true;
}


int GameField::GetRow() { return col; }

int GameField::GetCol() { return row; }

bool GameField::AddShip(int x, int y, Ship& ship, int IndexShip) {
    int len = ship.GetLength();
    Orientation orientation = ship.GetOrientation();
    ValidCoordinaties(x, y);
    IsValidLocation(x, y, len, orientation);
    for (int i = 0; i < len; i++) {
        int cur_x = x + (orientation == Orientation::Horizontal ? i : 0);
        int cur_y = y + (orientation == Orientation::Vertical ? i : 0);
        SetCellStatus(cur_x, cur_y, CellStatus::Ship);
        SetShipSegment(cur_x, cur_y, ship.GetSegment(i));
        Field[cur_y][cur_x].SetIndexes(i, IndexShip);
    }
    return true;

}

int GameField::Hit(int x, int y, bool FlagHit) {
    ValidCoordinaties(x, y);
    if (GetStatus(x, y) == CellStatus::Empty) {
        throw EmptyCell(x, y);
    }

    if (GetStatus(x, y) == CellStatus::Unknown) {
        SetCellStatus(x, y, CellStatus::Empty);
        return  -1;
    }
    ShipSegment* segment = Field[y][x].GetShipSegment();
    segment->Hit();
    if (FlagHit) { 
        segment->Hit();
    }

    int index = Field[y][x].GetIndShip();
    return index;

}

void GameField::PrintField() {
    for (int y = 0; y < row; y++) {
        for (int x = 0; x < col; x++) {
            if (Field[y][x].GetStatus() == CellStatus::Empty) {
                std::cout << "X";
            }
            else if (Field[y][x].GetStatus() == CellStatus::Unknown) {
                std::cout << "_";
            }
            else{
                ShipSegment* segment= Field[y][x].GetShipSegment();
                if (segment->GetState() == SegmentState::Intact) {
                    std::cout << "2";
                }
                else if (segment->GetState() == SegmentState::Damaged) {
                    std::cout << "1";
                }
                else {
                    std::cout << "0";
                }
            }
        }
        std::cout << "\n";
    }
}

void GameField::PrintFieldComputer() {
    for (int y = 0; y < row; y++) {
        for (int x = 0; x < col; x++) {
            if (Field[y][x].GetStatus() == CellStatus::Empty) {
                std::cout << "X";
            }
            else if (Field[y][x].GetStatus() == CellStatus::Unknown) {
                std::cout << "_";
            }
            else {
                ShipSegment* segment = Field[y][x].GetShipSegment();
                if (segment->GetState() == SegmentState::Intact) {
                    std::cout << "_";
                }
                else if (segment->GetState() == SegmentState::Damaged) {
                    std::cout << "1";
                }
                else {
                    std::cout << "0";
                }
            }
        }
        std::cout << "\n";
    }
}


nlohmann::json GameField::to_json() const {
    nlohmann::json j;
    j["row"] = row;
    j["col"] = col;
    j["field"] = nlohmann::json::array();
    for (const auto& row : Field) {
        nlohmann::json jsonRow = nlohmann::json::array();
        for (const auto& cell : row) {
            jsonRow.push_back(cell.to_json()); 
        }
        j["field"].push_back(jsonRow);
    }
    return j;
}


GameField GameField::from_json(const nlohmann::json& j) {
    if (!j.contains("row") || !j.contains("col")) {
        throw std::invalid_argument("problem in fromjson in GameField : /");
    }
    int row = j["row"].get<int>();
    int col = j["col"].get<int>();
    GameField field(col, row);
    for (size_t i = 0; i < j["field"].size(); i++) {
        for (size_t k = 0; k < j["field"][i].size(); k++) {
            field.Field[i][k] = Cell::from_json(j["field"][i][k]);
        }
    }
    return field;

}

void GameField::restoreConnection(ShipManager& manager) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (Field[i][j].GetStatus() == CellStatus::Ship) {
                int indShip = Field[i][j].GetIndShip();
                int indSeg = Field[i][j].GetIndSeg();
                if (indSeg < 0 || indShip < 0 || indShip >= manager.GetShipCount()) {
                    throw std::invalid_argument("problem in fromjson in restoreConnection : /");
                }
                Field[i][j].SetShipSegment(manager.GetShip(indShip).GetSegment(indSeg));
            }
        }
    }
}