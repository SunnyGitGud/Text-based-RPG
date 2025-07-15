#pragma once
#include <iostream>
#include "StandMember.hpp"
#include "Ability.hpp"
#include "StatusEffect.hpp"

class BattleSystem {
public:
    static void useAbility(StandMember& attacker, StandMember& target, const Ability& ability) {
        std::cout << "\n🌀 " << attacker.getName() << " uses " << ability.name
                  << " on " << target.getName() << "!\n";

        if (ability.type == AbilityType::Normal) {
            // Basic damage logic
            int baseDamage = attacker.getStats().atk - target.getStats().def;
            int totalDamage = std::max(baseDamage + ability.power, 1);
            target.getHP().TakeDamage(totalDamage);

            std::cout << "💥 " << target.getName() << " takes " << totalDamage
                      << " damage. [HP: " << target.getHP().getHP() << "]\n";
        }

        // Status effect logic (only if it's not "None")
        if (ability.statusEffect != StatusEffect::None) {
            int roll = rand() % 100;
            if (roll < ability.effectChance) {
                bool applied = target.tryApplyStatus(ability.statusEffect);
                if (applied)
                    std::cout << "☠️ " << target.getName() << " is affected by "
                              << statusEffectName(ability.statusEffect) << "!\n";
                else
                    std::cout << "🛡️ " << target.getName() << " resisted the effect.\n";
            }
        }
    }

private:
    static std::string statusEffectName(StatusEffect effect) {
        switch (effect) {
            case StatusEffect::Poison: return "Poison";
            case StatusEffect::Stun:   return "Stun";
            case StatusEffect::Silence:return "Silence";
            default:                   return "Unknown";
        }
    }
};
