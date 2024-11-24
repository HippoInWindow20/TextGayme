#include <iostream>
#include <string>
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

int main()
{
    
    string name;
    cout << "Please name your character: ";
    cin >> name;
    Player player(name);

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