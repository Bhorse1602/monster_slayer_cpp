#pragma once
/*pragma once is used to prevent multiple inclusions of the same header file*/
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <functional>
#include "observer.h"

#define CONCAT(a, b) a##b
#define APPEND_TYPE(x) CONCAT(x, Type)

#define REGISTER_ENEMY(Type) \
    namespace { \
        automatic_registration<Type> reg_instance_##Type(enemyType::APPEND_TYPE(Type)); \
    }
    enum class enemyType {
     orcType,
     goblinType, 
     giantType,
        VampireKingNebulaType
    };

class enemy; // Forward declaration of enemy class
class enemyFactory; // Forward declaration of enemyFactory class


class enemy:public subject{
    public:
        enemy(int health, int attackPower, enemyType type, int speed, int defense):
            health(health), attackPower(attackPower), type(type), speed(speed), defense(defense) {}
        
        virtual ~enemy() = default;
        
        std::string getType() const {
            if(type == enemyType::orcType)    return "Orc";
            if(type == enemyType::goblinType) return "Goblin";
            if(type == enemyType::giantType) return "Giant";
            if(type == enemyType::VampireKingNebulaType) return "Vampire King Nebula";
            return "Unknown";
        }

        int getHealth() const { return health; }
        int getAttackPower() const { return attackPower; }

        void takeDamage(int damage)
        {
            health -= damage;
            if (health < 0)
                health = 0;

            notify("ENEMY_DAMAGE", damage, getType());

            if (health <= 0)
            {
                notify("ENEMY_DEATH", 0, getType());
            }
        }

        virtual void attack(){
            std::cout << "The " << getType() << " attacks with " << attackPower << " power!" << std::endl;
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
class VampireKingNebula: public enemy{
    public:
        VampireKingNebula(): enemy(300, 50, enemyType::VampireKingNebulaType, 30, 30) {} 
        void attack() override {
            std::cout << "The " << getType() << " unleashes a devastating cosmic attack with " << getAttackPower() << " power!" << std::endl;
        }
    };
class enemyFactory{
       /* using Creator = unique_ptr<enemy>(*)(); 
       This is a function pointer type */
    private:  
        // C++11 lambda functions can be used as creators, so we use std::function instead of raw function pointers.
        using creator = std::function<std::unique_ptr<enemy>()>; 
        //There is only one copy of registry for the entire program, so we can make it static.
        static inline std::unordered_map<enemyType, creator> registry;
    public:

    static void register_enemy(enemyType type, creator create){
        /*std::move is used here as a way to transfer ownership of the lambda function to std::unordered_map 
        std::move(creator) tells the compiler: "I don't need this creator object anymore after this line. You can steal its resources."
        This allows the assignment to move the internal state of the std::function into the map instead of copying it.
        */
        registry[type] = std::move(create);
    }
    static std::unique_ptr<enemy> create_boss(){
        return create_enemy(enemyType::VampireKingNebulaType);
    }
    
    static std::unique_ptr<enemy> create_enemy(enemyType type){
        auto it = registry.find(type);
        if (it != registry.end()){
            return (it->second)(); // Call the creator function to create an enemy
        }
        std::cout << "Enemy type not registered!" << std::endl;
        return nullptr; // Return nullptr if the type is not registered
    }

    static std::unique_ptr<enemy> random_enemy(){
        if (registry.empty()) {
            std::cout << "No enemies registered!" << std::endl;
            return nullptr;
        }

        // Only normal enemies for random spawns (Exclude Boss)
        std::vector<enemyType> normalEnemies = {
            enemyType::orcType,
            enemyType::goblinType,
            enemyType::giantType
        };

        int randNum = rand() % normalEnemies.size();
        enemyType selectedType = normalEnemies[randNum];

        return create_enemy(selectedType);
    }
    static void deregister_enemy (enemyType type){
        registry.erase(type);
    }
};

template<typename T>
class automatic_registration{
    public:
    //Constructor that takes an enemyType and registers the corresponding enemy class with the factory
    automatic_registration(enemyType type){
        //This behaviour is similar to a static initializer, it runs before main() starts, 
        //ensuring that the enemy types are registered before they are used.
        enemyFactory::register_enemy(type, []() -> std::unique_ptr<enemy> {
            return std::make_unique<T>();
        });
    }
};
// Auto Registration
REGISTER_ENEMY(orc)
REGISTER_ENEMY(goblin)
REGISTER_ENEMY(giant)
REGISTER_ENEMY(VampireKingNebula)