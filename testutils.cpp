#include "TestUtils.hpp"

void createTestAbilities(std::vector<std::vector<Ability>>& allAbilities) {
    allAbilities = {
        {
            {"Pulse Jab", AbilityType::Normal, 10, StatusEffect::None, 0},
            {"Breaker Shout", AbilityType::Normal, 15, StatusEffect::Stun, 20},
            {"Echo Drive", AbilityType::Normal, 12, StatusEffect::None, 0},
            {"Crimson Riot", AbilityType::Buff, 0, StatusEffect::None, 0},
            {"Mute Anthem", AbilityType::Debuff, 0, StatusEffect::Silence, 40},
            {"Final Reverb", AbilityType::Ultimate, 30, StatusEffect::Stun, 50}
        },
        {
            {"Thread Bite", AbilityType::Normal, 8, StatusEffect::Poison, 40},
            {"Iron Snap", AbilityType::Normal, 10, StatusEffect::None, 0},
            {"Web Crush", AbilityType::Normal, 14, StatusEffect::Stun, 25},
            {"Stone Guard", AbilityType::Buff, 0, StatusEffect::None, 0},
            {"Trap Thread", AbilityType::Debuff, 0, StatusEffect::Stun, 50},
            {"Widow's Bloom", AbilityType::Ultimate, 28, StatusEffect::Silence, 40}
        },
        {
            {"Tempo Cut", AbilityType::Normal, 10, StatusEffect::None, 0},
            {"Flash Fade", AbilityType::Normal, 12, StatusEffect::None, 0},
            {"Discharge Spiral", AbilityType::Normal, 14, StatusEffect::Stun, 30},
            {"Quickstep Sync", AbilityType::Buff, 0, StatusEffect::None, 0},
            {"Rust Tempo", AbilityType::Debuff, 0, StatusEffect::Silence, 50},
            {"Storm Encore", AbilityType::Ultimate, 25, StatusEffect::Poison, 30}
        }
    };
}

StandMember createMember(const std::string& name, StandType type, int hpVal, int atk, int def, int spd, const std::vector<Ability>& abilities) {
    StatBlock stats = {static_cast<ui8>(atk), static_cast<ui8>(def), static_cast<ui8>(spd), 10, 10, 10};
    hp myHP(hpVal, hpVal, 0);
    StandMember member(name, type, myHP, stats);
    for (const auto& ab : abilities) {
        member.addAbility(ab);
    }
    return member;
}
