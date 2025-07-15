#pragma once
#include <vector>
#include "Ability.hpp"
#include "StandMember.hpp"

void createTestAbilities(std::vector<std::vector<Ability>>& allAbilities);

StandMember createMember(const std::string& name, StandType type, int hpVal, int atk, int def, int spd, const std::vector<Ability>& abilities);
