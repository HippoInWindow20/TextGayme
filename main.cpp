#include "character.h"
#include <stdlib.h>
#include <cstdlib>
#include <fstream>

using namespace std;

const int LAYER_CNT = 10;

vector<Item> itemList; // a list of all items

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
    

    string name;
    cout << "Please name your character: ";
    getline(cin, name);
    Player player(name);

    system("cls");

    // World building
    printCharByChar("\"Go upwards!\"\n");
    printCharByChar("An unclear yet familiar voice resonates in " + player.getName() + "'s dream.\n");
    printCharByChar("At that time, " + player.getName() + " was no older than ten.\n");
    printCharByChar("Food and resources are lacking in the lower layers.\n");
    printCharByChar("The only hope is to move upwards.\n");
    printCharByChar("All " + player.getName() + " can do is to aim for the top layer.\n");
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
        printCharByChar("There are 1 or 2 randomly decided enemies on each layer.\n");
        printCharByChar("You may choose an item as reward after defeating each enemy.\n");
        printCharByChar("There are 3 types of items: projectile, weapon, and potion.\n");
        printCharByChar("Projectile is single-use item, only effective in the round of attack.\n");
        printCharByChar("Weapon is infinite-use item, also only effective in the round of attack.\n");
        printCharByChar("Potion is single-use item, values will add to your attributes once obtained.\n");
        printCharByChar("Enemies will become stronger as you reach higher layers.\n");
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
            cout << "Moving to Layer 1.";
            sleep(1000);
            system("cls");
            cout << "Moving to Layer 1..";
            sleep(1000);
            system("cls");
            cout << "Moving to Layer 1...";
            sleep(1000);
            system("cls");
        }
        if (i + 1 == LAYER_CNT)
        {
            printCharByChar("Oh, behold the guardian of the gold, the dragon of magic light.\n");
            printCharByChar("In front of " + player.getName() + " is our legend, our hero.\n");
            printCharByChar("His name is...\n");
            sleep(100);
            cout << colorStart(33) << " _____                                             _____ " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << "( ___ )-------------------------------------------( ___ )" << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |                                             |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |   _          _                              |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |  | |   ___  | | __  _   _   _ __     __ _   |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |  | |  / __| | |/ / | | | | | '_ \\   / _` |  |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |  | | | (__  |   <  | |_| | | | | | | (_| |  |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |  |_|  \\___| |_|\\_\\  \\__,_| |_| |_|  \\__, |  |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |   |                                     |___/   |   | " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << " |___|                                             |___| " << colorEnd << endl;
            sleep(100);
            cout << colorStart(33) << "(_____)-------------------------------------------(_____)" << colorEnd << endl << endl;
            sleep(100);
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
                thisEnemy = Enemy(i + 1, "lckung", 150, 300, 0.3, 30, 30, 400);

            while (thisEnemy.getHP() > 0) // Player fights
            {
                cout << "Current Layer: " << i + 1 << endl;
                cout << "Eneny In This Layer: " << j+1 << '/' << enemyCnt << endl << endl;
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
                    cout << thisEnemy.getName() << " dodged " << player.getName() << "'s attack!" << endl;
                }
                else // hit
                {
                    int randHitPlayer = randomInt(1, 100);
                    if (randHitPlayer <= player.getCritChance() * 100) // critical hit!
                    {
                        double dmg = roundToOneDec(player.getCritDmg() * max((1 - thisEnemy.getDefense() / 100), 0.0));
                        thisEnemy.hit(dmg);
                        cout << "Crit! " << thisEnemy.getName() << " loses " << dmg << "HP!" << endl;
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
                        cout << player.getName() << " dodged " << thisEnemy.getName() << "'s attack!" << endl
                             << endl;
                    }
                    else // hit
                    {
                        int randHitEnemy = randomInt(1, 100);
                        if (randHitEnemy <= thisEnemy.getCritChance() * 100) // critical hit!
                        {
                            double dmg = roundToOneDec(thisEnemy.getCritDmg() * max((1 - player.getDefense() / 100), 0.0));
                            player.hit(dmg);
                            cout << "Crit! " << player.getName() << " loses " << dmg << "HP..." << endl
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
                        if (i + 1 == LAYER_CNT){
                            printCharByChar("Maybe Homework 10 is too hard for you...\n");
                            printCharByChar("lckung gives you an F for this course...\n");
                            printCharByChar("You can enroll this course next year!\n");
                            printCharByChar("But I'm worried about your GPA...\n");
                        }
                        else {
                            printCharByChar(player.getName() + " is defeated on layer " + to_string(i + 1) + "...\n");
                            printCharByChar("The journey ends here... Have better luck next time!\n");
                        }
                        // Get current time
                        time_t now = time(nullptr);
                        tm *local_time = localtime(&now);

                        char curTime[20];
                        strftime(curTime, sizeof(curTime), "%Y-%m-%d %H:%M:%S", local_time);

                        // output file
                        ofstream history;
                        history.open("history.txt", ios::app);
                        history << curTime << " " << player.getName() << " is defeated on layer " << i + 1 << " after a long journey which lasts " << formatSeconds(endTime - startTime) << ".\n";
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

                    // Choose item as reward before fighting with next enemy / entering next layer
                    if (i + 1 != LAYER_CNT) // not the last layer
                    {
                        system("cls");
                        cout << "Choose an item to obtain: " << endl;
                        // Pick random three numbers not exceeding total item count
                        for (int k = 0; k < 3; k++)
                        {
                            if (i <= 4)
                                options[k] = randomInt(0, itemList.size() - 7); // 6 items exclusive for layer 6 - 9
                            else
                                options[k] = randomInt(5, itemList.size() - 1); // 5 items exclusive for layer 1 - 5
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
                        player.equipItem(itemList, options[choice - 1]);
                        cout << "Congrats! You have obtained: " << endl;
                        itemList[options[choice - 1]].printInfo();
                        cout << endl;
                        
                        if (j == enemyCnt - 1)
                            player.levelUp();
                    }

                    if (i + 1 == LAYER_CNT && beatenEnemyCnt == enemyCnt) // Game completion
                    {
                        time_t endTime = time(0);
                        sleep(2000);
                        system("cls");
                        printCharByChar(colorStart(32) + "CONGRATULATIONS!\n" + colorEnd);
                        printCharByChar("After a long journey, " + player.getName() + " finally reaches the top layer.\n");
                        printCharByChar("It's a tranquil and peaceful place covered with white snow.\n");
                        printCharByChar("However, there is no food found on the top layer.\n");
                        printCharByChar("With nowhere else to go, " + player.getName() + " decides to enjoy their last days with the remaining food.\n");
                        printCharByChar("\"Living sure has been great...\"\n");
                        printCharByChar("\"I should eat now and then take a nap. After that, maybe think about something...\"\n");
                        sleep(2000);
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
                            cout << "Moving to Layer " << i + 2 << ".";
                            sleep(1000);
                            system("cls");
                            cout << "Moving to Layer " << i + 2 << "..";
                            sleep(1000);
                            system("cls");
                            cout << "Moving to Layer " << i + 2 << "...";
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
