#include <iostream>
#include <string>
#include <limits>
#include <thread> // for sleep feature
#include <chrono> // for sleep feature
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;

const int LAYER_CNT = 3;

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
        int type; //1 for throwable, 2 for weapon, 3 for potion
    public:
        Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange, int type);
        void printInfo();
        //getter from chatgpt
        double getAtkChange() const { return atkChange; }
    	double getCritChange() const { return critChange; }
    	double getCritChanceChange() const { return critChanceChange; }
   		double getAgilityChange() const { return agilityChange; }
    	double getDefenseChange() const { return defenseChange; }
    	double getHpChange() const { return hpChange; }
    	int getType() const { return type; }
};

Item::Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange, int type) : 
    name(name), atkChange(atkChange), critChange(critChange), critChanceChange(critChanceChange), agilityChange(agilityChange), 
    defenseChange(defenseChange), hpChange(hpChange), type(type)
{}

void Item::printInfo(){
	
	if (this->type == 1)
        cout << "PROJECTILE ";
    else if (this->type == 2)
        cout << "WEAPON ";
    else if (this->type == 3)
        cout << "POTION ";
	
    cout << this->name << endl;
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
Item note7("Note 7", 2, 2, 0.01, 0, 0, 0, 1);
Item nuclearBomb("Nuclear Bomb", 100, 120, 0.4, 0, 0, -20, 1);
Item knife("Knife", 1, 2, 0, 0, 0, 0, 2);
Item freezeDog("Freezed Sausage", 3, 4, 0, 0, 0, 0, 2);
Item energyDrink("Energy Drink", 0, 0, 0, 0, 0, 50, 3);
Item hyperEnergyDrink("Hyper Energy Drink", 0, 0, 0, 0, 0, 200, 3);
Item drone("Drone", 20, 0, 0.1, 0, 0, 0, 1);
Item map("Map", 0, 0, 0.4, 20, 0, 0, 2);
Item shield("Shield", 0, 0, 0, 0, 30, 0, 2);
Item barrier("Barrier", 0, 0, 0, 0, 100, 0, 1);
Item chocoBar("Chocolate Bar", 2, 0, 0.01, 2, 2, 10, 3);
Item mysteryFish("Mystery Fish", 10, 0, 0.05, 10, 10, 30, 3);
Item cppGuideBook("Guide Book for C++ programming Language", 0, 0, 0.1, 10, 30, 20, 3);
Item godStar("God Star", 1000, 1000, 1000, 1000, 1000, 1000, 2);

vector<Item> itemList;	//a list of all existing items

int options[3] = {0};

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

string Character::getName(){return this->name;}
double Character::getAtk(){return this->atk;}
double Character::getCritDmg(){return this->critDmg;}
double Character::getCritChance(){return this->critChance;}
double Character::getAgility(){return this->agility;}
double Character::getDefense(){return this->defense;}
double Character::getHP(){return hp;}

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
        int getItemCnt();
        void printPossessedItem(int index);
        void useItem (int index){
			this->atk+= handsOn[index-1].getAtkChange();
			this->critDmg+= handsOn[index-1].getCritChange();
			this->critChance+= handsOn[index-1].getCritChanceChange();
			this->agility+= handsOn[index-1].getAgilityChange();
			this->defense+= handsOn[index-1].getDefenseChange();
			this->hp+= handsOn[index-1].getHpChange();
        };
        void removeItem(int index){
        	this->atk-= handsOn[index-1].getAtkChange();
			this->critDmg-= handsOn[index-1].getCritChange();
			this->critChance-= handsOn[index-1].getCritChanceChange();
			this->agility-= handsOn[index-1].getAgilityChange();
			this->defense-= handsOn[index-1].getDefenseChange();
			this->hp-= handsOn[index-1].getHpChange();
			if(handsOn[index-1].getType() == 1){
				handsOn.erase(handsOn.begin() + index - 1);
			}
				
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

    this->handsOn.push_back(itemList[id]);
        
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
    this->critChance = 0.1 * pow(level, 1.0 / 3);
    this->agility = 10 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * level;
    this->defense = 2 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * level;
    this->hp = 15 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * level;
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
	
	itemList.push_back(note7);
	itemList.push_back(nuclearBomb);
	itemList.push_back(knife);
	itemList.push_back(freezeDog);
	itemList.push_back(godStar);
	
	
	fstream mobFile;
    mobFile.open("mobNames.txt");
    vector<string> mobName;
    string fileInput;
    while(!mobFile.eof()){
    	mobFile >> fileInput;
    	mobName.push_back(fileInput);
	}
	
	
    system("cls");
    cout << "! WARNING !\n";
    cout << "This game is a parody of the manga series Girls' Last Tour.\n";
    cout << "It contains major spoilers for the series. However, keep in mind that some elements aren't based on the series.\n\n";
    
    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);
    // Debug
    player.equipItem(0);
    player.equipItem(1);
    player.equipItem(2);
    player.equipItem(3);
    player.equipItem(4);
    
    system("cls");
    
    // world building
    cout << "\"Go upwards!\"" << endl;
    sleep(10);
    cout << "An unclear yet familiar voice resonates in " << player.getName() << "'s dream." << endl;
    sleep(10);
    cout << "At that time, " << player.getName() << " was no older than ten." << endl;
    sleep(10);
    cout << "Food and resources are lacking in the lower layers." << endl;
    sleep(10);
    cout << "The only hope is to move upwards." << endl;
    sleep(10);
    cout << "All " << player.getName() << " can do is to aim for the top layer."<< endl;
    sleep(10);
    cout << "Please lend " << player.getName() << " a helping hand!" << endl;
    sleep(10);
    cout << "[ Press Enter to start the game ]" << endl;
    
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
            Enemy thisEnemy(mobName[randomInt(0, mobName.size() - 1)] , i + 1);
            
            while (thisEnemy.getHP() > 0)  // Player fights
            {
                cout << "Current Layer: " << i + 1 << endl << endl;
                thisEnemy.printInfo();
                cout << endl;
                player.printInfo();
                cout << endl << "[ Press Enter to Continue... ]" << endl;
                cin.ignore();
                cin.get();
                
                // Select tool (or fight with bare hands)
                cout << endl << "Select a tool to fight with " << thisEnemy.getName() << ":" << endl;
                for (int k = 1; k <= player.getItemCnt(); k++){
                    cout << k <<  ") ";
                    player.printPossessedItem(k - 1);
                }
                cout << player.getItemCnt() + 1 << ") Bare hands" << endl;
                
                // Equip item
                int selectedIndex = 0;
                while (true) {
                    string input;
                    cin >> input;
                    try {
                        selectedIndex = stoi(input);
                        if (selectedIndex < 1 || selectedIndex > player.getItemCnt() + 1 || input.length() != to_string(selectedIndex).length()) {
                            throw invalid_argument("Invalid range");
                        }
                        break;
                    } catch (invalid_argument&) {
                        cout << "Invalid input! Please try again: ";
                    }
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
                        cout << player.getName() << " is defeated on layer " << i + 1 << "...";
                        break;
                    }
                    else
                    {
                    	player.removeItem(selectedIndex);
                        cout << "[ Press Enter to Continue... ]" << endl;
                        cin.ignore();
                        cin.get();
                        system("cls");
                    }
                }
                else
                {
                	player.removeItem(selectedIndex);
                    beatenEnemyCnt++;
                    cout << thisEnemy.getName() << " is beaten!!!" << endl << endl;
                    
                    if (i + 1 == LAYER_CNT && beatenEnemyCnt == enemyCnt)
                    {
                        sleep(2000);
                        system("cls");
                        cout << "After a long journey, " << player.getName() << " finally reaches the top layer.\n";
                        sleep(2500);
                        cout << "It's a tranquil and peaceful place covered with white snow.\n";
                        sleep(2500);
                        cout << "However, there is no food found on the top layer.\n";
                        sleep(2500);
                        cout << "With nowhere else to go, " << player.getName() << " decides to enjoy their last days with the remaining food.\n";
                        sleep(2500);
                        cout << "\"Living sure has been great...\"\n";
                        sleep(2500);
                        cout << "\"I should eat now and then take a nap. After that, maybe think about something...\"\n";
                        sleep(2500);
                        cout << endl;
                        cout << ".###%%%*@@#%%%@@@@@               @@@@@@@=-@@@@@@ " << endl;
                        cout << " #%%%%%*@@#%@@@@   .=+++++++++++=.  .@@@@@@@@@@@@ " << endl;
                        cout << " %%%%%%#@@#@@@  .=+=--==++++++++===-  #@@%%%+-@@@ " << endl;
                        cout << " %%%%%%#@@@@+ .=+==@@@@--+++++++==@@@+  @@@%-%%** " << endl;
                        cout << " %%%%%%#@@@  -+++=@    @-+++++++=@   @+ =@@=%@%%% " << endl;
                        cout << " %%%%%%%@@ .=++++=@   @--+++++++==@@@=-- @+@@%%%% " << endl;
                        cout << " %%%%%%@@: =+++++==@@@==+++++++++++=--++..@@%%%%% " << endl;
                        cout << " #%%%%@@# =+++++++++++++++++++++++++++++= @@%%%%% " << endl;
                        cout << " #%%%%@@ -++++++++++++++++++=+++++++++++- @@%%%%% " << endl;
                        cout << " %#%%@@- ++++++++++++++++++( )+++++++++= -@@%%%%% " << endl;
                        cout << " @#*%@@ -+++++++++++++++++++++++++++++=. @@%%%%%% " << endl;
                        cout << " @@@*@@ ++++++++++++++++++++++++++++++. @@@%%%%%% " << endl;
                        cout << " @@@@@: +++++++++++++++++++++++++++++. @@@%%%%%%% " << endl;
                        cout << " %@@@@ :++++++++++++++++++++++++++++- @%@%%%%%%%% " << endl;
                        cout << " %##@@ -+++++++++++++++++++++++++++= @@-@%%%%%%%% " << endl;
                        cout << " %%%@@ -+++++++++++++++++++++++++++=.@@#@%%%%%%%% " << endl;
                        cout << " %%%@@.-++++++++++++++++++++++++++++- -@@@%%%%%%% " << endl;
                        cout << " %%%@@.=+@@=++++++++++*****+*+**+++++=  @@@%%%%%% " << endl;
                        cout << " %%@@@ +=-@==++++*++**+++++++++=:=:.-++: @@%%%%%= " << endl;
                        cout << " %@@@ -*+=-@=+**+@*++++*+++++=:.=@@@  -+. @@@:@@- " << endl;
                        cout << " %@@@ +***=+#++*+:@     .... :=#+:.-@+ .: *@@@@@- " << endl;
                        cout << " %@@::+****+#+--: @@@@%::-==+=-#@@@@@@@  =@@@@@:+ " << endl;
                        cout << " ::=         @ @ @@@@%@@@@@@@@@@@%#**+*@@@@%+*@#  " << endl;
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
                        	cout << "Moving to Next Layer.";
                        	sleep(1000);
                        	system("cls");
                        	cout << "Moving to Next Layer..";
                        	sleep(1000);
                        	system("cls");
                        	cout << "Moving to Next Layer...";
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
