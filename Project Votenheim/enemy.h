#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

class Enemy : public Character {
    public:
        Enemy();
        Enemy(Stats& enemyStat, std::vector<Move>& moveList, int gold, std::string name);

        ~Enemy();
    

        /**
         * @brief Enemy drops a specific amount of xp based on their level
         * 
         * @return int 
         */
        int dropXP();

        /**
         * @brief The enemy has a 20% chance to drop an item.
         * 
         * @return Item 
         */
        Item dropItem();

    private:


};





#endif