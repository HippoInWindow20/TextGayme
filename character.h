#include <iostream>
#include <string>
#include <vector>
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
    string getName();
    double getAtk();
    double getCritDmg();
    double getCritChance();
    double getAgility();
    double getDefense();
    double getHP();

    void hit(double dmg);
    virtual void printInfo();
};

string Character::getName() { return this->name; }
double Character::getAtk() { return this->atk; }
double Character::getCritDmg() { return this->critDmg; }
double Character::getCritChance() { return this->critChance; }
double Character::getAgility() { return this->agility; }
double Character::getDefense() { return this->defense; }
double Character::getHP() { return hp; }

void Character::hit(double dmg)
{
    this->hp = max(hp - dmg, 0.0);
}

void Character::printInfo()
{
    cout << reverseColorStart(7) << "CHARACTER" << colorEnd << "  Lv. " << this->level << "  " << this->name << endl;
    cout << "  ATK: " << this->atk << endl;
    cout << "  Crit Damage: " << this->critDmg << endl;
    cout << "  Crit Chance: " << this->critChance * 100 << "%" << endl;
    cout << "  Agility: " << this->agility << endl;
    cout << "  Defense: " << this->defense << endl;
    cout << "  HP: " << this->hp << endl;
}

////////////////////////////////////////////////////
class Player : public Character
{
protected:
    vector<Item> handsOn;

public:
    Player(string name);
    ~Player();
    void equipItem(vector<Item> vec, int id);
    void printInfo();
    int getItemCnt();
    void printPossessedItem(int index);
    void useItem(int index)
    {
        this->atk += handsOn[index - 1].getAtkChange();
        this->critDmg += handsOn[index - 1].getCritChange();
        this->critChance += handsOn[index - 1].getCritChanceChange();
        this->agility += handsOn[index - 1].getAgilityChange();
        this->defense += handsOn[index - 1].getDefenseChange();
        this->hp += handsOn[index - 1].getHpChange();
    };
    void nullifyItem(int index)
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
    };
    void levelUp()
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
    };
    void addValues(double atk, double critDmg, double critChance, double agility, double defense, double hp)
    {
        this->atk += atk;
        this->critDmg += critDmg;
        this->critChance += critChance;
        this->agility += agility;
        this->defense += defense;
        this->hp += hp;
    };
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

void Player::equipItem(vector<Item> vec, int id)
{
    if (vec[id].getType() != 3)
        this->handsOn.push_back(vec[id]);
    else
        this->addValues(vec[id].getAtkChange(), vec[id].getCritChange(), vec[id].getCritChanceChange(), vec[id].getAgilityChange(), vec[id].getDefenseChange(), vec[id].getHpChange());
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
/////////////////////////////////////////////
class Enemy : public Character
{
public:
    Enemy(string name, int layer);
    Enemy(int level, string name, double atk, double critDmg, double critChance, double agility, double defense, double hp);
    ~Enemy();
    void printInfo();
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
// Enemy constructor with custom values
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