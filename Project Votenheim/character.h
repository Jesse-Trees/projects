#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>

struct Item {
    std::string itemName;
    std::string itemDescription;
    int quantity;
};
struct Gear
{
    std::string itemName;
    char itemType;
    int protection;
};



struct Stats {
    int xp;
    int xpCap;
    int strength;
    int speed;
    int hp;
    int hpMax;
    int mpMax;
    int mp;
    int defense;
    int intelligence;
    int level;
};

struct Move { // moves will be extracted from a file and separate everything in order
    char moveFor; // who the move is for
    std::string moveName; // name of the move
    std::string moveType; // move type (physical or magic)
    int power; // how strong the move is
    int manaCost; // how much a move costs
    std::string description; // explains the move
    
};



class Character {

    public:
        Character();
        ~Character();


        /**
         * @brief Set the Name of the character
         * 
         * @param NAME 
         */
        void setName(const std::string& NAME);

        /**
         * @brief Get the Name of the character
         * 
         * @return std::string 
         */
        std::string getName();


        void attack(Character& character, const Move& MOVE); 

        /**
         * @brief uses an item the character has in their inventory
         * 
         * @param item the item thats being used.
         */
        void useItem(Item& item);


        /**
         * @brief The character takes in a certain amount of damage
         * 
         * @param DAMAGE 
         */
        void takeDamage(const int DAMAGE);

        /**
         * @brief Puts the item inside the player's inventory
         * 
         * @param item 
         */
        void placeItem(Item& item);

        /**
         * @brief Adds the gold from the users inventory 
         * 
         * @param gold 
         */
        void addGold(int gold);

        /**
         * @brief Subtracts the gold from the users inventory
         * 
         * @param gold 
         */
        void subtractGold(int gold);

        /**
         * @brief Set the Stats object
         * 
         * @param STATS 
         */
        void setStats(const Stats& STATS);

        /**
         * @brief Get the Stats object
         * 
         * @return Stats 
         */
        Stats getStats() const;

        /**
         * @brief Get the Move List object
         * 
         * @return std::vector<Move> 
         */
        std::vector<Move> getMoveList() const;

        /**
         * @brief Set the Move List object
         * 
         * @param MOVELIST 
         */
        void setMoveList(const std::vector<Move>& MOVELIST);

        /**
         * @brief Get the Item List object
         * 
         * @return std::vector<Item> 
         */
        std::vector<Item> getItemList() const;

        /**
         * @brief Set the Item List object
         * 
         * @param ITEMLIST 
         */
        void setItemList(const std::vector<Item>& ITEMLIST);

        /**
         * @brief Sets the number of gold
         * 
         * @param GOLD 
         */
        void setGold(const int GOLD);

        /**
         * @brief Gets the number of gold
         * 
         * @return int 
         */
        int getGold();

        /**
         * @brief Set the Alive status of character
         * 
         * @param ALIVE 
         */
        void setAlive(const bool ALIVE);

        /**
         * @brief Get the Alive status of character
         * 
         * @return true if the character is alive
         * @return false if the character has been defeated
         */
        bool getAlive();

        /**
         * @brief 
         * 
         * @param PRICE 
         * @param ITEM 
         */
        void makePurchase(const int PRICE, const Item ITEM);

        /**
         * @brief The character gains an item from shop or enemy
         * 
         * @param item 
         */
        void gainItem(const Item ITEM);

        /**
         * @brief The character gains xp from enemy and checks if they have leveled up
         * 
         * @param XP 
         */
        void gainXP(const int XP);





    private:
        Stats _stat;
        std::string _name;
        std::vector<Move> _mList;
        std::vector<Item> _itemList;
        int _gold;
        bool _alive;
};












#endif