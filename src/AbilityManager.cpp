#include <queue>
#include <vector>
#include <iostream>
#include <random>
#include "AbilityMananger.h"
#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "Abilities.h"
#include "Exceptions.h"
#include "json.hpp"


AbilityManager::AbilityManager() :input(nullptr), FlagHit(false){
    std::vector<std::unique_ptr<Ability>> availableAbilities;

    availableAbilities.push_back(std::make_unique<DoubleHit>());
    availableAbilities.push_back(std::make_unique<Scanner>());
    availableAbilities.push_back(std::make_unique<Shelling>());

    std::mt19937 rng;
    std::shuffle(availableAbilities.begin(), availableAbilities.end(), rng);

    for (auto& ability : availableAbilities) {
        abilities.push(std::move(ability));
    }
}
int AbilityManager::GetSize() const{
    return abilities.size();
}


void AbilityManager::getRandomAbility() {
    
    srand(time(0)); 
    int randomIndex = rand()%3;
    std::vector<std::function<std::unique_ptr<Ability>()>> abilitiesFactory = {
        []() { return std::make_unique<DoubleHit>(); },
        []() { return std::make_unique<Scanner>(); },
        []() { return std::make_unique<Shelling>(); }
    };

    abilities.push(std::move(abilitiesFactory[randomIndex]()));
}

std::tuple<bool, AbilityStatus> AbilityManager::applyAbility(GameField& gameField, ShipManager& shipManager) {
    if (abilities.empty()) {
        throw  NoAbilities();
    }
    std::unique_ptr<Ability>  ability = std::move(abilities.front());
    abilities.pop();
    return ability->apply(gameField, shipManager, *this);
}
