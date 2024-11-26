#include <iostream>
#include <string>
#include <limits>
#include <thread> // for sleep feature
#include <chrono> // for sleep feature
using namespace std;

const int FLOOR_CNT = 100;

class Item
{
    protected:
	    string name;
	    int attackChange;
        int critAttackChange;
        int critChanceChange;
        int speedChange;
        int defenseChange;
        int hpChange;
    public:
        Item(string name, int attackChange, int critAttackChange, int critChanceChange, int speedChange, int defenseChange, int hpChange);
};

Item::Item(string name, int attackChange, int critAttackChange, int critChanceChange, int speedChange, int defenseChange, int hpChange) : 
    name(name), attackChange(attackChange), critAttackChange(critAttackChange), critChanceChange(critChanceChange), speedChange(speedChange), 
    defenseChange(defenseChange), hpChange(hpChange)
{}

class Character
{
    protected:
        string name;
        int attack;
        int critAttack;
        int critChance;
        int speed;
        int defense;
        int hp;
    public:
        void attackOpponent(Character* opponent);
        
        int getHP();
        string getName();
};

int Character::getHP()
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
        Item* handsOn;

    public:
        Player(string name);
        ~Player();
        void levelUp();
        void equipItem(string itemName);
};

Player::Player(string name)
{
    this->name = name;
    this->attack = 5;
    this->critAttack = 10;
    this->critChance = 0.1;
    this->speed = 1;
    this->defense = 1;
    this->hp = 0;
    this->level = 1;
    this->exp = 0;
}

Player::~Player()
{
    delete[] handsOn;
}

void Player::equipItem(string itemName)
{

}

void sleep()
{
    this_thread::sleep_for(std::chrono::milliseconds(1200));
}

int main()
{
    
    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);
    
    // world building
    cout << "「往上層去吧！」" << endl;
    sleep();
    cout << "模糊卻熟悉的聲音在夢裡迴響著" << endl;
    sleep();
    cout << "那時候的 " << player.getName() << " 大概還不滿 10 歲" << endl;
    sleep();
    cout << "下層的食糧資源已消耗殆盡" << endl;
    sleep();
    cout << "只有往上才有生存的希望" << endl;
    sleep();
    cout << "從此以後，便以到達最頂層為目標" << endl;
    sleep();
    cout << "請助 " << player.getName() << " 一臂之力吧" << endl << endl;
    sleep();
    cout << "【按下 Enter 以開始遊戲】" << endl;
    
    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
    cin.get();

    // Item listing
    Item note7("Note 7", 2, 2, 0.01, 0, 0, 0);
    Item nuclearBomb("Nuclear Bomb", 1, 10, 0, 0, 0, 0);
    Item knife("Knife", 1, 2, 0, 0, 0, 0);

    // game
    for (int i = 0; i < FLOOR_CNT; i++)
    {
        if (player.getHP() <= 0)
        {
            cout << player.getName() << " sucks.";
            break;
        }
    }
    
    return 0;
}