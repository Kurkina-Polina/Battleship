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
    bool FlagHit; //флаг того применена ли способность duble_hit
    Input* input;

public:
    AbilityManager();
    ~AbilityManager() { delete input; }

    // Запрет копирования
    AbilityManager(const AbilityManager&) = delete;
    AbilityManager& operator=(const AbilityManager&) = delete;

    // Разрешение перемещения
    AbilityManager(AbilityManager&& other) noexcept
        : abilities(std::move(other.abilities)),
        FlagHit(other.FlagHit),
        input(other.input) {
        other.input = nullptr; // Обнуление указателя у перемещённого объекта
    }

    AbilityManager& operator=(AbilityManager&& other) noexcept {
        if (this != &other) {
            abilities = std::move(other.abilities);
            FlagHit = other.FlagHit;

            delete input; // Удаляем старый ресурс
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
        FlagHit = false; // состояние флага проверяется перед ударом. В хит я не могу удалить удар, тк не пердаю ссылку на манагаера сп-тей. Но в силу того, что если флаг возвращается тру, то после этого будет применена двойная аттака почти сразу
        // исключений тут нет так что мы запрашиваем флаг и при этом у нас нет нужны его убрать. Поэтому будем сбрасывать флаг каждый раз после того как его запросили))
        return tmpFlag;
    }

    void getRandomAbility();

    std::tuple<bool, AbilityStatus> applyAbility(GameField& gameField, ShipManager& shipManager);

    void removeAbility(){ abilities.pop(); }

    
};
