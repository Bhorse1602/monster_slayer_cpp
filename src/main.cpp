#include "player.h"
REGISTER_ENEMY(orc)
REGISTER_ENEMY(goblin)
REGISTER_ENEMY(giant)
int main(){
    player_ player;
    while (player.isAlive()){
       
        cout << "Player's Initial health: " << player.getHealth() << endl;
        unique_ptr<enemy> enemy = enemyFactory::random_enemy();
       
        std::cout << "A wild " << enemy->getType() << " appears!" << "Health: " << enemy->getHealth() << ", Attack Power: " << enemy->getAttackPower() << endl;
        int playerInitialHealth = player.getHealth();
        while (enemy->isAlive() && player.isAlive()){
            
            if(player.getHealth() < playerInitialHealth / 2){
                std::cout << "Player's health is low! Consider running away!" << endl;
            }
            else if(player.getHealth() < playerInitialHealth ){
                std::cout << "Player's health" << player.getHealth() << endl;
            }

            std::cout << "Please select an action: " << endl;
            std::cout << "1. Attack" << endl;
            std::cout << "2. Run" << endl;
            int choice;
            std::cin >> choice;  
            if (choice == 1){
                player.attack(enemy.get());
                std::cout << "Enemy's health after attack: " << enemy->getHealth() << endl;
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
