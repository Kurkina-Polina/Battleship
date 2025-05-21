#pragma once
#include "Ship.h"
#include <vector>
#include <iostream>

#include "json.hpp"
//Создать класс менеджера кораблей, хранящий информацию о кораблях.

class ShipManager {
private:
    std::vector<Ship> Ships;
public:
    ShipManager(int count_ships, std::vector<int> sizes_ships);
    ShipManager(){}
    
    // дает колво кораблей
    int GetShipCount() const;

    // дает ссылку на корабль по индексу
    Ship& GetShip(int index);

    // добавляет корабль в список кораблей
    void AddShip(Ship& ship);

    // Оператор присваивания перемещением
    ShipManager& operator=(ShipManager&& other) noexcept;
    // Метод сериализации
    nlohmann::json to_json() const;

    // Метод десериализации
    static ShipManager from_json(const nlohmann::json& j);
    ShipManager(const ShipManager& other);
    ShipManager& operator=(const ShipManager& other);
};