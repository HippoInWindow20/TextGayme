#include <cmath>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <chrono>
using namespace std;

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