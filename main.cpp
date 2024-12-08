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

const int LAYER_CNT = 10;

int randomInt(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

double roundToOneDec(double num)
{
    return round(num * 10) / 10.0;
}

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
    int type; // 1 for projectile, 2 for weapon, 3 for potion
public:
    Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange, int type);
    void printInfo();
    // getter from chatgpt
    double getAtkChange() const { return atkChange; }
    double getCritChange() const { return critChange; }
    double getCritChanceChange() const { return critChanceChange; }
    double getAgilityChange() const { return agilityChange; }
    double getDefenseChange() const { return defenseChange; }
    double getHpChange() const { return hpChange; }
    int getType() const { return type; }
};

Item::Item(string name, double atkChange, double critChange, double critChanceChange, double agilityChange, double defenseChange, double hpChange, int type) : name(name), atkChange(atkChange), critChange(critChange), critChanceChange(critChanceChange), agilityChange(agilityChange),
                                                                                                                                                               defenseChange(defenseChange), hpChange(hpChange), type(type)
{
}

void Item::printInfo()
{

    if (this->type == 1)
        cout << "PROJECTILE ";
    else if (this->type == 2)
        cout << "WEAPON ";
    else if (this->type == 3)
        cout << "POTION ";

    cout << this->name << endl;
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

// Item listing
Item note7("Note 7", 8, 15, 0.01, 0, 0, 0, 1);
Item nuclearBomb("Nuclear Bomb", 100, 120, 0.4, 0, 0, -20, 1);
Item knife("Knife", 5, 10, 0, 0, 0, 0, 2);
Item freezeDog("Frozen Sausage", 3, 4, 0, 0, 0, 0, 2);
Item energyDrink("Energy Drink", 0, 0, 0, 0, 0, 50, 3);
Item hyperEnergyDrink("Hyper Energy Drink", 0, 0, 0, 0, 0, 200, 3);
Item drone("Drone", 20, 0, 0.1, 0, 0, 0, 1);
Item map("Map", 0, 0, 0.2, 10, 0, 0, 2);
Item shield("Shield", 0, 0, 0, 0, 30, 0, 1);
Item barrier("Barrier", 0, 0, 0, 0, 100, 0, 1);
Item chocoBar("Chocolate Bar", 2, 0, 0.01, 2, 2, 10, 3);
Item mysteryFish("Mystery Fish", 1, 0, 0.03, 2, 10, 3, 3);
Item cppGuideBook("Guide Book for C++ Programming Language", 0, 0, 0.1, 5, 30, 20, 3);
Item gambleToken("Gamble Token", 0, 9999, -0.08, 0, 0, 0, 1);
Item godStar("God Star", 1000, 1000, 1, 100, 1000, 1000, 2);

vector<Item> itemList; // a list of all existing items

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
    void attackOpponent(Character *opponent);

    string getName();
    double getAtk();
    double getCritDmg();
    double getCritChance();
    double getAgility();
    double getDefense();
    double getHP();

    void hit(double dmg);
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

//////////////////////////////////////////////////////////////////////////////////////

class Player : public Character
{
protected:
    int level;
    int exp;
    vector<Item> handsOn;

public:
    Player(string name);
    ~Player();
    void equipItem(int id);
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
        this->atk *= 1.2;
        cout << this->atk << endl;
        cout << "Crit Damage: " << this->critDmg << " -> ";
        this->critDmg = atk * 2;
        cout << this->critDmg << endl;
        cout << "Crit Chance: " << this->critChance * 100 << "% -> ";
        this->critChance += 0.01;
        cout << this->critChance * 100 << "%" << endl;
        cout << "Agility: " << this->agility << " -> ";
        this->agility += 1.5;
        cout << this->agility << endl;
        cout << "Defense: " << this->defense << " -> ";
        this->defense *= 1.15;
        cout << this->defense << endl;
        cout << "HP: " << this->hp << " -> ";
        this->hp += randomInt(10, 50);
        cout << this->hp << endl;
    };
    void addValues (double atk, double critDmg, double critChance, double agility, double defense, double hp)
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
    this->exp = 0;
}

Player::~Player()
{
}

void Player::equipItem(int id)
{
    if (itemList[id].getType() != 3)
        this->handsOn.push_back(itemList[id]);
    else
        this->addValues(itemList[id].getAtkChange(), itemList[id].getCritChange(), itemList[id].getCritChanceChange(), itemList[id].getAgilityChange(), itemList[id].getDefenseChange(), itemList[id].getHpChange());
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

int Player::getItemCnt()
{
    return this->handsOn.size();
}

void Player::printPossessedItem(int index)
{
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
    this->level = layer;
    this->name = name;
    this->atk = roundToOneDec(10 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * pow(level, 3.0 / 4));
    this->critDmg = roundToOneDec(atk * 2);
    this->critChance = roundToOneDec(0.1 * pow(level, 2.0 / 5));
    this->agility = roundToOneDec(8 * pow(level, 2.0 / 5));
    this->defense = roundToOneDec(3 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * pow(level, 2.0 / 3));
    this->hp = roundToOneDec(10 * (1 + (static_cast<double>(rand()) / RAND_MAX)) * level);
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

void printCharByChar(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        cout << text[i];
        sleep(50);
    }
}

string twoDigitsOrElse (string num){
    if (num.length() == 1)
        return "0" + num;
    return num;
}

string formatSeconds(int sec) {
    int hours = sec / 3600;
    int minutes = (sec % 3600) / 60;
    int seconds = sec % 60;
    return twoDigitsOrElse(to_string(hours)) + ":" + twoDigitsOrElse(to_string(minutes)) + ":" + twoDigitsOrElse(to_string(seconds));
}

string colorStart(int num) {
    return "\x1B[" + to_string(num) + "m";
}

string colorEnd = "\033[0m";


int main()
{
    srand(time(0));
    itemList.push_back(note7);
    itemList.push_back(nuclearBomb);
    itemList.push_back(knife);
    itemList.push_back(freezeDog);
    itemList.push_back(godStar);
    itemList.push_back(energyDrink);
    itemList.push_back(hyperEnergyDrink);
    itemList.push_back(drone);
    itemList.push_back(map);
    itemList.push_back(shield);
    itemList.push_back(barrier);
    itemList.push_back(chocoBar);
    itemList.push_back(mysteryFish);
    itemList.push_back(cppGuideBook);
    itemList.push_back(gambleToken);

    fstream mobFile;
    mobFile.open("mobNames.txt");
    vector<string> mobName;
    string fileInput;
    while (!mobFile.eof())
    {
        mobFile >> fileInput;
        mobName.push_back(fileInput);
    }

    system("cls");
    cout << "\x1B[31m! WARNING !\033[0m\n";
    cout << "This game is a parody of the manga series Girls' Last Tour.\n";
    cout << "It contains major spoilers for the series. However, keep in mind that some elements aren't based on the series.\n\n";

    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);

    system("cls");

    // world building
    printCharByChar("\"Go upwards!\"\n");
    sleep(50);
    printCharByChar("An unclear yet familiar voice resonates in ");
    printCharByChar(player.getName());
    printCharByChar("'s dream.\n");
    sleep(50);
    printCharByChar("At that time, " + player.getName() + " was no older than ten.\n");
    sleep(10);
    printCharByChar("Food and resources are lacking in the lower layers.\n");
    sleep(10);
    printCharByChar("The only hope is to move upwards.\n");
    sleep(10);
    printCharByChar("All " + player.getName() + " can do is to aim for the top layer.\n");
    sleep(10);
    printCharByChar("Please lend " + player.getName() + " a helping hand!\n");
    sleep(1000);
    cout << colorStart(93) << "[ Press Enter to start the game ]" << colorEnd << endl;

    cin.get();
    time_t startTime = time(0);
    // game
    for (int i = 0; i < LAYER_CNT; i++)
    {
        // Generate random number of enemies
        int enemyCnt = randomInt(1, 2);
        int beatenEnemyCnt = 0;

        system("cls");

        // Start fighting
        for (int j = 0; j < enemyCnt; j++)
        {
            // Generate enemy
            Enemy thisEnemy(mobName[randomInt(0, mobName.size() - 1)], i + 1);

            while (thisEnemy.getHP() > 0) // Player fights
            {
                cout << "Current Layer: " << i + 1 << endl << endl;
                thisEnemy.printInfo();
                cout << endl;
                player.printInfo();
                cout << endl
                     << "[ Press Enter to Continue... ]" << endl;
                cin.ignore();

                // Select tool (or fight with bare hands)
                cout << endl
                     << "Select a tool to fight with " << thisEnemy.getName() << ":" << endl;
                for (int k = 1; k <= player.getItemCnt(); k++)
                {
                    cout << k << ") ";
                    player.printPossessedItem(k - 1);
                }
                cout << player.getItemCnt() + 1 << ") Bare hands" << endl;

                // Equip item
                int selectedIndex = 0;
                while (true)
                {
                    string input;
                    cin >> input;
                    try
                    {
                        selectedIndex = stoi(input);
                        if (selectedIndex < 1 || selectedIndex > player.getItemCnt() + 1 || input.length() != to_string(selectedIndex).length())
                        {
                            throw invalid_argument("Invalid range");
                        }
                        break;
                    }
                    catch (invalid_argument &)
                    {
                        cout << "Invalid input! Please try again: ";
                    }
                }
                if (selectedIndex != player.getItemCnt() + 1) // not fight with bare hands
                    player.useItem(selectedIndex);
                cout << endl;

                // Player fights enemy
                int randAgilityEnemy = randomInt(1, 100);
                if (randAgilityEnemy < thisEnemy.getAgility() - player.getAgility()) // safe
                {
                    cout << player.getName() << " deals no damage in the attack..." << endl;
                }
                else // hit
                {
                    int randHitPlayer = randomInt(1, 100);
                    if (randHitPlayer <= player.getCritChance() * 100) // critical hit!
                    {
                        double dmg = roundToOneDec(player.getCritDmg() * max((1 - thisEnemy.getDefense() / 100), 0.0));
                        thisEnemy.hit(dmg);
                        cout << thisEnemy.getName() << " loses " << dmg << "HP!" << endl;
                    }
                    else // normal hit
                    {
                        double dmg = roundToOneDec(player.getAtk() * max((1 - thisEnemy.getDefense() / 100), 0.0));
                        thisEnemy.hit(dmg);
                        cout << thisEnemy.getName() << " loses " << dmg << "HP!" << endl;
                    }
                }
                

                // Enemy fights back if it's alive
                if (thisEnemy.getHP() > 0)
                {
                    int randAgilityPlayer = randomInt(1, 100);
                    if (randAgilityPlayer < player.getAgility() - thisEnemy.getAgility()) // safe
                    {
                        cout << thisEnemy.getName() << " deals no damage in the attack!" << endl << endl;
                    }
                    else // hit
                    {
                        int randHitEnemy = randomInt(1, 100);
                        if (randHitEnemy <= thisEnemy.getCritChance() * 100) // critical hit!
                        {
                            double dmg = roundToOneDec(thisEnemy.getCritDmg() * max((1 - player.getDefense() / 100), 0.0));
                            player.hit(dmg);
                            cout << player.getName() << " loses " << dmg << "HP..." << endl << endl;
                        }
                        else // normal hit
                        {
                            double dmg = roundToOneDec(thisEnemy.getAtk() * max((1 - player.getDefense() / 100), 0.0));
                            player.hit(dmg);
                            cout << player.getName() << " loses " << dmg << "HP..." << endl << endl;
                        }
                    }
                    
                    if (player.getHP() <= 0) // Player died
                    {
                        time_t endTime = time(0);
                        cout << player.getName() << " is defeated on layer " << i + 1  << "...\n\n";
                        cout << "Game history successfully saved in <history.txt>.";
                        
                        // Get current time
                        time_t now = time(nullptr);
                        tm *local_time = localtime(&now);
                    
                        char curTime[20];
                        strftime(curTime, sizeof(curTime), "%Y-%m-%d %H:%M:%S", local_time);
                        
                        // output file
                        ofstream history;
                        history.open("history.txt", ios::app);
                        history << curTime << " " << player.getName() << " is deafeted on layer " << i + 1 << " in " << formatSeconds(endTime - startTime) << ".\n";
                        history.close();
                        break;
                    }
                    else
                    {
                        if (selectedIndex != player.getItemCnt() + 1) // not fight with bare hands
                            player.nullifyItem(selectedIndex);
                        cout << "[ Press Enter to Continue... ]" << endl;
                        cin.ignore();
                        cin.get();
                        system("cls");
                    }
                }
                
                else // Enemy is beaten
                {
                    if (selectedIndex != player.getItemCnt() + 1) // not fight with bare hands
                        player.nullifyItem(selectedIndex);
                    beatenEnemyCnt++;
                    cout << thisEnemy.getName() << " is beaten!!!" << endl
                         << endl;
                    sleep(3000);
                    
                    // Choose item as reward before entering next layer
                    if (i + 1 != LAYER_CNT && j == enemyCnt - 1) // not the last layer and the last enemy
                    {
                        system("cls");
                        cout << "Choose an item to obtain: " << endl;
                        // Pick random three numbers not exceeding total item count
                        for (int k = 0; k < 3; k++)
                        {
                            options[k] = randomInt(0, itemList.size() - 1);
                            sleep(500);
                            cout << k + 1 << ") ";
                            itemList[options[k]].printInfo();
                        }
                        int choice = 0;
                        while (true)
                        {
                            string choice_input;
                            cin >> choice_input;
                            try
                            {
                                choice = stoi(choice_input);
                                if (choice < 1 || choice > 3 || choice_input.length() != to_string(selectedIndex).length())
                                {
                                    throw invalid_argument("Invalid range");
                                }
                                break;
                            }
                            catch (invalid_argument &)
                            {
                                cout << "Invalid input! Please try again: ";
                            }
                        }
                        player.equipItem(options[choice - 1]);
                        cout << "Congrats! You have obtained:" << endl;
                        itemList[options[choice - 1]].printInfo();
                        cout << endl;
                        player.levelUp();
                    }
                    
                    if (i + 1 == LAYER_CNT && beatenEnemyCnt == enemyCnt) // Game completion
                    {
                        time_t endTime = time(0);
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
                        cout << " ###%%%*@@#%%%@@@@@               @@@@@@@=-@@@@@@ " << endl;
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
                        cout << " ::=         @ @ @@@@%@@@@@@@@@@@%#**+*@@@@%+*@#  " << endl << endl;
                        // Get current time
                        time_t now = time(nullptr);
                        tm *local_time = localtime(&now);
                    
                        char curTime[20];
                        strftime(curTime, sizeof(curTime), "%Y-%m-%d %H:%M:%S", local_time);
                        
                        // output file
                        ofstream history;
                        history.open("history.txt", ios::app);
                        history << curTime << " " << player.getName() << " reached the top layer in " << formatSeconds(endTime - startTime) << ". Congratulations!!\n";
                        history.close();
                        cout << "Game history successfully saved in <history.txt>.";
                    }
                    else
                    {
                        if (beatenEnemyCnt < enemyCnt)
                        {
                            cout << "[ Press Enter to Continue... ]" << endl;
                            cin.ignore();
                            cin.get();
                            system("cls");
                        }
                        else
                        {
                            sleep(5000);
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
            if (player.getHP() <= 0)
                break;
        }
        if (player.getHP() <= 0)
            break;
    }

    return 0;
}
