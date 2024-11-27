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

//==========================================================================================================
class Item
{
    protected:
        string name;
        double attackChange;
        double critAttackChange;
        double critChanceChange;
        double agilityChange;
        double defenseChange;
        double hpChange;
    public:
        Item(string name, double attackChange, double critAttackChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange);
        void getInfo();
};

Item::Item(string name, double attackChange, double critAttackChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange) : 
    name(name), attackChange(attackChange), critAttackChange(critAttackChange), critChanceChange(critChanceChange), agilityChange(agilityChange), 
    defenseChange(defenseChange), hpChange(hpChange)
{}

void Item::getInfo(){
    cout << this->name <<endl;
    if (attackChange > 0)
        cout << "   Attack: +" << attackChange << endl;
    if (critAttackChange > 0)
        cout << "   Critical Attack: +" << critAttackChange << endl;
    if (critChanceChange > 0)
        cout << "   Critical Chance: +" << critChanceChange * 100 << "%" << endl;
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
//==========================================================================================================
class Character
{
    protected:
        string name;
        double attack;
        double critAttack;
        double critChance;
        double agility;
        double defense;
        double hp;
    public:
        void attackOpponent(Character* opponent);
        
        double getHP();
        string getName();
};

double Character::getHP()
{
    return hp;
}

string Character::getName()
{
    return name;
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
        int getItemCnt ();
        void getItemInfo(int index);
};

Player::Player(string name)
{
    this->name = name;
    this->attack = 50;
    this->critAttack = attack * 2;
    this->critChance = 0.1;
    this->agility = 20;
    this->defense = 1;
    this->hp = 25;
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

int Player::getItemCnt() {
    return this->handsOn.size();
}

void Player::getItemInfo(int index){
    this->handsOn[index].getInfo();
}

//==========================================================================================================
class Enemy : public Character {
    protected:
        int level;

    public:
        Enemy(string name, int floor);
        ~Enemy();
        void printEnemy();
};

Enemy::Enemy(string name, int floor)
{
    srand(time(0));
    
    this->level = floor;
    this->name = name;
    this->attack = 10 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * level;
    this->critAttack = attack * 2;
    this->critChance = 0.1;
    this->agility = 10;
    this->defense = 5;
    this->hp = 5;
}

Enemy::~Enemy(){
}

void Enemy::printEnemy(){
    cout << "Monster " << this->name << endl;
    cout << "  Level: " << this->level << endl;
    cout << "  Attack: " << this->attack << endl;
    cout << "  Critial Attack: " << this->critAttack << endl;
    cout << "  Critical Chance: " << this->critChance * 100 << "%" << endl;
    cout << "  Agility: " << this->agility << endl;
    cout << "  Defense: " << this->defense << endl;
    cout << "  HP: " << this->hp << endl;
}
//==========================================================================================================
void sleep(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

int randomInt (int bottom, int top) {
    srand(time(0));
    return bottom + rand() % (top + 1 - bottom);
}

int main()
{
    
    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);
    //Debug
    player.equipItem(0);
    player.equipItem(0);
    player.equipItem(1);
    player.equipItem(2);
    
    system("cls");
    
    
    // world building
    cout << "「往上層去吧！」" << endl;
    sleep(1000);
    cout << "模糊卻熟悉的聲音在夢裡迴響著" << endl;
    sleep(1000);
    cout << "那時候的 " << player.getName() << " 大概還不滿十歲" << endl;
    sleep(1000);
    cout << "下層的食糧資源已消耗殆盡" << endl;
    sleep(1000);
    cout << "只有往上才有生存的希望" << endl;
    sleep(1000);
    cout << "從此以後，便以到達最頂層為目標" << endl;
    sleep(1000);
    cout << "請助 " << player.getName() << " 一臂之力吧" << endl << endl;
    sleep(1000);
    cout << "【按下 Enter 以開始遊戲】" << endl;
    
    cin.get();

    // game
    for (int i = 0; i < FLOOR_CNT; i++)
    {
        // create random monster
        int enemyQty = randomInt(1, 4);
        
        
        
        system("cls");
        if (player.getHP() <= 0) // player died
        {
            cout << player.getName() << " sucks. GAME OVER!";
            break;
        } else {
            //start gayme
            for (int j = 0;j < enemyQty;j++){
                //create monster
                Enemy thisEnemy("lckungFake",i+1);
                thisEnemy.printEnemy();
                sleep(1000);
                cout << endl;
                while (thisEnemy.getHP() > 0){
                    //Player fight
                    //Select tool (or fight with bare hands)
                    cout << "Select tool: " << endl;
                    for (int k = 1;k <= player.getItemCnt();k++){
                        cout << k <<  ") ";
                        player.getItemInfo(k-1);
                    }
                    cout << player.getItemCnt() + 1 << ") Bare hands" << endl;
                    int selectedIndex = 0;
                    cin >> selectedIndex;
                    //Fight
                }
            }
        }
    }
    
    
    
    return 0;
}
