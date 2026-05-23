#include "enemy_factory.h"
class player_{
    int health;
    int attackPower;
public:
    player_(): health(150), attackPower(25) {}

    int getHealth() const { return health; }

    void attack(enemy* target){
        std::cout << "Player attacks with " << attackPower << " power!" << endl;
        target->takeDamage(attackPower);
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int damage){
        health -= damage;
        std::cout << "Player takes " << damage << " damage!" << endl;
    }
};