#include "raylib.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include "Standmember.hpp"
#include "BattleSystem.hpp"
#include "StatBlock.hpp"
#include "Ability.hpp"
#include "Party.hpp"

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

int main() {
    InitWindow(800, 600, "Overworld + Battle Demo");
    SetTargetFPS(60);

    Texture2D playerTex = LoadTexture("player.png");
    Texture2D enemyTex = LoadTexture("enemy.png");

    Rectangle playerRect = {100.0f, 100.0f, 32.0f, 32.0f};
    Rectangle enemyRect = {500.0f, 300.0f, 32.0f, 32.0f};
    float speed = 2.0f;

    bool inBattle = false;
    int turn = 1;
    int selectedAbility = -1;
    int selectedTarget = -1;
    int currentPlayer = 0;

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

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!inBattle) {
            if (IsKeyDown(KEY_RIGHT)) playerRect.x += speed;
            if (IsKeyDown(KEY_LEFT)) playerRect.x -= speed;
            if (IsKeyDown(KEY_UP)) playerRect.y -= speed;
            if (IsKeyDown(KEY_DOWN)) playerRect.y += speed;

            DrawTextureRec(playerTex, Rectangle{0,0,64,64}, Vector2{playerRect.x, playerRect.y}, WHITE);
            DrawTextureRec(enemyTex, Rectangle{0,0,64,64}, Vector2{enemyRect.x, enemyRect.y}, WHITE);

            if (CheckCollisionRecs(playerRect, enemyRect)) {
                inBattle = true;
            }
        } else if (!playerParty.isDefeated() && !enemyParty.isDefeated()) {
            DrawText(TextFormat("Turn %d", turn), 10, 10, 20, BLACK);

            if (currentPlayer < playerParty.size()) {
                StandMember& attacker = playerParty.getMember(currentPlayer);
                if (attacker.isAlive()) {
                    DrawText(TextFormat("Choose attack for %s", attacker.getName().c_str()), 10, 40, 20, DARKBLUE);

                    for (int i = 0; i < attacker.getAbilities().size(); i++) {
                        DrawRectangle(10, 70 + i * 40, 300, 30, LIGHTGRAY);
                        DrawText(TextFormat("%d: %s", i, attacker.getAbility(i).name.c_str()), 15, 75 + i * 40, 18, BLACK);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            Vector2 mouse = GetMousePosition();
                            Rectangle rect = {10.0f, 70.0f + static_cast<float>(i) * 40.0f, 300.0f, 30.0f};
                                if (CheckCollisionPointRec(mouse, rect)) {
                                    selectedAbility = i;
                                }
                        }
                    }

                    if (selectedAbility != -1) {
                        DrawText("Choose a target:", 350, 40, 20, MAROON);
                        int targetY = 70;
                        for (int i = 0; i < enemyParty.size(); ++i) {
                            if (!enemyParty.getMember(i).isAlive()) continue;
                            DrawRectangle(350, targetY, 300, 30, LIGHTGRAY);
                            DrawText(TextFormat("%d: %s (HP: %d)", i, enemyParty.getMember(i).getName().c_str(), enemyParty.getMember(i).getHP().getHP()), 355, targetY + 5, 18, BLACK);
                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                Vector2 mouse = GetMousePosition();
                                if (CheckCollisionPointRec(mouse, Rectangle{350, (float)targetY, 300, 30})) {
                                    selectedTarget = i;
                                }
                            }
                            targetY += 40;
                        }

                        if (selectedTarget != -1) {
                            StandMember& target = enemyParty.getMember(selectedTarget);
                            const Ability& ab = attacker.getAbility(selectedAbility);
                            BattleSystem::useAbility(attacker, target, ab);
                            selectedAbility = -1;
                            selectedTarget = -1;
                            currentPlayer++;
                        }
                    }
                } else {
                    currentPlayer++;
                }
            } else {
                for (int i = 0; i < enemyParty.size(); ++i) {
                    auto& attacker = enemyParty.getMember(i);
                    if (!attacker.isAlive()) continue;
                    auto& target = playerParty.getFirstAlive();
                    const Ability& ab = attacker.getAbility(rand() % attacker.getAbilities().size());
                    BattleSystem::useAbility(attacker, target, ab);
                }
                playerParty.updateAllStatusEffects();
                enemyParty.updateAllStatusEffects();
                currentPlayer = 0;
                turn++;
            }
        } else {
            DrawText("Battle Over!", 300, 280, 30, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
