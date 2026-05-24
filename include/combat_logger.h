// include/combat_logger.h
#pragma once
#include "observer.h"

class CombatLogger : public observer {
public:
    void update(const std::string& event, int value, const std::string& source) override {
        if (event == "PLAYER_DAMAGE") {
            std::cout << "💥 " << source << " took " << value << " damage!\n";
        }
        else if (event == "ENEMY_DAMAGE") {
            std::cout << "⚔️  " << source << " took " << value << " damage!\n";
        }
        else if (event == "ENEMY_DEATH") {
            std::cout << "✅ " << source << " has been defeated!\n";
        }
        else if (event == "PLAYER_DEATH") {
            std::cout << "💀 You have fallen...\n";
        }
        else {
            std::cout << "🔍 Unknown event: " << event << " from " << source << " with value " << value << "\n";
        }
    }
};