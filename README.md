# Text Based RPG- Unfinished

A simple turn-based RPG game written in C++. Players and enemies take turns using abilities, applying status effects, and managing HP. The game is played in the terminal and features a party system, abilities, and status effects.

## Features
- Party system for both player and enemy
- Multiple StandMember types (Power, Defense, Speed, Control)
- Abilities with types: Normal, Buff, Debuff, Ultimate
- Status effects: Poison, Stun, Silence
- Turn-based battle loop
- Input validation for ability and target selection

## File Structure
- `main.cpp` — Main game loop and user interface
- `party.hpp` — Party class and party management
- `Standmember.hpp` — StandMember class and battle logic
- `BattleSystem.hpp` — Ability usage and status effect application
- `ability.hpp` — Ability struct and types
- `StatusEffect.hpp` — Status effect enum and helpers
- `StatBlock.hpp` — StatBlock struct for member stats
- `hp.hpp` — HP management class
- `hitpointtypes.hpp` — Type definitions for HP
- `testutils.cpp` / `testutils.hpp` — Utility functions for creating test data

## How to Build
1. Make sure you have a C++ compiler (e.g., g++).
2. Open a terminal in the project directory.
3. Run:
   ```sh
   g++ main.cpp testutils.cpp -o main.exe
   ```
4. Run the game:
   ```sh
   ./main.exe
   ```
   (On Windows, use `main.exe`)

## How to Play
- On your turn, select an ability and a target from the enemy party.
- Abilities may deal damage or apply status effects.
- The battle continues until one party is defeated.

## Customization
- Add new StandMembers, abilities, or status effects by editing the relevant header/source files.
- Change party size or stats in `party.hpp` and `StatBlock.hpp`.

## License
This project is for educational purposes and is provided as-is.
