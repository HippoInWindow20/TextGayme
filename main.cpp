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

const int LAYER_CNT = 4;

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
    cout << "ITEM " << this->name <<endl;
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
Item nuclearBomb("Nuclear Bomb", 10, 100, 100, 0, 0, -5);
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

//////////////////////////////////////////////////////////////////////////////////////

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
        void useItem (int index){

        };
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
        Enemy(string name, int layer);
        ~Enemy();
        void printInfo();
};

Enemy::Enemy(string name, int layer)
{
    srand(time(0));
    
    this->level = layer;
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
    cout << "! WARNING !\n";
    cout << "This game is a parody of the manga series Girl's Last Tour.\n";
    cout << "It contains major spoilers for the series. However, keep in mind that some elements aren't based on the series.\n\n";
    
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
    cout << "¡u©¹¤W¼h¥h§a¡I¡v" << endl;
    sleep(10);
    cout << "¼Ò½k«o¼ô±xªºÁn­µ¦b¹Ú¸Ì°jÅTµÛ" << endl;
    sleep(10);
    cout << "¨º®É­Ôªº " << player.getName() << " ¤j·§ÁÙ¤£º¡¤Q·³" << endl;
    sleep(10);
    cout << "¤U¼hªº­¹Â³¸ê·½¤w®ø¯Ó¬pºÉ" << endl;
    sleep(10);
    cout << "¥u¦³©¹¤W¤~¦³¥Í¦sªº§Æ±æ" << endl;
    sleep(10);
    cout << "±q¦¹¥H«á¡A«K¥H¨ì¹F³Ì³»¼h¬°¥Ø¼Ð" << endl;
    sleep(10);
    cout << "½Ð§U " << player.getName() << " ¤@Áu¤§¤O§a" << endl << endl;
    sleep(10);
    cout << "¡i«ö¤U Enter ¥H¶}©l¹CÀ¸¡j" << endl;
    
    cin.get();

    // game
    for (int i = 0; i < LAYER_CNT; i++)
    {
        // Generate random number of monsters
        int enemyCnt = randomInt(1, 1);
        int beatenEnemyCnt = 0;
        
        system("cls");
        
        // Start fighting
        for (int j = 0; j < enemyCnt; j++)
        {
            // Generate monster
            Enemy thisEnemy("lckungFake", i + 1);
            
            while (thisEnemy.getHP() > 0)  // Player fights
            {
                cout << "Current Layer: " << i + 1 << endl << endl;
                thisEnemy.printInfo();
                cout << endl;
                
                // Select tool (or fighting with bare hands)
                player.printInfo();
                cout << endl << "Choose Your Weapon!" << endl;
                sleep(500);
                cout << endl << "Select tool: " << endl;
                for (int k = 1; k <= player.getItemCnt(); k++){
                    cout << k <<  ") ";
                    player.printPossessedItem(k - 1);
                }
                cout << player.getItemCnt() + 1 << ") Bare hands" << endl;
                
                int selectedIndex = 0;
                cin >> selectedIndex;
                // do something to equip item
                while ((selectedIndex < 1 || selectedIndex > player.getItemCnt() + 1) || cin.fail()){
                    cout << "Invalid Number! Try again: ";
                    cin >> selectedIndex;
                    cout << endl;
                }
                player.useItem(selectedIndex);
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
                    beatenEnemyCnt++;
                    cout << thisEnemy.getName() << " is beaten!!!" << endl << endl;
                    
                    if (i + 1 == LAYER_CNT && beatenEnemyCnt == enemyCnt)
                    {
                        cout << "After a long journey, " << player.getName() << " finally reaches the top layer.\n";
                        sleep(2500);
                        cout << "It's a tranquil and peaceful place covered with white snow.\n";
                        sleep(2500);
                        cout << "However, there is no food found on the top layer.\n";
                        sleep(2500);
                        cout << "With nowhere else to go, " << player.getName() << " decides to enjoy their last days with the remaining food.\n";
                        sleep(2500);
                        cout << "Living sure has been great...\n";
                        sleep(2500);
                        cout << "I should eat now and then take a nap. After that, maybe think about something...\n";
                        sleep(2500);
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                        cout << "??????????????????????????????" << endl;
                    }
                    else
                    {
                    	if(beatenEnemyCnt < enemyCnt){
                    		cout << "[ Press Enter to Continue... ]" << endl;
                        	cin.ignore();
                        	cin.get();
                        	system("cls");
						}
                        else{
                        	sleep(2000);
                        	system("cls");
                        	cout << "Entering Next Floor.";
                        	sleep(1000);
                        	system("cls");
                        	cout << "Entering Next Floor..";
                        	sleep(1000);
                        	system("cls");
                        	cout << "Entering Next Floor...";
                        	sleep(1000);
                        	system("cls");
						}
                    }
                    
                }
            }
        }
    }
    
    return 0;
}
