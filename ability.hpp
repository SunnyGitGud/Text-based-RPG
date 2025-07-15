#pragma once
#include <string>
#include "StatusEffect.hpp"



enum class AbilityType {
    Normal,
    Buff,
    Debuff,
    Ultimate
};


struct Ability {
    std::string name;
    AbilityType type;
    int power;
    StatusEffect statusEffect;
    int effectChance;

    Ability(const std::string& name, AbilityType type, int power,
            StatusEffect statusEffect = StatusEffect::None, int effectChance = 0)
        : name(name), type(type), power(power),
          statusEffect(statusEffect), effectChance(effectChance) {}
};