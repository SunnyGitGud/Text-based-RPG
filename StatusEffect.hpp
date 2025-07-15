#pragma once
#include <string>

enum class StatusEffect {
    None,
    Poison,
    Stun,
    Silence
};

inline std::string statusEffectName(StatusEffect effect) {
    switch (effect) {
        case StatusEffect::Poison:  return "Poison";
        case StatusEffect::Stun:    return "Stun";
        case StatusEffect::Silence: return "Silence";
        case StatusEffect::None:    return "None";
        default:                    return "Unknown";
    }
}
