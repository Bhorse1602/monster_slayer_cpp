
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
using namespace std;

enum class enemyType { orcType, goblinType, giantType };

class enemy{
    public:
        enemy(int health, int attackPower, enemyType type, int speed, int defense):
            health(health), attackPower(attackPower), type(type), speed(speed), defense(defense) {}
        
        virtual ~enemy() = default;
        
        string getType() const {
            if(type == enemyType::orcType)    return "Orc";
            if(type == enemyType::goblinType) return "Goblin";
            return "Giant";
        }

        int getHealth() const { return health; }
        int getAttackPower() const { return attackPower; }

        void takeDamage(int damage){
            health -= damage;
            cout << "The " << getType() << " takes " << damage << " damage!" << endl;
        }

        virtual void attack(){
            cout << "The " << getType() << " attacks with " << attackPower << " power!" << endl;
        }

        bool isAlive() const {
            return health > 0;
        }

    private:
        int health;
        int attackPower;
        enemyType type;
        int speed;
        int defense;
};

class orc: public enemy{
    public:
        orc(): enemy(100, 20, enemyType::orcType, 5, 10) {} 
};

class goblin: public enemy{
    public:
        goblin(): enemy(50, 10, enemyType::goblinType, 10, 5) {} 
};

class giant: public enemy{
    public:
        giant(): enemy(200, 30, enemyType::giantType, 2, 15) {} 
};

class enemyFactory{
    public:
        static unique_ptr<enemy> createEnemy(enemyType type){
            switch (type) {
                case enemyType::orcType:   return make_unique<orc>();
                case enemyType::goblinType: return make_unique<goblin>();
                case enemyType::giantType:  return make_unique<giant>();
            }
            return nullptr;
        }

        static unique_ptr<enemy> random_enemy(){
            int randomNum = rand() % 3;
            return createEnemy(static_cast<enemyType>(randomNum));
        }
};
