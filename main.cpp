#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include "Standmember.hpp"
#include "BattleSystem.hpp"
#include "testutils.hpp"
#include "party.hpp"




void printAbilities(const StandMember& member) {
    const auto& abilities = member.getAbilities();
    std::cout << "+---------------------------+\n";
    std::cout << "|         ATTACKS          |\n";
    std::cout << "+---------------------------+\n";
    for (size_t i = 0; i < abilities.size(); ++i) {
        std::cout << "| " << std::setw(2) << i << ": " << std::setw(20) << std::left << abilities[i].name;
        if (abilities[i].type == AbilityType::Buff)
            std::cout << " (Buff)    |\n";
        else if (abilities[i].type == AbilityType::Debuff)
            std::cout << " (Debuff)  |\n";
        else if (abilities[i].type == AbilityType::Ultimate)
            std::cout << " (Ultimate)|\n";
        else
            std::cout << " (Normal)  |\n";
    }
    std::cout << "+---------------------------+\n";
}


void printEnemyTargets(const Party& enemyParty) {
    std::cout << "\n+---------------------- Targets ----------------------+\n";
    for (size_t i = 0; i < enemyParty.size(); ++i) {
        const auto& target = enemyParty.getMember(i);
        std::cout << "| " << i << ": " << std::setw(15) << target.getName()
                  << " HP: " << target.getHP().getHP() << (target.isAlive() ? "     |\n" : " (KO'd) |\n");
    }
    std::cout << "+-----------------------------------------------------+\n";
}

int main() {
    srand(time(0));

    std::vector<std::vector<Ability>> allAbilities;
    createTestAbilities(allAbilities);

    Party playerParty;
    playerParty.addMember(createMember("Crimson Pulse", StandType::Power, 100, 20, 10, 10, allAbilities[0]));
    playerParty.addMember(createMember("Stone Widow", StandType::Defense, 120, 15, 20, 8, allAbilities[1]));
    playerParty.addMember(createMember("Voltage Waltz", StandType::Speed, 90, 18, 8, 25, allAbilities[2]));

    Party enemyParty;
    enemyParty.addMember(createMember("Mirror Shade", StandType::Control, 90, 16, 9, 12, allAbilities[1]));
    enemyParty.addMember(createMember("Granite Echo", StandType::Defense, 130, 13, 18, 6, allAbilities[0]));
    enemyParty.addMember(createMember("Shock Tempo", StandType::Speed, 95, 17, 10, 22, allAbilities[2]));

    int turn = 1;
    while (!playerParty.isDefeated() && !enemyParty.isDefeated()) {
        std::cout << "\n--- Turn " << turn << " ---\n";

        for (int i = 0; i < playerParty.size(); ++i) {
            auto& attacker = playerParty.getMember(i);
            if (!attacker.isAlive()) continue;

            std::cout << "\nChoose attack for " << attacker.getName() << ":\n";
            printAbilities(attacker);

            int abilityChoice;
            std::cout << "Enter ability index (0-5): ";
            std::cin >> abilityChoice;
            if (std::cin.fail() || abilityChoice < 0 || abilityChoice >= attacker.getAbilities().size()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid choice! Skipping turn.\n";
                continue;
            }

            printEnemyTargets(enemyParty);
            int targetIndex;
            std::cout << "Select target index: ";
            std::cin >> targetIndex;
            if (std::cin.fail() || targetIndex < 0 || targetIndex >= enemyParty.size() || !enemyParty.getMember(targetIndex).isAlive()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid target! Skipping turn.\n";
                continue;
            }

            auto& target = enemyParty.getMember(targetIndex);
            const Ability& ab = attacker.getAbility(abilityChoice);
            BattleSystem::useAbility(attacker, target, ab);
        }

        for (int i = 0; i < enemyParty.size(); ++i) {
            auto& attacker = enemyParty.getMember(i);
            if (!attacker.isAlive()) continue;
            auto& target = playerParty.getFirstAlive();
            const Ability& ab = attacker.getAbility(rand() % attacker.getAbilities().size());
            BattleSystem::useAbility(attacker, target, ab);
        }

        playerParty.updateAllStatusEffects();
        enemyParty.updateAllStatusEffects();

        ++turn;
    }

    std::cout << "\n\n====== BATTLE RESULT ======\n";
    if (playerParty.isDefeated())
        std::cout << "You lost the battle...\n";
    else
        std::cout << "You won the battle!\n";

    return 0;
}
