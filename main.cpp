#include <iostream>
#include <string>
#include <limits>
#include <thread> // for sleep feature
#include <chrono> // for sleep feature
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int FLOOR_CNT = 20;

//////////////////////////////////////////////////////////////////////////////////////

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
    public:
        Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange);
        void printInfo();
};

Item::Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange) : 
    name(name), atkChange(atkChange), critChange(critChange), critChanceChange(critChanceChange), agilityChange(agilityChange), 
    defenseChange(defenseChange), hpChange(hpChange)
{}

void Item::printInfo(){
    cout << "PLAYER " << this->name <<endl;
    if (atkChange > 0)
        cout << "   ATK: +" << atkChange << endl;
    if (critChange > 0)
        cout << "   Crit Damage: +" << critChange << endl;
    if (critChanceChange > 0)
        cout << "   Crit Chance: +" << critChanceChange * 100 << "%" << endl;
    if (agilityChange > 0)
        cout << "   Agility: +" << agilityChange << endl;
    if (defenseChange > 0)
        cout << "   Defense: +" << defenseChange << endl;
    if (hpChange > 0)
        cout << "   HP: +" << hpChange << endl;
    cout << endl;
}

// Item listing
Item note7("Note 7", 2, 2, 0.01, 0, 0, 0);
Item nuclearBomb("Nuclear Bomb", 1, 10, 0, 0, 0, 0);
Item knife("Knife", 1, 2, 0, 0, 0, 0);

//////////////////////////////////////////////////////////////////////////////////////

class Character
{
    protected:
        string name;
        double atk;
        double critDmg;
        double critChance;
        double agility;
        double defense;
        double hp;
    public:
        void attackOpponent(Character* opponent);
        
        string getName();
        double getAtk();
        double getCritDmg();
        double getCritChance(); 
        double getAgility();
        double getDefense();
        double getHP();
        
        void hit(double dmg);
};

string Character::getName()
{
    return this->name;
}

double Character::getAtk()
{
    return this->atk;
}
double Character::getCritDmg()
{
    return this->critDmg;
}
double Character::getCritChance()
{
    return this->critChance;
}
double Character::getAgility()
{
    return this->agility;
}
double Character::getDefense()
{
    return this->defense;
}       
double Character::getHP()
{
    return hp;
}

void Character::hit(double dmg)
{
    this->hp = max(hp - dmg, 0.0);
}


class Player : public Character {
    protected:
        int level;
        int exp;
        vector<Item> handsOn;

    public:
        Player(string name);
        ~Player();
        void levelUp();
        void equipItem(int id);
        void printInfo();
        int getItemCnt ();
        void printPossessedItem(int index);
};

Player::Player(string name)
{
    this->name = name;
    this->atk = 10;
    this->critDmg = atk * 2;
    this->critChance = 0.1;
    this->agility = 20;
    this->defense = 10;
    this->hp = 99;
    this->level = 1;
    this->exp = 0;
}

Player::~Player()
{
}

void Player::equipItem(int id)
{
    switch (id){
        case 0:
            this->handsOn.push_back(note7);
            break;
        case 1:
            this->handsOn.push_back(nuclearBomb);
            break;
        case 2:
            this->handsOn.push_back(knife);
        default:
            ;
    }
}

void Player::printInfo()
{
    cout << "PLAYER  " << "Lv. " << this->level << "  " << this->name << endl;
    cout << "  ATK: " << this->atk << endl;
    cout << "  Crit Damage: " << this->critDmg << endl;
    cout << "  Crit Chance: " << this->critChance * 100 << "%" << endl;
    cout << "  Agility: " << this->agility << endl;
    cout << "  Defense: " << this->defense << endl;
    cout << "  HP: " << this->hp << endl;
} 

int Player::getItemCnt() {
    return this->handsOn.size();
}

void Player::printPossessedItem(int index){
    this->handsOn[index].printInfo();
}

//////////////////////////////////////////////////////////////////////////////////////

class Enemy : public Character
{
    protected:
        int level;

    public:
        Enemy(string name, int floor);
        ~Enemy();
        void printInfo();
};

Enemy::Enemy(string name, int floor)
{
    srand(time(0));
    
    this->level = floor;
    this->name = name;
    this->atk = 10 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * level;
    this->critDmg = atk * 2;
    this->critChance = 0.1;
    this->agility = 10;
    this->defense = 5;
    this->hp = 15;
}

Enemy::~Enemy()
{
}

void Enemy::printInfo()
{
    cout << "ENEMY  " << "Lv. " << this->level << "  " << this->name << endl;
    cout << "  ATK: " << this->atk << endl;
    cout << "  Crit Damage: " << this->critDmg << endl;
    cout << "  Crit Chance: " << this->critChance * 100 << "%" << endl;
    cout << "  Agility: " << this->agility << endl;
    cout << "  Defense: " << this->defense << endl;
    cout << "  HP: " << this->hp << endl;
}

//////////////////////////////////////////////////////////////////////////////////////

void sleep(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

int randomInt(int min, int max) {
    srand(time(0));
    return min + rand() % (max + 1 - min);
}

int main()
{
    
    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);
    // Debug
    player.equipItem(0);
    player.equipItem(0);
    player.equipItem(1);
    player.equipItem(2);
    
    system("cls");
    
    // world building
    cout << "「往上層去吧！」" << endl;
    sleep(10);
    cout << "模糊卻熟悉的聲音在夢裡迴響著" << endl;
    sleep(10);
    cout << "那時候的 " << player.getName() << " 大概還不滿十歲" << endl;
    sleep(10);
    cout << "下層的食糧資源已消耗殆盡" << endl;
    sleep(10);
    cout << "只有往上才有生存的希望" << endl;
    sleep(10);
    cout << "從此以後，便以到達最頂層為目標" << endl;
    sleep(10);
    cout << "請助 " << player.getName() << " 一臂之力吧" << endl << endl;
    sleep(10);
    cout << "【按下 Enter 以開始遊戲】" << endl;
    
    cin.get();
    sleep(300);

    // game
    for (int i = 0; i < FLOOR_CNT; i++)
    {
        // Generate random number of monsters
        int enemyQty = randomInt(1, 4);
        
        system("cls");
        if (player.getHP() <= 0) // Player died
        {
            cout << player.getName() << " sucks. GAME OVER!";
            break;
        } else {
            // Start fighting
            for (int j = 0; j < enemyQty; j++)
            {
                // Generate monster
                Enemy thisEnemy("lckungFake", i + 1);
                
                while (thisEnemy.getHP() > 0)  // Player fights
                {
                    thisEnemy.printInfo();
                    cout << endl;
                    
                    // Select tool (or fighting with bare hands)
                    player.printInfo();
                    cout << endl << "Seraching for available items..." << endl;
                    sleep(1500);
                    cout << endl << "Select tool: " << endl;
                    for (int k = 1; k <= player.getItemCnt(); k++){
                        cout << k <<  ") ";
                        player.printPossessedItem(k - 1);
                    }
                    cout << player.getItemCnt() + 1 << ") Bare hands" << endl;
                    
                    int selectedIndex = 0;
                    cin >> selectedIndex;
                    // do something to equip item
                    
                    cout << endl;
                    
                    // Player fights enemy
                    int temp = randomInt(1, 100);
                    if (temp <= player.getCritChance() * 100) // critical hit!
                    {
                        double dmg = player.getCritDmg() * max((1 - thisEnemy.getDefense() / 100), 0.0);
                        thisEnemy.hit(dmg);
                        cout << thisEnemy.getName() << " loses " << dmg << "HP!" << endl;
                    }
                    else // normal hit
                    {
                        double dmg = player.getAtk() * max((1 - thisEnemy.getDefense() / 100), 0.0);
                        thisEnemy.hit(dmg);
                        cout << thisEnemy.getName() << " loses " << dmg << "HP!" << endl;
                    }
                    
                    
                    // Enemy fights back if it's alive
                    if (thisEnemy.getHP() > 0)
                    {
                        if (temp <= player.getCritChance() * 100) // critical hit!
                        {
                            double dmg = player.getCritDmg() * max((1 - player.getDefense() / 100), 0.0);
                            player.hit(dmg);
                            cout << player.getName() << " loses " << dmg << "HP..." << endl;
                        }
                        else // normal hit
                        {
                            double dmg = player.getAtk() * max((1 - player.getDefense() / 100), 0.0);
                            player.hit(dmg);
                            cout << player.getName() << " loses " << dmg << "HP..." << endl << endl;
                        }
                        
                        if (player.getHP() <= 0) // Player died
                        {
                            cout << player.getName() << " sucks. GAME OVER!";
                            break;
                        }
                        else
                        {
                            cout << "[ Press Enter to Continue... ]" << endl;
                            cin.ignore();
                            cin.get();
                            system("cls");
                        }
                    }
                    else
                    {
                        cout << thisEnemy.getName() << " is beaten!!!" << endl << endl;
                        cout << "[ Press Enter to Continue... ]" << endl;
                        cin.ignore();
                        cin.get();
                        system("cls");
                    }
                }
            }
        }
    }
    
    return 0;
}
