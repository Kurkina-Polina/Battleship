#pragma once
#include <queue>
#include <vector>
#include <iostream>
#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "AbilityStatus.h"


class AbilityManager;
class Ability {
/// <summary>
/// передавать через конструктор
/// </summary>
public:
	virtual ~Ability() = default;
	virtual std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) = 0;
	virtual std::string getName() const = 0;
};

// наносит двойной удар
class DoubleHit : public Ability {

	std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) override;
	std::string getName() const override {return "Double Damage";}
};
// сканирует обласить 2х2 от выбранной точки и вправо вниз
class Scanner : public Ability {

	std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) override;
	std::string getName() const override {return "Scanner";}
};
//обстраел: наносит удар случайному сегменту случайного корябля. не меняет статус клетки
class Shelling : public Ability {

	std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) override;
	std::string getName() const override {return "Shelling";}
};


