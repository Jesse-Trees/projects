#ifndef HERO_H
#define HERO_H

#include "character.h"


class Hero : public Character {
    public:
        /**
         * @brief Construct a new Hero object with 25 gold
         * 
         */
        Hero();

        /**
         * @brief Construct a new Hero object with stats based on their occupation, Mage or Swordsmen
         * 
         * @param name 
         * @param occupation 
         * @param moveList 
         * @param itemList 
         */
        Hero(const std::string NAME, const char OCCUPATION, const std::vector<Move>& MOVELIST, const std::vector<Item>& ITEMLIST);

        ~Hero();


        /**
         * @brief Set the Occupation of the 
         * 
         * @param OCCUPATION 
         */
        void setOccupation(const char OCCUPATION);

        /**
         * @brief Get the Occupation character
         * 
         * @return char 
         */
        char getOccupation();


        

    private:
        char _occupation;
        

};

#endif