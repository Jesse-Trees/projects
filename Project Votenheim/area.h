#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "enemy.h"


class Area {
    public:
        /**
         * @brief Construct a new Area object
         * 
         */
        Area();

        ~Area();
    


        Area(const double DIFFICULTY, const int AREANUMBER, std::vector<Enemy*> ENEMIES, const std::string AREANAME, Enemy* BIGBOSS);


        /**
         * @brief Lets the user go to a shop and purchase items and prints out how many the shop has and how much it costs.
         * 
         */
        void shop(Character& hero);

        /**
         * @brief Users goes to the forest to either encounter an enemy or a big boss depending on certain conditions
         * 
         * 
         */
        void forest();


        /**
         * @brief User goes to the forest to encounter an enemy
         * 
         * 
         */
        void fight(Character& hero, Enemy* cEnemy);

        /**
         * @brief User fights the boss after defeating all the enemies in the area
         * 
         * @return returns true if hero won the fight or false if the hero loses the fight
         */
        void fightBoss(Character& hero);


        /**
         * @brief Get the Area Name object
         * 
         * @return string 
         */
        std::string getAreaName();

        /**
         * @brief Set the Area Name object
         * 
         * @param AREANAME 
         */
        void setAreaName(const std::string AREANAME);

        /**
         * @brief Get the Area Number object
         * 
         * @return int 
         */
        int getAreaNumber();

        /**
         * @brief Set the Area Number object
         * 
         * @param AREANUMBER 
         */
        void setAreaNumber(const int AREANUMBER);

        /**
         * @brief Get the Area Difficulty object
         * 
         * @return double 
         */
        double getAreaDifficulty();

        /**
         * @brief Set the Area Difficulty object
         * 
         * @param DIFFICULTY 
         */
        void setAreaDifficulty(const double DIFFICULTY);

        /**
         * @brief Set the Enemy List object
         * 
         * @param ENEMYLIST 
         */
        void setEnemyList(const std::vector<Enemy*>& ENEMIES);

        /**
         * @brief Get the Enemy List object
         * 
         * @return std::vector<Enemy> 
         */
        std::vector<Enemy*> getEnemyList();

        /**
         * @brief Set the Big Boss object
         * 
         * @param BIGBOSS 
         */
        void setBigBoss(Enemy* BIGBOSS);

        /**
         * @brief Get the Big Boss object
         * 
         * @return Enemy 
         */
        Enemy* getBigBoss();

        /**
         * @brief Set the Price of the items
         * 
         * @param PRICE 
         */
        void setPrice(const int PRICE);

        /**
         * @brief Get the Price of the items
         * 
         * @return int 
         */
        int getPrice();



    private:
        std::vector<Enemy*> _numEnemies;
        double _difficulty;
        Item _healthPotions;
        Item _manaPotions;
        std::string _areaName;
        int _areaNumber;
        Enemy* _bigBoss;
        int _price;


};







#endif