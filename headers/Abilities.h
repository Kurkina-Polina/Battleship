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

public:
	virtual ~Ability() = default;
	virtual std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) = 0;
	virtual std::string getName() const = 0;
};

class DoubleHit : public Ability {

	std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) override;
	std::string getName() const override {return "Double Damage";}
};
class Scanner : public Ability {

	std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) override;
	std::string getName() const override {return "Scanner";}
};

class Shelling : public Ability {

	std::tuple<bool, AbilityStatus> apply(GameField& field, ShipManager& shipManager, AbilityManager& abilityManager) override;
	std::string getName() const override {return "Shelling";}
};


