#include "hero.h"
#include <vector>
#include <iostream>

using namespace std;

Hero::Hero() {
    _occupation = ' ';
}

Hero::Hero(const string NAME, const char OCCUPATION, const vector<Move>& MOVELIST, const vector<Item>& ITEMLIST) {
    this->setName(NAME);
    this->setAlive(true);
    _occupation = OCCUPATION;
    this->setMoveList(MOVELIST);
    this->setItemList(ITEMLIST);
    this->addGold(25);
    if(_occupation == 'S') {
        Stats hStats;
        hStats.hpMax = 30;
        hStats.hp = hStats.hpMax;
        hStats.defense = 8;
        hStats.speed = 7;
        hStats.intelligence = 5;
        hStats.strength = 10;
        hStats.xp = 0;
        hStats.xpCap = 25 + (hStats.level);
        hStats.mpMax = 80;
        hStats.mp = hStats.mpMax;
        hStats.level = 5;
        this->setStats(hStats);
    }
    else {
        Stats hStats;
        hStats.hpMax = 30;
        hStats.hp = hStats.hpMax;
        hStats.defense = 6;
        hStats.speed = 6;
        hStats.intelligence = 10;
        hStats.strength = 8;
        hStats.xp = 0;
        hStats.xpCap = 25 + (hStats.level);
        hStats.mpMax = 120;
        hStats.mp = hStats.mpMax;
        hStats.level = 5;
        this->setStats(hStats);

    }
    // set up stats based on occupation;
}

Hero::~Hero(){
    cout << "Deleting Hero" << endl;
}

void Hero::setOccupation(const char OCCUPATION){
    _occupation = OCCUPATION;
}
char Hero::getOccupation() {
    return _occupation;
}

