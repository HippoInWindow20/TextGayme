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

string removeUnderscore(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '_')
            str[i] = ' ';
    }
    return str;
}

string colorStart(int num)
{
    return "\x1B[" + to_string(num) + "m";
}

string reverseColorStart(int num)
{
    return "\033[" + to_string(num) + "m";
}

string colorEnd = "\033[0m";

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
    // getters
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

vector<Item> itemList; // a list of all items

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
        this->atk = roundToOneDec(atk * 1.25);
        cout << this->atk << endl;
        cout << "Crit Damage: " << this->critDmg << " -> ";
        this->critDmg = roundToOneDec(critDmg * 1.25);
        cout << this->critDmg << endl;
        cout << "Crit Chance: " << this->critChance * 100 << "% -> ";
        this->critChance += 0.015;
        cout << this->critChance * 100 << "%" << endl;
        cout << "Agility: " << this->agility << " -> ";
        this->agility += 2;
        cout << this->agility << endl;
        cout << "Defense: " << this->defense << " -> ";
        this->defense = roundToOneDec(defense * 1.2);
        cout << this->defense << endl;
        cout << "HP: " << this->hp << " -> ";
        this->hp += randomInt(40, 80);
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

//////////////////////////////////////////////////////////////////////////////////////

class Enemy : public Character
{
protected:
    int level;

public:
    Enemy(string name, int layer);
    Enemy(string name, double atk, double critDmg, double critChance, double agility, double defense, double hp);
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
// Enemy constructor with custom values
Enemy::Enemy(string name, double atk, double critDmg, double critChance, double agility, double defense, double hp)
{
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

string twoDigitsOrElse(string num)
{
    if (num.length() == 1)
        return "0" + num;
    return num;
}

string formatSeconds(int sec)
{
    int hours = sec / 3600;
    int minutes = (sec % 3600) / 60;
    int seconds = sec % 60;
    return twoDigitsOrElse(to_string(hours)) + ":" + twoDigitsOrElse(to_string(minutes)) + ":" + twoDigitsOrElse(to_string(seconds));
}

int main()
{
    // generate items
    srand(time(0));
    int itemCnt = 0;
    fstream itemFile;
    itemFile.open("items.txt");
    while (!itemFile.eof())
    {
        string itemName;
        double atkChange;
        double critChange;
        double critChanceChange;
        double agilityChange;
        double defenseChange;
        double hpChange;
        int type;
        itemFile >> itemName >> atkChange >> critChange >> critChanceChange >> agilityChange >> defenseChange >> hpChange >> type;
        Item newItem(removeUnderscore(itemName), atkChange, critChange, critChanceChange, agilityChange, defenseChange, hpChange, type);
        itemList.push_back(newItem);
        itemCnt++;
    }
    int options[3] = {0};

    // read enemy names
    fstream mobFile;
    mobFile.open("mobNames.txt");
    vector<string> mobName;
    string fileInput;
    while (!mobFile.eof())
    {
        mobFile >> fileInput;
        mobName.push_back(fileInput);
    }

    // Starting menu
    system("cls");
    cout << colorStart(31) << "! WARNING !\n"
         << colorEnd;
    cout << "This game is a parody of the manga series Girls' Last Tour.\n";
    cout << "It contains major spoilers for the series. However, keep in mind that some elements aren't based on the series.\n\n";

    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);

    system("cls");

    // World building
    printCharByChar("\"Go upwards!\"\n");
    sleep(50);
    printCharByChar("An unclear yet familiar voice resonates in ");
    printCharByChar(player.getName());
    printCharByChar("'s dream.\n");
    sleep(50);
    printCharByChar("At that time, " + player.getName() + " was no older than ten.\n");
    sleep(50);
    printCharByChar("Food and resources are lacking in the lower layers.\n");
    sleep(50);
    printCharByChar("The only hope is to move upwards.\n");
    sleep(50);
    printCharByChar("All " + player.getName() + " can do is to aim for the top layer.\n");
    sleep(50);
    printCharByChar("Please lend " + player.getName() + " a helping hand!\n\n");
    sleep(500);

    cout << colorStart(93) << "Enter 1 to directly start the game.\n"
         << colorEnd;
    cout << colorStart(93) << "Enter 2 to read instructions before starting the game.\n\n"
         << colorEnd;
    int ans = 0;
    while (true)
    {
        string ansInput;
        cin >> ansInput;
        try
        {
            ans = stoi(ansInput);
            if (ans < 1 || ans > 2 || ansInput.length() != to_string(ans).length())
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
    if (ans == 2)
    {
        system("cls");
        printCharByChar("There are a total of " + to_string(LAYER_CNT) + " layers. Your goal is to reach the top layer.\n");
        printCharByChar("There will be 1 to 3 enemies in each layer, which are randomly generated.\n");
        printCharByChar("You may choose an item as reward after passing each layer.\n");
        printCharByChar("There are 3 types of items: projectile, weapon, and potion.\n");
        printCharByChar("Projectile is single-use item, only effective in the round of attack.\n");
        printCharByChar("Weapon is infinite-use item, also only effective in the round of attack.\n");
        printCharByChar("Potion is single-use item, values will add to your attributes once obtained.\n");
        printCharByChar("Enemies will become stronger as you reach higher layer.\n");
        printCharByChar("And of course, there is a final boss awaits...\n"); 
        printCharByChar("Good luck and have fun!\n\n");

        sleep(500);
        cout << colorStart(93) << "[ Press Enter to start the game ]" << colorEnd << endl;
        cin.ignore();
        cin.get();
    }

    time_t startTime = time(0);
    // Game
    for (int i = 0; i < LAYER_CNT; i++)
    {
        // Generate random number of enemies
        int enemyCnt = randomInt(1, 2);
        if (i + 1 == LAYER_CNT)
            enemyCnt = 1;
        int beatenEnemyCnt = 0;

        system("cls");

        if (i == 0)
        {
            cout << "Moving to First Layer.";
            sleep(1000);
            system("cls");
            cout << "Moving to First Layer..";
            sleep(1000);
            system("cls");
            cout << "Moving to First Layer...";
            sleep(1000);
            system("cls");
        }
        if (i + 1 == LAYER_CNT)
        {
            printCharByChar("Oh behold, the guardian of the gold, the dragon of magic light.\n");
            printCharByChar("In front of " + player.getName() + " is our legend, our hero.\n");
            printCharByChar("His name is....\n");
            cout << colorStart(33) << "=============================================" << colorEnd << endl;
            cout << colorStart(33) << ".__          __                       ._._._." << colorEnd << endl;
            cout << colorStart(33) << "|  |   ____ |  | ____ __  ____    ____| | | |" << colorEnd << endl;
            cout << colorStart(33) << "|  | _/ ___\\|  |/ /  |  \\/    \\  / ___\\ | | |" << colorEnd << endl;
            cout << colorStart(33) << "|  |_\\  \\___|    <|  |  /   |  \\/ /_/  >|\\|\\|" << colorEnd << endl;
            cout << colorStart(33) << "|____/\\___  >__|_ \\____/|___|  /\\___  /______" << colorEnd << endl;
            cout << colorStart(33) << "        \\/     \\/          \\//_____/ \\/\\/\\/  " << colorEnd << endl;
            cout << colorStart(33) << "===================(lckung)==================" << colorEnd << endl;
            printCharByChar("Now, " + player.getName() + " has to fight with him in order to reach the top layer.\n");
            printCharByChar("It must be an epic fierce battle...");
            sleep(2000);
            system("cls");
        }

        // Start fighting
        for (int j = 0; j < enemyCnt; j++)
        {
            // Generate enemy
            Enemy thisEnemy(mobName[randomInt(0, mobName.size() - 1)], i + 1);
            if (i + 1 == LAYER_CNT)
                thisEnemy = Enemy("lckung", 150, 300, 0.3, 30, 30, 400);

            while (thisEnemy.getHP() > 0) // Player fights
            {
                cout << "Current Layer: " << i + 1 << endl
                     << endl;
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
                        cout << thisEnemy.getName() << " deals no damage in the attack!" << endl
                             << endl;
                    }
                    else // hit
                    {
                        int randHitEnemy = randomInt(1, 100);
                        if (randHitEnemy <= thisEnemy.getCritChance() * 100) // critical hit!
                        {
                            double dmg = roundToOneDec(thisEnemy.getCritDmg() * max((1 - player.getDefense() / 100), 0.0));
                            player.hit(dmg);
                            cout << player.getName() << " loses " << dmg << "HP..." << endl
                                 << endl;
                        }
                        else // normal hit
                        {
                            double dmg = roundToOneDec(thisEnemy.getAtk() * max((1 - player.getDefense() / 100), 0.0));
                            player.hit(dmg);
                            cout << player.getName() << " loses " << dmg << "HP..." << endl
                                 << endl;
                        }
                    }

                    if (player.getHP() <= 0) // Player died
                    {
                        time_t endTime = time(0);
                        sleep(2000);
                        system("cls");
                        printCharByChar(colorStart(31) + "GAME OVER!\n" + colorEnd);
                        printCharByChar(player.getName() + " is defeated on layer " + to_string(i + 1) + "...\n");
                        printCharByChar("Have better luck next time!\n");
                        printCharByChar("- Nuko(?)\n");
                        // Get current time
                        time_t now = time(nullptr);
                        tm *local_time = localtime(&now);

                        char curTime[20];
                        strftime(curTime, sizeof(curTime), "%Y-%m-%d %H:%M:%S", local_time);

                        // output file
                        ofstream history;
                        history.open("history.txt", ios::app);
                        history << curTime << " " << player.getName() << " is deafeted on layer " << i + 1 << " after a long journey which lasts " << formatSeconds(endTime - startTime) << ".\n";
                        history.close();

                        sleep(500);
                        cout << "\nGame history successfully saved in <history.txt>.";
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
                        printCharByChar(colorStart(32) + "YOU WIN!\n" + colorEnd);
                        sleep(2500);
                        printCharByChar("After a long journey, " + player.getName() + " finally reaches the top layer.\n");
                        sleep(2500);
                        printCharByChar("It's a tranquil and peaceful place covered with white snow.\n");
                        sleep(2500);
                        printCharByChar("However, there is no food found on the top layer.\n");
                        sleep(2500);
                        printCharByChar("With nowhere else to go, " + player.getName() + " decides to enjoy their last days with the remaining food.\n");
                        sleep(2500);
                        printCharByChar("\"Living sure has been great...\"\n");
                        sleep(2500);
                        printCharByChar("\"I should eat now and then take a nap. After that, maybe think about something...\"\n");
                        sleep(2500);
                        cout << endl;
                        cout << " ###%%%*@@#%%%@@@@@@  +++++++++  @@@@@@@@=-@@@@@@ " << endl;
                        cout << " #%%%%%*@@#%@@@@@  .=+++++++++++=.  @@@@@@@@@@@@@ " << endl;
                        cout << " %%%%%%#@@#@@@@ .=+=--==++++++++===-  #@@%%%+-@@@ " << endl;
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
                        cout << " ::=         @ @ @@@@%@@@@@@@@@@@%#**+*@@@@%+*@#  " << endl
                             << endl;
                        // Get current time
                        time_t now = time(nullptr);
                        tm *local_time = localtime(&now);

                        char curTime[20];
                        strftime(curTime, sizeof(curTime), "%Y-%m-%d %H:%M:%S", local_time);

                        // output file
                        ofstream history;
                        history.open("history.txt", ios::app);
                        history << curTime << " " << player.getName() << " reached the top layer after a long journey which lasts " << formatSeconds(endTime - startTime) << ". Congratulations!!\n";
                        history.close();
                        cout << "Game history successfully saved in <history.txt>.";
                    }
                    else
                    {
                        if (beatenEnemyCnt < enemyCnt)
                        {
                            cout << "[ Next Enemy Is Approaching. Press Enter to Continue... ]" << endl;
                            cin.ignore();
                            cin.get();
                            system("cls");
                        }
                        else
                        {
                            sleep(5000);
                            system("cls");
                            cout << "Moving to Layer " << i+2 << ".";
                            sleep(1000);
                            system("cls");
                            cout << "Moving to Layer " << i+2 << "..";
                            sleep(1000);
                            system("cls");
                            cout << "Moving to Layer " << i+2 << "...";
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
