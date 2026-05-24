#pragma once

#include "enemy_factory.h"
class player_:public subject 
{
    int health;
    int attackPower;
    int maxHealth;
    int potions;
public:
    player_(): health(200), attackPower(25), maxHealth(200), potions(5) {}

    int getHealth() const { return health; }
    int getAttackPower() const { return attackPower; }  
    int getPotions() const { return potions; }  
    int getMaxHealth() const { return maxHealth; }
    void usePotion(){
        if(potions > 0){
            health += 50;
            if(health > maxHealth) health = maxHealth;
            potions--;
            std::cout << "Player uses a potion and restores health! Current health: " << health << std::endl;
            notify("potion_used", health, "player");
        }
        else{
            std::cout << "No potions left!" << std::endl;
        }
    }
    void levelUp(){
        attackPower += 10;
        maxHealth += 20;
        health = maxHealth; // Restore health to max on level up
        std::cout << "Player levels up! Attack power and max health increased!" << std::endl;
        notify("level_up", attackPower, "player");
    }

    void attack(enemy* enemy_){
        std::cout << "Player attacks with " << attackPower << " power!" << std::endl;
        enemy_->takeDamage(attackPower);
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int damage){
        health -= damage;
        if(health<=0){
            health = 0;
            notify("player_defeated", 0, "player");
            std::cout << "Player has been defeated!" << std::endl;
        }
        std::cout << "Player takes " << damage << " damage!" << std::endl;
        notify("health_changed", health, "player");
        
    }
};