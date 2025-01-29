#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cmath>

#include "character.h"
#include "hero.h"
#include "enemy.h"
#include "area.h"

using namespace std;


Stats makeRandomStat(const int AREA_NUMBER, const double AREA_DIFFICULTY ) {
    srand(time(0));
    Stats randomStat;
    randomStat.level = round((rand() % 3 + 1 + AREA_NUMBER) * AREA_DIFFICULTY); // level influences the random stats on the enemy
    randomStat.hpMax = round((double(rand()/ RAND_MAX) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY); // level affects the hp and hpmax is rand over randmax
    randomStat.hp = randomStat.hpMax;
    randomStat.defense = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.intelligence = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.strength = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.speed = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.xp = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.mpMax = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.mp = randomStat.mpMax;
    randomStat.xpCap = randomStat.xp + 1;
    return randomStat;
}
Stats makeRandomStatForBoss(const int AREA_NUMBER, const double AREA_DIFFICULTY) {
    srand(time(0));
    Stats randomStat;
    randomStat.level = round((rand() % 3 + 6 + AREA_NUMBER) * AREA_DIFFICULTY); // level influences the random stats on the enemy
    randomStat.hpMax = round((double(rand()/ RAND_MAX) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY); // level affects the hp and hpmax is rand over randmax
    randomStat.hp = randomStat.hpMax;
    randomStat.defense = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.intelligence = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.strength = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.speed = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.xp = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.mpMax = round((double(rand() % 2) + randomStat.level + AREA_NUMBER) * AREA_DIFFICULTY);
    randomStat.mp = randomStat.mpMax;
    randomStat.xpCap = randomStat.xp + 1;
    return randomStat;
}
vector<Move> filterMoves(string fileName, char occupation) {
    vector<Move> moves;
    ifstream fin(fileName);
    if(fin.is_open()) {
        string line;
        getline(fin, line);
        while(getline(fin, line)) {
            stringstream ss(line);
            string moveType;
            getline(ss, moveType, ',');
            if (moveType[0] == occupation || moveType[0] == 'E') {
                Move move;
                move.moveFor = moveType[0];
                getline(ss, move.moveName, ',');
                getline(ss, move.moveType, ',');
                ss >> move.power;
                ss.ignore(1);
                ss >> move.manaCost;
                ss.ignore(1);
                getline(ss, move.description);
                moves.push_back(move);
            }
        }
        fin.close();
    }
    return moves;
}

int main() {
    srand(time(0));
    const int areaNumber = 1;
    const double areaDifficulty = 1.0;
    vector<Move> enemyMoves;
    Move enemyMove1;
    Move enemyMove2;
    Move enemyMove3;
    Move enemyMove4;
    enemyMove1.moveName = "Scratch";
    enemyMove2.moveName = "Tackle";
    enemyMove3.moveName = "Slash";
    enemyMove4.moveName = "Headbutt";
    enemyMove1.power = 20;
    enemyMove2.power = 35;
    enemyMove3.power = 50;
    enemyMove4.power = 40;
    enemyMove1.manaCost = 0;
    enemyMove2.manaCost = 0;
    enemyMove3.manaCost = 0;
    enemyMove4.manaCost = 0;
    enemyMove1.moveType = "Physical";
    enemyMove2.moveType = "Physical";
    enemyMove3.moveType = "Physical";
    enemyMove4.moveType = "Physical";
    enemyMove1.moveFor = 'E';
    enemyMove2.moveFor = 'E';
    enemyMove3.moveFor = 'E';
    enemyMove4.moveFor = 'E';
    enemyMove1.description = "Small cuts with the fingers";
    enemyMove2.description = "A powerful charge with the body";
    enemyMove3.description = "A powerful sword slash.";
    enemyMove4.description = "A powerful charge with the head forward.";
    enemyMoves.push_back(enemyMove1);
    enemyMoves.push_back(enemyMove2);
    enemyMoves.push_back(enemyMove3);
    enemyMoves.push_back(enemyMove4);
    vector<Enemy*> enemyList;
    for(int i = 0; i < 10; i++) { // Creates 10 random enemies
        Stats enemyStat;
        enemyStat = makeRandomStat(areaNumber, areaDifficulty);
        int gold = rand() % 4 + 1;
        Enemy* brainCells = new Enemy(enemyStat, enemyMoves, gold, "Goblin");
        enemyList.push_back(brainCells);
    }
    string name;
    char occupation;
    
    Stats bigBossStat = makeRandomStat(areaNumber, areaDifficulty);
    Enemy* bigBoss = new Enemy(bigBossStat, enemyMoves, 999, "Goblin General");
    Area firstArea(areaDifficulty, areaNumber, enemyList, "Area 1", bigBoss);

    cout << "Welcome Player to the World of Vohtenheim" << endl;
    cout << "Please name your hero!" << endl;
    cin >> name;
    bool isSatisfied = false;
    cout << "Please select your Occupation, (S)wordsmen or (M)age: ";
    while(!isSatisfied) {
        cin >> occupation;
        occupation = toupper(occupation);
        if(occupation == 'S' || occupation == 'M') {
            isSatisfied = true;
        }
        else {
            cout << "Invalid Response! Please type in S for Swordsmen or M for Mage." << endl;
        }
    }
    cout << "Please select your 4 moves." << endl;

    // Hero protagonist;
    string moveFile = "data/moveData.csv";
    // bool satisfied = false; // we want to know if the user is satisfied with his selection of moves
    vector<Move> movesSelected;
    vector<Move> moveOptions = filterMoves(moveFile, occupation);
    // while(!satisfied) {
        
    // }
    for(size_t i = 0; i < moveOptions.size(); i++) {
        cout << i + 1 << ". " << moveOptions.at(i).moveName << " (" << moveOptions.at(i).moveType << ", " << moveOptions.at(i).power << ", " << moveOptions.at(i).manaCost << ", " << moveOptions.at(i).description << ")" << endl;  
    }
    while (movesSelected.size() < 4) {
        cout << "Select a move (enter the number): ";
        size_t selection;
        cin >> selection;

        if (selection >= 1 && selection <= moveOptions.size()) {
            movesSelected.push_back(moveOptions[selection - 1]);
            cout << "Move '" << moveOptions.at(selection - 1).moveName << "' selected." << endl;
        } else {
            cout << "Invalid selection. Please try again." << endl;
        }
    }
    cout << "Moves selected:" << endl;
    for (const auto& move : movesSelected) {
        cout << move.moveName << " (" << move.moveType << ")" << endl;
    }


    Hero protagonist;
    protagonist.setAlive(true);
    protagonist.setGold(25);
    protagonist.setMoveList(movesSelected);
    protagonist.setName(name);
    protagonist.setOccupation(occupation);
    cout << protagonist.getStats().hpMax << endl;
    while(bigBoss->getAlive() == true) {
        // bool heroAlive = true;
        cout << "What would you like to do?" << endl;
        cout << "1. Go to the forest" << endl;
        cout << "2. Go to the shop" << endl;
        cout << "Enter your choice; ('1' or '2')" << endl;
        int choice;
        cin >> choice;
        if(choice == 1) {
            firstArea.forest();
            firstArea.fight(protagonist, enemyList.at(0));
            if(protagonist.getAlive() == false) {
                break;
            }
        }
        else if(choice == 2) {
            firstArea.shop(protagonist);
        }
        else {
            cout << "It appears there has been some confusion from " << protagonist.getName() << ". Please give us an appropriate input." << endl;
        }

    }

    if(protagonist.getAlive() == false) {
        cout << "Who will defeat the EEEEEeeeeeevvviiiiiiiillllllllll now?" << endl;
    }

    else if(protagonist.getAlive() == true) {

        cout << "Congratulations, " << protagonist.getName() << "!!! You defeated the first boss!" << endl;
        cout << "Remember, this is only the beginning of your journey to save Vohtenheim." << endl;
        cout << "Tune in next time with our hero " << protagonist.getName() << endl;
    }
    else {
        cout << "Confusion" << endl;
    }

    return 0;

}