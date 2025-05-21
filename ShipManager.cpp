#include "ShipManager.h"
#include <iostream>
#include <vector>


ShipManager::ShipManager(int count_ships, std::vector<int> sizes_ships) {
    for (int i = 0; i < count_ships; i++) {
        Ships.push_back(Ship(sizes_ships[i], Orientation::Horizontal));
    }
}

// дает колво кораблей
int ShipManager::GetShipCount() const { return Ships.size(); }

// дает ссылку на корабль по индексу
Ship& ShipManager::GetShip(int index) {
    return Ships[index];
}

// добавляет корабль в список кораблей
void ShipManager::AddShip(Ship& ship) {
    Ships.push_back(ship);
}

//ShipManager& ShipManager::operator=(ShipManager&& other) noexcept {
//    if (this != &other) {
//
//        Ships = std::move(other.Ships);
//
//    }
//    return *this;
//}
//// Конструктор копирования
//ShipManager::ShipManager(const ShipManager& other) {
//    Ships = other.Ships; // Копируем вектор ships элемент за элементом
//}

// Конструктор копирования
ShipManager::ShipManager(const ShipManager& other) {
    Ships = other.Ships;
}

// Оператор присваивания копированием
ShipManager& ShipManager::operator=(const ShipManager& other) {
    if (this != &other) {
        Ships = other.Ships;
    }
    return *this;
}

// Перемещающий оператор присваивания
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
    // Проверка наличия необходимых полей
    if (!j.contains("ships") || !j["ships"].is_array()) {
        throw std::invalid_argument("problem in fromjson in ShipMananger : /");
    }
    std::vector<Ship> ships;
    //std::vector<int> sizes_ships; //да создаю отдельный массив, тк иначе нужно создавать пустой контейнер
    nlohmann::json ships_j = j["ships"];
    for (const auto& ship_j : ships_j) {
        Ship ship = Ship::from_json(ship_j);
        ships.push_back(ship);
        //sizes_ships.push_back(ship.GetLength());
    }
    //ShipManager manager(sizes_ships.size(), sizes_ships);
    ShipManager manager;
    manager.Ships = ships;
    return manager;
}