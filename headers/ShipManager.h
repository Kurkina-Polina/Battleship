#pragma once
#include "Ship.h"
#include <vector>
#include <iostream>

#include "json.hpp"

class ShipManager {
private:
    std::vector<Ship> Ships;
public:
    ShipManager(int count_ships, std::vector<int> sizes_ships);
    ShipManager(){}
    
    int GetShipCount() const;

    Ship& GetShip(int index);

    void AddShip(Ship& ship);

    ShipManager& operator=(ShipManager&& other) noexcept;

    nlohmann::json to_json() const;

    static ShipManager from_json(const nlohmann::json& j);
    ShipManager(const ShipManager& other);
    ShipManager& operator=(const ShipManager& other);
};