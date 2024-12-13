#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "item.h"
using namespace std;

class Character
{
protected:
    string name;
    int level;
    double atk;
    double critDmg;
    double critChance;
    double agility;
    double defense;
    double hp;

public:
    // getters
    string getName() const;
    double getAtk() const;
    double getCritDmg() const;
    double getCritChance() const;
    double getAgility() const;
    double getDefense() const;
    double getHP() const;

    void hit(double dmg); // character gets hit
    virtual void printInfo() = 0;
};

string Character::getName() const { return this->name; }
double Character::getAtk() const { return this->atk; }
double Character::getCritDmg() const { return this->critDmg; }
double Character::getCritChance() const { return this->critChance; }
double Character::getAgility() const { return this->agility; }
double Character::getDefense() const { return this->defense; }
double Character::getHP() const { return hp; }

void Character::hit(double dmg)
{
    this->hp = max(this->hp - dmg, 0.0);
}

////////////////////////////////////////////////////////////////////

class Player : public Character
{
protected:
    vector<Item> handsOn; // Possessed item list

public:
    Player(string name);
    ~Player();
    void printInfo(); // Print player info
    int getItemCnt(); // Get Possessed item count
    void printPossessedItem(int index); // Print info of the possessed item
    void addValues(double atk, double critDmg, double critChance, double agility, double defense, double hp); // Add to player's values for type 3 item
    void equipItem(vector<Item> vec, int id); // Add to item list if type 1 or 2, Add to player's values if type 3
    void useItem(int index); // Temporarily add to player's values for type 1 and 2 item
    void nullifyItem(int index); // Remove item effect, also remove item if type 1
    void levelUp(); // Level up with Improvement
};

Player::Player(string name)
{
    this->name = name;
    this->atk = 10;
    this->critDmg = atk * 2;
    this->critChance = 0.1;
    this->agility = 10;
    this->defense = 10;
    this->hp = 200;
    this->level = 1;
}

Player::~Player()
{
}

void Player::printInfo()
{
    cout << reverseColorStart(7) << "PLAYER" << colorEnd << "  Lv. " << this->level << "  " << this->name << endl;
    cout << "  ATK: " << this->atk << endl;
    cout << "  Crit Damage: " << this->critDmg << endl;
    cout << "  Crit Chance: " << this->critChance * 100 << "%" << endl;
    cout << "  Agility: " << this->agility << endl;
    cout << "  Defense: " << this->defense << endl;
    cout << "  HP: " << this->hp << endl;
}

int Player::getItemCnt()
{
    return this->handsOn.size();
}

void Player::printPossessedItem(int index)
{
    this->handsOn[index].printInfo();
}

void Player::addValues(double atk, double critDmg, double critChance, double agility, double defense, double hp)
{
    this->atk += atk;
    this->critDmg += critDmg;
    this->critChance += critChance;
    this->agility += agility;
    this->defense += defense;
    this->hp += hp;
}

void Player::equipItem(vector<Item> vec, int id)
{
    if (vec[id].getType() != 3)
        this->handsOn.push_back(vec[id]);
    else
        this->addValues(vec[id].getAtkChange(), vec[id].getCritChange(), vec[id].getCritChanceChange(), vec[id].getAgilityChange(), vec[id].getDefenseChange(), vec[id].getHpChange());
}

void Player::useItem(int index)
{
    this->atk += handsOn[index - 1].getAtkChange();
    this->critDmg += handsOn[index - 1].getCritChange();
    this->critChance += handsOn[index - 1].getCritChanceChange();
    this->agility += handsOn[index - 1].getAgilityChange();
    this->defense += handsOn[index - 1].getDefenseChange();
    this->hp += handsOn[index - 1].getHpChange();
}

void Player::nullifyItem(int index)
{
    this->atk -= handsOn[index - 1].getAtkChange();
    this->critDmg -= handsOn[index - 1].getCritChange();
    this->critChance -= handsOn[index - 1].getCritChanceChange();
    this->agility -= handsOn[index - 1].getAgilityChange();
    this->defense -= handsOn[index - 1].getDefenseChange();
    this->hp -= handsOn[index - 1].getHpChange();
    if (handsOn[index - 1].getType() == 1)
    {
        handsOn.erase(handsOn.begin() + index - 1);
    }
}

void Player::levelUp()
{
    cout << "[ Level up! ]" << endl;
    
    cout << "Level: " << this->level << " -> ";
    this->level += 1;
    cout << this->level << endl;
    
    cout << "Attack: " << this->atk << " -> ";
    this->atk = roundToOneDec(atk * 1.25);
    cout << this->atk << endl;
    
    cout << "Crit Damage: " << this->critDmg << " -> ";
    this->critDmg = roundToOneDec(critDmg * 1.25);
    cout << this->critDmg << endl;
    
    cout << "Crit Chance: " << this->critChance * 100 << "% -> ";
    this->critChance += 0.012;
    cout << this->critChance * 100 << "%" << endl;
    
    cout << "Agility: " << this->agility << " -> ";
    this->agility += 2;
    cout << this->agility << endl;
    
    cout << "Defense: " << this->defense << " -> ";
    this->defense = roundToOneDec(defense * 1.12);
    cout << this->defense << endl;
    
    cout << "HP: " << this->hp << " -> ";
    this->hp += randomInt(sqrt(level) * 10, sqrt(level) * 15);
    cout << this->hp << endl;
}

////////////////////////////////////////////////////////////////////

class Enemy : public Character
{
public:
    Enemy(string name, int layer); // Enemy constructor (for layer 1 - 9)
    Enemy(int level, string name, double atk, double critDmg, double critChance, double agility, double defense, double hp); // Enemy constructor with custom values (for final boss)
    ~Enemy();
    void printInfo(); // Print enemy info
};

Enemy::Enemy(string name, int layer)
{
    this->level = layer;
    this->name = name;
    this->atk = roundToOneDec(9 * (1 + (static_cast<double>(rand()) / RAND_MAX) / 2) * pow(level, 3.0 / 5));
    this->critDmg = roundToOneDec(atk * 2);
    this->critChance = roundToOneDec(0.1 * pow(level, 2.0 / 5));
    this->agility = roundToOneDec(8 * (1 + (static_cast<double>(rand()) / RAND_MAX) / 2) * pow(level, 2.0 / 5));
    this->defense = roundToOneDec(4.5 * (1 + (static_cast<double>(rand()) / RAND_MAX) / 2) * pow(level, 2.0 / 3));
    this->hp = roundToOneDec(10 * (1 + (static_cast<double>(rand()) / RAND_MAX) / 2) * level);
}

Enemy::Enemy(int level, string name, double atk, double critDmg, double critChance, double agility, double defense, double hp)
{
    this->level = level;
    this->name = name;
    this->atk = atk;
    this->critDmg = critDmg;
    this->critChance = critChance;
    this->agility = agility;
    this->defense = defense;
    this->hp = hp;
}

Enemy::~Enemy()
{
}

void Enemy::printInfo()
{
    cout << reverseColorStart(7) << "ENEMY" << colorEnd << "  Lv. " << this->level << "  " << this->name << endl;
    cout << "  ATK: " << this->atk << endl;
    cout << "  Crit Damage: " << this->critDmg << endl;
    cout << "  Crit Chance: " << this->critChance * 100 << "%" << endl;
    cout << "  Agility: " << this->agility << endl;
    cout << "  Defense: " << this->defense << endl;
    cout << "  HP: " << this->hp << endl;
}
