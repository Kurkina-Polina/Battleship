#pragma once
#include <queue>
#include <vector>
#include <iostream>
#include <random>
#include "Ship.h"
#include "ShipManager.h"
#include "Field.h"
#include "Abilities.h"
#include "Exceptions.h"
#include "json.hpp"
#include "Input.h"
#include "AbilityStatus.h"
class Input;

class AbilityManager {
private:
    std::queue<std::unique_ptr<Ability>> abilities;
    bool FlagHit; 
    Input* input;

public:
    AbilityManager();
    ~AbilityManager() { delete input; }

    AbilityManager(const AbilityManager&) = delete;
    AbilityManager& operator=(const AbilityManager&) = delete;

    AbilityManager(AbilityManager&& other) noexcept
        : abilities(std::move(other.abilities)),
        FlagHit(other.FlagHit),
        input(other.input) {
        other.input = nullptr; 
    }

    AbilityManager& operator=(AbilityManager&& other) noexcept {
        if (this != &other) {
            abilities = std::move(other.abilities);
            FlagHit = other.FlagHit;

            delete input; 
            input = other.input;
            other.input = nullptr;
        }
        return *this;
    }
    int GetSize() const;

    void SetInput(Input* input) { input = input; }

    Input* GetInput() { return input; }

    void SetFlag() { FlagHit = true;}


    bool GetFlag() {
        bool tmpFlag = FlagHit;
        FlagHit = false; 
        return tmpFlag;
    }

    void getRandomAbility();

    std::tuple<bool, AbilityStatus> applyAbility(GameField& gameField, ShipManager& shipManager);

    void removeAbility(){ abilities.pop(); }

    
};
