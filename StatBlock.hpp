#pragma once
#include "hitpointtypes.hpp"

struct StatBlock {
    ui8 atk = 0;
    ui8 def = 0;
    ui8 spd = 0;

    // Resistance values: 0–100 (% chance to resist)
    ui8 poisonResist = 0;
    ui8 stunResist = 0;
    ui8 silenceResist = 0;
};
  