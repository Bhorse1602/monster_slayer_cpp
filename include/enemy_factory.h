
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <functional>
using namespace std;

#define CONCAT(a, b) a##b
#define APPEND_TYPE(x) CONCAT(x, Type)

#define REGISTER_ENEMY(Type) \
    namespace { \
        automatic_registration<Type> reg_instance_##Type(enemyType::APPEND_TYPE(Type)); \
    }
    enum class enemyType {
     orcType,
     goblinType, 
     giantType 
    };

class enemy; // Forward declaration of enemy class
class enemyFactory; // Forward declaration of enemyFactory class


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
            std::cout << "The " << getType() << " takes " << damage << " damage!" << endl;
        }

        virtual void attack(){
            std::cout << "The " << getType() << " attacks with " << attackPower << " power!" << endl;
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
       /* using Creator = unique_ptr<enemy>(*)(); 
       This is a function pointer type */
    private:  
        // C++11 lambda functions can be used as creators, so we use std::function instead of raw function pointers.
        using creator = std::function<unique_ptr<enemy>()>; 
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

    static unique_ptr<enemy> create_enemy(enemyType type){
        auto it = registry.find(type);
        if (it != registry.end()){
            return (it->second)(); // Call the creator function to create an enemy
        }
        std::cout << "Enemy type not registered!" << endl;
        return nullptr; // Return nullptr if the type is not registered
    }
    static unique_ptr<enemy> random_enemy(){
        if (registry.empty()){
            std::cout << "No enemies registered!" << endl;
            return nullptr;
        }
        vector<enemyType> types;
        for(const auto& pair : registry){
            types.push_back(pair.first);
        }
        int randNum = rand() % types.size(); // Generate a random number between 0 and the size of the types vector
        enemyType type = types[randNum]; // Select a random enemy type
        return create_enemy(type); // Create and return a random enemy
    }
    static void deregister_enemy (enemyType type){
        registry.erase(type);
    }
};

template<typename T>
class automatic_registration{
    public:
    automatic_registration(enemyType type){
        enemyFactory::register_enemy(type, []() -> unique_ptr<enemy> {
            return make_unique<T>();
        });
    }
};