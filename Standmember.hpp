#pragma once
#include <string>
#include <random>
#include <iostream>
#include "hp.hpp"
#include "StatBlock.hpp"
#include "Ability.hpp"
#include <vector>

enum class StandType {
    Power,
    Defense,
    Speed,
    Control
};

class StandMember {
private:
    std::string name;
    StandType type;
    hp health;
    StatBlock stats;
    std::vector<Ability> abilities;

    int poisonDuration = 0;
    int stunDuration = 0;
    int silenceDuration = 0;

public:
    StandMember(const std::string& name, StandType type, hp health, StatBlock stats)
        : name(name), type(type), health(health), stats(stats) {}

    std::string getName() const { return name; }
    StandType getType() const { return type; }

    hp& getHP() { return health; }
    const hp& getHP() const { return health; }
    const StatBlock& getStats() const { return stats; }

    bool isAlive() const {
        return health.getHP() > 0;
    }

    bool tryApplyStatus(StatusEffect effect) {
        int resist = 0;

        switch (effect) {
            case StatusEffect::Poison:  resist = stats.poisonResist; break;
            case StatusEffect::Stun:    resist = stats.stunResist; break;
            case StatusEffect::Silence: resist = stats.silenceResist; break;
        }

        int roll = rand() % 100;
        if (roll >= resist) {
            switch (effect) {
                case StatusEffect::Poison:  poisonDuration = 3; break;
                case StatusEffect::Stun:    stunDuration = 1; break;
                case StatusEffect::Silence: silenceDuration = 2; break;
            }
            return true;
        }
        return false;
    }

    bool isPoisoned() const { return poisonDuration > 0; }
    bool isStunned() const { return stunDuration > 0; }
    bool isSilenced() const { return silenceDuration > 0; }

    ui16 getCurrentHP() const {
        return health.getHP();
    }

    void addAbility(const Ability& ability) {
        abilities.push_back(ability);
    }

    const Ability& getAbility(int index) const {
        return abilities.at(index);
    }

    void listAbilities() const {
        for (size_t i = 0; i < abilities.size(); ++i) {
            std::cout << i << ": " << abilities[i].name << "\n";
        }
    }

    const std::vector<Ability>& getAbilities() const {
        return abilities;
    }

    void updateStatusEffects() {
        if (poisonDuration > 0) {
            poisonDuration--;
            health.TakeDamage(5);
            std::cout << "☠️ " << name << " takes 5 poison damage!\n";
        }

        if (stunDuration > 0)
            stunDuration--;

        if (silenceDuration > 0)
            silenceDuration--;
    }
};
