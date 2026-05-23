#include "player.h"
 int main(){
    player_ player;
    while (player.isAlive()){
        unique_ptr<enemy> enemy = enemyFactory::random_enemy();
        std::cout << "A wild " << enemy->getType() << " appears!" << endl;
        while (enemy->isAlive() && player.isAlive()){
            std::cout << "Player's health: " << player.getHealth() << endl;
            std::cout << "Enemy's health: " << enemy->getHealth() << endl;
            std::cout << "Please select an action: " << endl;
            std::cout << "1. Attack" << endl;
            std::cout << "2. Run" << endl;
            int choice;
            std::cin >> choice;  
            if (choice == 1){
                player.attack(enemy.get());
                if (enemy->isAlive()){
                    enemy->attack();
                    player.takeDamage(enemy->getAttackPower());
                }
            }
            else if (choice == 2){
                std::cout << "Player runs away!" << endl;
                break;
            }
            else{
                std::cout << "Invalid choice, please try again!" << endl;
            }
        }
    }
}
