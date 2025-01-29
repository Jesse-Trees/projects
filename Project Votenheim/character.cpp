#include "character.h"
#include <iostream>
#include <cmath>

using namespace std;

Character::Character() {
    _name = "";
    _gold = 0;
    _alive = true;
}

Character::~Character() {
    
}

void Character::setName(const string& NAME) {
    _name = NAME;
}

string Character::getName() {
    return _name;
}

void Character::attack(Character& character, const Move& MOVE) {
    cout << _name << " attacks " << character.getName() << " with " << MOVE.moveName << endl;
    if(MOVE.moveType == "Physical") {
        int damage = int(1 + (MOVE.power * 0.01)) * character.getStats().strength;
        character.takeDamage(damage);
    }
    else if (MOVE.moveType == "Special" && _stat.mp >= MOVE.manaCost) {
        int damage = int(1 + (MOVE.power * 0.01)) * character.getStats().intelligence;
        _stat.mp -= MOVE.manaCost;
        character.takeDamage(damage);
    }
    else if (MOVE.moveType == "Special" && _stat.mp < MOVE.manaCost) {
        cout << "You do not have enough mana to use " << MOVE.moveName << endl;
    }
}

void Character::useItem(Item& item) {
    if(_itemList.size() == 0) {
        cout << "You do not have any items in your inventory" << endl;
    }
    else {
        cout << _name << " uses " << item.itemName << endl;
        size_t index = 0;
        for(size_t i = 0; i < _itemList.size(); i++) {
            if(_itemList.at(i).itemName == item.itemName) {
                index = i;
            }
        }
        if(item.itemName == "Small Health Potion" && _itemList.at(index).quantity > 0) {
            // health who ever uses it
            _itemList.at(index).quantity -= 1;
            _stat.hp += int(round(double(_stat.hpMax * 0.15)));
            if(_stat.hp >= _stat.hpMax) {
                _stat.hp = _stat.hpMax;
            }
            if(_itemList.at(index).quantity == 0) {
                _itemList.erase(_itemList.begin() + index);
            }
            
        }
            
        else if(item.itemName == "Small Mana Potion" && _itemList.at(index).quantity > 0) {
            // recover mana on who ever uses it
            _itemList.at(index).quantity -= 1;
            _stat.mp += int(round(double(_stat.mpMax * 0.15)));
            if(_stat.mp >= _stat.mpMax) {
                _stat.mp = _stat.mpMax;
            }
            if(_itemList.at(index).quantity == 0) {
                _itemList.erase(_itemList.begin() + index);
            }
        
        }
    }
    
}

void Character::placeItem(Item& item) {
    size_t index = 0;
    if(_itemList.size() == 0) {
        _itemList.push_back(item);
    }
    else {
        for(size_t i = 0; i < _itemList.size(); i++) {
            if(_itemList.at(i).itemName == item.itemName) {
                index = i;
            }
        }
        _itemList.at(index).quantity += 1;
    }
}

void Character::addGold(int gold) {
    _gold += gold;
}

void Character::subtractGold(int gold) {
    _gold -= gold;
}

void Character::takeDamage(const int DAMAGE) {
    _stat.hp -= round(DAMAGE * (1 - double(_stat.defense * 0.01)));
    if(_stat.hp <= 0) {
        _alive = false;
        cout << _name << " has been defeated!" << endl;
    }
}

void Character::setStats(const Stats& STATS) {
    _stat = STATS;
}

Stats Character::getStats() const {
    return _stat;
}

vector<Move> Character::getMoveList() const {
    return _mList;
}

void Character::setMoveList(const std::vector<Move>& MOVELIST) {
    _mList = MOVELIST;
}

vector<Item> Character::getItemList() const {
    return _itemList;
}

void Character::setItemList(const std::vector<Item>& ITEMLIST) {
    _itemList = ITEMLIST;
}

int Character::getGold() {
    return _gold;
}

void Character::setGold(const int GOLD) {
    _gold = GOLD;
}

void Character::setAlive(const bool ALIVE) {
    _alive = ALIVE;
}
bool Character::getAlive() {
    return _alive;
}

void Character::makePurchase(const int PRICE, const Item ITEM) {
    if(_gold < PRICE) {
        cout << "It seems you can't afford that, my friend. :(_" << endl;
    }
    else if(ITEM.quantity == 0) {
        cout << "Sorry pal, but we are out of stock." << endl;
    }
    else {
        cout << _name << " has purchased a " << ITEM.itemName << "." << endl;
        subtractGold(PRICE);
        gainItem(ITEM);
    }
}

void Character::gainItem(const Item ITEM) {
    vector<Item> newItemList = _itemList;
    size_t index;
    bool found = false;
    if(newItemList.size() == 0) {
        newItemList.push_back(ITEM);
    }
    for(size_t i = 0; i < newItemList.size(); i++) {
        if(newItemList.at(i).itemName == ITEM.itemName) {
            found = true;
            index = i;
        }
    }

    if(!found) {
        newItemList.push_back(ITEM);
    }
    else {
        newItemList.at(index).quantity += 1;
    }
    _itemList = newItemList;
}


void Character::gainXP(const int XP) {
    Stats newStat = _stat;
    newStat.xp += XP;
    if(newStat.xp >= newStat.xpCap) {
        cout << _name << " has leveled up!" << endl;
        newStat.level += 1;
        newStat.xpCap = newStat.xpCap + 3;
        newStat.xp = newStat.xp % newStat.xpCap;
        newStat.hpMax += 2;
        newStat.hp += 2;
        newStat.defense += 1;
        newStat.intelligence += 1;
        newStat.mp += 5;
        newStat.mpMax += 5;
        newStat.strength += 1;
        newStat.speed += 1;
    }
    _stat = newStat;
}


