#include <cmath>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

// Generate random integer
int randomInt(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

// Round value to one decimal
double roundToOneDec(double value)
{
    return round(value * 10) / 10.0;
}

// Replace underscore with space
// For reading item names
string removeUnderscore(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '_')
            str[i] = ' ';
    }
    return str;
}

// Colorize text
string colorStart(int num)
{
    return "\x1B[" + to_string(num) + "m";
}

// Colorize text background
string reverseColorStart(int num)
{
    return "\033[" + to_string(num) + "m";
}

string colorEnd = "\033[0m";

// Sleep for some time
void sleep(int ms)
{
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Print character by character
void printCharByChar(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        cout << text[i];
        sleep(50);
    }
}

// For formatting times
string twoDigitsOrElse(string num)
{
    if (num.length() == 1)
        return "0" + num;
    return num;
}

// Formatting seconds to hh:mm:ss
string formatSeconds(int sec)
{
    int hours = sec / 3600;
    int minutes = (sec % 3600) / 60;
    int seconds = sec % 60;
    return twoDigitsOrElse(to_string(hours)) + ":" + twoDigitsOrElse(to_string(minutes)) + ":" + twoDigitsOrElse(to_string(seconds));
}
