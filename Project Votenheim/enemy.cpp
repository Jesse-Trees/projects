#include <iostream>
#include "enemy.h"
#include <cstdlib>
#include <ctime>
#include <vector>


using namespace std;


Enemy::Enemy() {

}

Enemy::Enemy(Stats& enemyStat, std::vector<Move>& moveList, int gold, string name) {
    this->setStats(enemyStat);
    this->setMoveList(moveList);
    this->setGold(gold);
    this->setName(name);
    this->setAlive(true);
}

Enemy::~Enemy() {
    cout << "Destroying Enemy" << endl;
}

int Enemy::dropXP() {
    srand(time(0));
    int xp = getStats().level * (rand() % 4 + 1);
    return xp;
}

Item Enemy::dropItem() {
    srand(time(0));
    int chance = rand() % 10;
    if(chance == 0) {
        Item healthPotion;
        healthPotion.itemName = "Small Health Potion";
        healthPotion.quantity = 1;
        healthPotion.itemDescription = "Heals a small portion of your HP.";
        return healthPotion;
    }
    else if(chance == 1) {
        Item manaPotion;
        manaPotion.itemName = "Small Mana Potion";
        manaPotion.quantity = 1;
        manaPotion.itemDescription = "Recovers a small portion of your MP.";
        return manaPotion;
    }
    else {
        Item noItem;
        noItem.quantity = 0;
        noItem.itemDescription = "No item dropped";
        noItem.itemName = "None";
        return noItem;
    }
}