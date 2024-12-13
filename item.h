#include "utils.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item
{
protected:
    string name;
    double atkChange;
    double critChange;
    double critChanceChange;
    double agilityChange;
    double defenseChange;
    double hpChange;
    int type; // 1 for projectile, 2 for weapon, 3 for potion
public:
    Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange, int type);
    void printInfo(); // print item info
    // getters
    double getAtkChange() const;
    double getCritChange() const;
    double getCritChanceChange() const;
    double getAgilityChange() const;
    double getDefenseChange() const;
    double getHpChange() const;
    int getType() const;
};

Item::Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange, int type) : name(name), atkChange(atkChange), critChange(critChange), critChanceChange(critChanceChange), agilityChange(agilityChange),
                                                                                                                                                               defenseChange(defenseChange), hpChange(hpChange), type(type)
{
}

void Item::printInfo()
{

    if (this->type == 1)
        cout << reverseColorStart(7) << "PROJECTILE" << colorEnd;
    else if (this->type == 2)
        cout << reverseColorStart(7) << "WEAPON" << colorEnd;
    else if (this->type == 3)
        cout << reverseColorStart(7) << "POTION" << colorEnd;

    cout << " " << this->name << endl;
    if (atkChange > 0)
        cout << "   ATK: +" << atkChange << endl;
    else if (atkChange < 0)
        cout << "   ATK: " << atkChange << endl;
    if (critChange > 0)
        cout << "   Crit Damage: +" << critChange << endl;
    else if (critChange < 0)
        cout << "   Crit Damage: " << critChange << endl;
    if (critChanceChange > 0)
        cout << "   Crit Chance: +" << critChanceChange * 100 << "%" << endl;
    else if (critChanceChange < 0)
        cout << "   Crit Chance: " << critChanceChange * 100 << "%" << endl;
    if (agilityChange > 0)
        cout << "   Agility: +" << agilityChange << endl;
    else if (agilityChange < 0)
        cout << "   Agility: " << agilityChange << endl;
    if (defenseChange > 0)
        cout << "   Defense: +" << defenseChange << endl;
    else if (defenseChange < 0)
        cout << "   Defense: " << defenseChange << endl;
    if (hpChange > 0)
        cout << "   HP: +" << hpChange << endl;
    else if (hpChange < 0)
        cout << "   HP: " << hpChange << endl;
    cout << endl;
}

double Item::getAtkChange() const { return atkChange; }
double Item::getCritChange() const { return critChange; }
double Item::getCritChanceChange() const { return critChanceChange; }
double Item::getAgilityChange() const { return agilityChange; }
double Item::getDefenseChange() const { return defenseChange; }
double Item::getHpChange() const { return hpChange; }
int Item::getType() const { return type; }
