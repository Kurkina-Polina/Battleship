#include "ShipManager.h"
#include <iostream>
#include <vector>


ShipManager::ShipManager(int count_ships, std::vector<int> sizes_ships) {
    for (int i = 0; i < count_ships; i++) {
        Ships.push_back(Ship(sizes_ships[i], Orientation::Horizontal));
    }
}

int ShipManager::GetShipCount() const { return Ships.size(); }

Ship& ShipManager::GetShip(int index) {
    return Ships[index];
}

void ShipManager::AddShip(Ship& ship) {
    Ships.push_back(ship);
}

ShipManager::ShipManager(const ShipManager& other) {
    Ships = other.Ships;
}

ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) {
        Ships = other.Ships;
    }
    return *this;
}

ShipManager& ShipManager::operator=(ShipManager&& other) noexcept {
    if (this != &other) {
        Ships = std::move(other.Ships);
    }
    return *this;
}

nlohmann::json ShipManager::to_json() const {
    nlohmann::json ships_j = nlohmann::json::array();
    for (const auto& ship : Ships) {
        ships_j.push_back(ship.to_json());
    }
    nlohmann::json manager;
    manager["ships"] = ships_j;
    return manager;
}

ShipManager ShipManager::from_json(const nlohmann::json& j) {
    if (!j.contains("ships") || !j["ships"].is_array()) {
        throw std::invalid_argument("problem in fromjson in ShipMananger : /");
    }
    std::vector<Ship> ships;
    nlohmann::json ships_j = j["ships"];
    for (const auto& ship_j : ships_j) {
        Ship ship = Ship::from_json(ship_j);
        ships.push_back(ship);
    }
    ShipManager manager;
    manager.Ships = ships;
    return manager;
}