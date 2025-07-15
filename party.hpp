#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Standmember.hpp"


class Party {
public:
    static const int MAX_PARTY_SIZE = 4;

    bool addMember(const StandMember& member) {
        if (members.size() >= MAX_PARTY_SIZE) {
            std::cout << "Party is full!\n";
            return false;
        }
        members.push_back(member);
        return true;
    }

    void listMembers() const {
        std::cout << "your party:\n";
        for (const auto& m : members) {
            std::cout << "- " << m.getName() << "\n";
        }
    }

    const auto& getMembers() const {
        return members;
    }
  
    StandMember& getMember(int index) {
        return members.at(index);
    }
    const StandMember& getMember(int index) const {
        return members.at(index);
    }
    size_t size() const {
        return members.size();
    }

    void listParty() const {
        for (size_t i = 0; i < members.size(); ++i) {
            std::cout << i << ". " << members[i].getName()
                << " (HP: " << members[i].getHP().getHP() << ")\n";
        }
    }

    void switchActive(int index) {
        if (index >= 0 && index < members.size())
            currentIndex = index;
    }

    bool hasLivingMembers() const {
        for (const auto& m : members) {
            if (m.isAlive()) return true;
        }
        return false;
    }

    // Returns true if all members are dead
    bool isDefeated() const {
        for (const auto& m : members) {
            if (m.isAlive()) return false;
        }
        return true;
    }

    // Updates status effects for all members
    void updateAllStatusEffects() {
        for (auto& m : members) {
            m.updateStatusEffects();
        }
    }

    // Returns first alive member (non-const for targeting)
    StandMember& getFirstAlive() {
        for (auto& m : members) {
            if (m.isAlive()) return m;
        }
        throw std::runtime_error("No living members in party");
    }

private:
    std::vector<StandMember> members;
    int currentIndex = 0;
};