#include "player.h"
#include "enemy_factory.h"
#include "combat_logger.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void printStory(int wave) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    
    if (wave == 0) {
        std::cout << "🌲 You are the legendary Hero.\n";
        std::cout << "Your best friend has been captured by the evil Vampire King Nebula.\n";
        std::cout << "You venture into the cursed forest to reach his dark castle...\n";
    } 
    else if (wave == 5) {
        std::cout << "🏰 You have finally reached the gates of Nebula's Dark Castle!\n";
        std::cout << "The air grows cold... The final battle awaits.\n";
    } 
    else {
        std::cout << "Wave " << wave << " - Vampire King Nebula sends more monsters to stop you!\n";
    }
    
    std::cout << std::string(60, '=') << "\n\n";
}

int main() {
    std::srand(static_cast<unsigned>(time(0)));

    player_ player;
    auto logger = std::make_shared<CombatLogger>();
    player.attach(logger);

    int wave = 0;
    bool gameOver = false;

    std::cout << "=== HERO'S REVENGE: VAMPIRE KING NEBULA ===\n\n";

    while (!gameOver && player.isAlive()) {
        printStory(wave);

        std::cout << "Your Status → HP: " << player.getHealth() << "/" << player.getMaxHealth()
                  << " | Attack: " << player.getAttackPower()
                  << " | Potions: " << player.getPotions() << "\n\n";

        std::unique_ptr<enemy> currentEnemy;

        // Final Boss after 5 waves
        if (wave >= 5) {
            currentEnemy = enemyFactory::create_boss();
        } else {
            currentEnemy = enemyFactory::random_enemy();
        }

        if (!currentEnemy) {
            std::cout << "Error spawning enemy!\n";
            break;
        }

        // Attach logger to enemy
        currentEnemy->attach(logger);

        std::cout << "A " << currentEnemy->getType() << " appears!\n\n";

        // Combat Loop
        while (currentEnemy->isAlive() && player.isAlive()) {
            std::cout << "1. Attack\n";
            std::cout << "2. Use Potion (" << player.getPotions() << " left)\n";
            std::cout << "3. Run\n";
            std::cout << "Choose your action: ";

            int choice;
            std::cin >> choice;

            if (choice == 1) {
                player.attack(currentEnemy.get());

                if (currentEnemy->isAlive()) {
                    currentEnemy->attack();
                    player.takeDamage(currentEnemy->getAttackPower());
                }
            } 
            else if (choice == 2) {
                player.usePotion();
            } 
            else if (choice == 3) {
                std::cout << "You ran away safely...\n";
                break;
            } 
            else {
                std::cout << "Invalid choice!\n";
            }
        }

        // Check game result
        if (!player.isAlive()) {
            std::cout << "\n💀 You have been defeated...\n";
            std::cout << "Your best friend remains trapped forever.\n";
            gameOver = true;
        }
        else if (!currentEnemy->isAlive()) {
            std::cout << "\n✅ " << currentEnemy->getType() << " has been defeated!\n";

            if (wave >= 5) {
                std::cout << "\n🎉 VICTORY! You defeated Vampire King Nebula!\n";
                std::cout << "Your best friend is saved. You are a legend!\n";
                gameOver = true;
            } else {
                player.levelUp();
                wave++;
                std::cout << "You feel stronger... Moving to next wave.\n";
            }
        }
    }

    std::cout << "\n=== Game Over ===\n";
    return 0;
}