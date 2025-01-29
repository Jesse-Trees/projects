#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "area.h"
#include "hero.h"

using namespace std;

Area::Area() {
    _healthPotions.quantity = 99;
    _manaPotions.quantity = 99;
    _price = 5;
    _difficulty = 1.05;
    _areaNumber = 1;
    _healthPotions.itemName = "Small Health Potion";
    _manaPotions.itemName = "Small Mana Potion";
    _healthPotions.itemDescription = "Heals a small portion of your HP.";
    _manaPotions.itemDescription = "Recovers a small portion of your MP.";
    // The enemies needed to created in the main file to add to the list in the area
}


Area::Area(const double DIFFICULTY, const int AREANUMBER, vector<Enemy*> ENEMIES, const string AREANAME, Enemy* BIGBOSS) {
    _difficulty = DIFFICULTY;
    _areaNumber = AREANUMBER;
    _areaName = AREANAME;
    _numEnemies = ENEMIES;
    _healthPotions.quantity = 99;
    _manaPotions.quantity = 99;
    _healthPotions.itemName = "Small Health Potion";
    _manaPotions.itemName = "Small Mana Potion";
    _healthPotions.itemDescription = "Heals a small portion of your HP.";
    _manaPotions.itemDescription = "Recovers a small portion of your MP.";
    _price = 5;
    _bigBoss = BIGBOSS;
}

Area::~Area() {
    cout << "Destroying Area" << endl;
}

void Area::shop(Character& hero) {
    bool leftShop = false;
    int choice;
    cout << "Welcome to the shop! Here are the available items:" << endl;
    
    while(!leftShop) {
        cout << "1. " << _healthPotions.itemName << ": " << _healthPotions.quantity << " in stock" << endl;
        cout << "2. " << _manaPotions.itemName << ": " << _manaPotions.quantity << " in stock" << endl;
        cout << "Press '1' or '2' to purchase either item or '3' to exit the store." << endl;
        cout << "You have x" << hero.getGold() << " Gold." << endl;
        cin >> choice;
        if(choice == 1) {
            hero.makePurchase(_price, _healthPotions);
            _healthPotions.quantity -= 1;
        }
        else if(choice == 2) {
            hero.makePurchase(_price, _manaPotions);
            _manaPotions.quantity -= 1;
        }
        else {
            leftShop = true;
            cout << "Thanks! Come again!" << endl;
        }
    }
}

void Area::forest() {
    // bool winner;
    cout << "Entering the forest..." << endl;
    if(_numEnemies.size() == 0) {
        cout << "Looks like you found the " << _bigBoss->getName() <<  "." << endl;
    }
    else if (_numEnemies.size() > 0) {
        cout << "Looks like you found an " << _numEnemies.at(0)->getName() << ". Engarde!!" << endl;
    }
    else {
        cout << "There seems to be no enemies around the area" << endl;
    }

    // if(winner == true && _numEnemies.size() > 0) {
    //     cout << "Horraayyyyyyy, " << hero.getName() << " has defeated " << _numEnemies.at(0).getName() << "!" << endl;
    //     _numEnemies.erase(_numEnemies.begin());
    //     return true; 
    // }

    // else if(winner == true && _bigBoss.getAlive() == false) {
    //     _bigBoss.setAlive(false);
    //     return true;
    // }

    // else if(winner == false && _numEnemies.size() > 0) {
    //     cout << "OOOOOOHHHHHHH NOOOOOOOO, " << hero.getName() << " has tooken deFEETed by " << _numEnemies.at(0).getName() << "!" << endl;
    //     return false;
    // }
    // else if(winner == false && _bigBoss.getAlive() == true) {
    //     cout << "OOOOOOHHHHHHH NOOOOOOOO, " << hero.getName() << " has tooken deFEETed by " << _bigBoss.getName() << "!" << endl;
    //     return false;
    // }
    // else {
    //     cout << "OOOOOOHHHHHHH NOOOOOOOO, " << hero.getName() << " has tooken deFEETed by " << _numEnemies.at(0).getName() << "!" << endl;
    //     return false;
    // }
}

void Area::fight(Character& hero, Enemy* cEnemy) {
    srand(time(0));
    int turn = 0;
    Enemy* currEnemy = cEnemy;
    vector<Move> currMoveSet = hero.getMoveList();
    vector<Item> currItems = hero.getItemList();
    cout << currEnemy->getAlive() << endl;
    cout << hero.getAlive() << endl;
    while(currEnemy->getAlive() == true || hero.getAlive() == true) {
        cout << "we are in the scene" << endl;
        if(turn % 2 == 0) { // It is the player's turn
            int choice;
            cout << "What will you do player? '1' to fight, or '2' to use item" << endl;
            cout << "Your HP: " << hero.getStats().hp << " / " << hero.getStats().hpMax << endl;
            cout << "Your MP: " << hero.getStats().mp << " / " << hero.getStats().mpMax << endl;
            cout << endl;
            cout << currEnemy->getName() << "'s HP: " << currEnemy->getStats().hp << " / " << currEnemy->getStats().hpMax << endl;
            cout << currEnemy->getName() << "'s MP: " << currEnemy->getStats().mp << " / " << currEnemy->getStats().mpMax << endl;
            cin >> choice;
            if(choice == 1) {
                int moveChoice;
                cout << "Select which move you would like to use: ('1', '2', '3', '4')" << endl;
                for(size_t i = 1; i < currMoveSet.size() + 1; i++) {
                    cout << i << ": " << currMoveSet.at(i-1).moveName << "  Power: " << currMoveSet.at(i-1).power << "  Mana Cost: " << currMoveSet.at(i-1).manaCost << "   Description: " << currMoveSet.at(i-1).description << endl; 
                }
                cin >> moveChoice;
                if(moveChoice == 1) {
                    hero.attack(*currEnemy, currMoveSet.at(0));
                }
                else if(moveChoice == 2) {
                    hero.attack(*currEnemy, currMoveSet.at(1));
                }
                else if(moveChoice == 3) {
                    hero.attack(*currEnemy, currMoveSet.at(2));
                }
                else if(moveChoice == 4) {
                    hero.attack(*currEnemy, currMoveSet.at(3));
                }
                else {
                    cout << "It seems like the hero is in some confusion! That's not good" << endl;
                }
            }

            else if(choice == 2) {
                if(currItems.size() == 0) {
                    cout << "Looks like you don't have any items there buddy. :(" << endl;
                }
                else {
                    int itemChoice;
                    cout << "Select which item you would like to use: ('1' or '2')" << endl;
                    for(size_t i = 1; currItems.size() + 1; i++) {
                        cout << i << ": " << currItems.at(i-1).itemName << " x" << currItems.at(i-1).quantity << "  Description: " << currItems.at(i-1).itemDescription << endl;
                    }
                    cin >> itemChoice;
                    if((itemChoice == 1 && currItems.size() == 1) || (itemChoice == 1 && currItems.size() > 1)) {
                        hero.useItem(currItems.at(0));
                    }
                    else if(itemChoice == 2 && currItems.size() == 2) {
                        hero.useItem(currItems.at(1));
                    }
                    else {
                        cout << "Oh no, the hero is confused! That's not good" << endl;
                    }
                    
                }
            }
            turn++;
        }
            
        else { // It is the enemy's turn
            // The enemy uses a random attack from its choices
            int enemyChoice = rand() % 4;
            Move moveSelected;
            if(enemyChoice == 0) {
                moveSelected = currEnemy->getMoveList().at(0);
                cout << "Looks like the " << currEnemy->getName() << " is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            else if(enemyChoice == 1) {
                moveSelected = currEnemy->getMoveList().at(1);
                cout << "Looks like the " << currEnemy->getName() << " is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            else if(enemyChoice == 2) {
                moveSelected = currEnemy->getMoveList().at(2);
                cout << "Looks like the " << currEnemy->getName() << " is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            else {
                moveSelected = currEnemy->getMoveList().at(3);
                cout << "Looks like the " << currEnemy->getName() << " is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            turn++;
        }
    }
    
    if(currEnemy->getAlive() == false && hero.getAlive() == true) {
        cout << "You defeated a " << currEnemy->getName() << endl;
        Item itemChance = currEnemy->dropItem();
        int xp = currEnemy->dropXP();
        hero.gainXP(xp);
        if(itemChance.itemName != "None") {
            cout << currEnemy->getName() << " dropped an item: " << itemChance.itemName << endl;
            hero.gainItem(itemChance);
        }
        // return true;
    }
    else if (currEnemy->getAlive() == true && hero.getAlive() == false)
    {
       cout << "You have been deFEETed by a " << currEnemy->getName()<< endl; 
    }
    else{
        cout << "It seems " << hero.getName() <<" cannot make it to the fight. We have skipped the fight so im gonna steal your pancreas" << endl;
    }

}

void Area::fightBoss(Character& hero) {
    srand(time(0));
    int turn = 0;
    Enemy* currEnemy = _bigBoss;
    vector<Move> currMoveSet = hero.getMoveList();
    vector<Item> currItems = hero.getItemList();
    while(currEnemy->getAlive() == false || hero.getAlive() == false) {
        
        if(turn % 2 == 0) { // It is the player's turn
            int choice;
            cout << "What will you do player? '1' to fight, or '2' to use item" << endl;
            cin >> choice;
            if(choice == 1) {
                int moveChoice;
                cout << "Select which move you would like to use: ('1', '2', '3', '4')" << endl;
                for(size_t i = 1; i < currMoveSet.size() + 1; i++) {
                    cout << i << ": " << currMoveSet.at(i-1).moveName << "  Power: " << currMoveSet.at(i-1).power << "  Mana Cost: " << currMoveSet.at(i-1).manaCost << "   Description: " << currMoveSet.at(i-1).description << endl; 
                }
                cin >> moveChoice;
                if(moveChoice == 1) {
                    hero.attack(*currEnemy, currMoveSet.at(0));
                }
                else if(moveChoice == 2) {
                    hero.attack(*currEnemy, currMoveSet.at(1));
                }
                else if(moveChoice == 3) {
                    hero.attack(*currEnemy, currMoveSet.at(2));
                }
                else if(moveChoice == 4) {
                    hero.attack(*currEnemy, currMoveSet.at(3));
                }
                else {
                    cout << "It seems like the hero is in some confusion! That's not good" << endl;
                }
            }

            else if(choice == 2) {
                if(currItems.size() == 0) {
                    cout << "Looks like you don't have any items there buddy. :(" << endl;
                }
                else {
                    int itemChoice;
                    cout << "Select which item you would like to use: ('1' or '2')" << endl;
                    for(size_t i = 1; currItems.size() + 1; i++) {
                        cout << i << ": " << currItems.at(i-1).itemName << " x" << currItems.at(i-1).quantity << "  Description: " << currItems.at(i-1).itemDescription << endl;
                    }
                    cin >> itemChoice;
                    if((itemChoice == 1 && currItems.size() == 1) || (itemChoice == 1 && currItems.size() > 1)) {
                        hero.useItem(currItems.at(0));
                    }
                    else if(itemChoice == 2 && currItems.size() == 2) {
                        hero.useItem(currItems.at(1));
                    }
                    else {
                        cout << "Oh no, the hero is confused! That's not good" << endl;
                    }
                    
                }
            }
            turn++;
        }
            
        else { // It is the enemy's turn
            // The enemy uses a random attack from its choices
            int enemyChoice = rand() % 4;
            Move moveSelected;
            if(enemyChoice == 0) {
                moveSelected = currEnemy->getMoveList().at(0);
                cout << "Looks like the " << currEnemy->getName() << "is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            else if(enemyChoice == 1) {
                moveSelected = currEnemy->getMoveList().at(1);
                cout << "Looks like the " << currEnemy->getName() << "is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            else if(enemyChoice == 2) {
                moveSelected = currEnemy->getMoveList().at(2);
                cout << "Looks like the " << currEnemy->getName() << "is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            else {
                moveSelected = currEnemy->getMoveList().at(3);
                cout << "Looks like the " << currEnemy->getName() << "is going to use " << moveSelected.moveName << "." << endl;
                currEnemy->attack(hero, moveSelected);
            }
            turn++;
        }
    }
    if(currEnemy->getAlive() == false && hero.getAlive() == true) {
        cout << "Congratulations!!! Yuusha-sama!" << endl;
        Item itemChance = currEnemy->dropItem();
        int xp = currEnemy->dropXP();
        hero.gainXP(xp);
        if(itemChance.itemName != "None") {
            cout << currEnemy->getName() << " dropped an item: " << itemChance.itemName << endl;
            hero.gainItem(itemChance);
        
        }
        // return true;
    }
    else if(currEnemy->getAlive() == true && hero.getAlive() == false){
        cout << "L bozo" << endl;
        // return false;
    }

}

string Area::getAreaName() {
    return _areaName;
}

void Area::setAreaName(const string AREANAME) {
    _areaName = AREANAME;
}

int Area::getAreaNumber() {
    return _areaNumber;
}

void Area::setAreaNumber(const int AREANUMBER) {
    _areaNumber = AREANUMBER;
}

double Area::getAreaDifficulty() {
    return _difficulty;
}

void Area::setAreaDifficulty(const double DIFFICULTY) {
    _difficulty = DIFFICULTY;
}

void Area::setEnemyList(const vector<Enemy*>& ENEMIES) {
    _numEnemies = ENEMIES;
}

vector<Enemy*> Area::getEnemyList() {
    return _numEnemies;
}

void Area::setBigBoss(Enemy* BIGBOSS) {
    _bigBoss = BIGBOSS;
}

Enemy* Area::getBigBoss() {
    return _bigBoss;
}

void Area::setPrice(const int PRICE) {
    _price = PRICE;
}

int Area::getPrice() {
    return _price;
}