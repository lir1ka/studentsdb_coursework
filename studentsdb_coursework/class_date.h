#pragma once
#include <string>
#include <iostream>

using namespace std;

class Date {
private:
    int day, month, year;
public:
    Date() {
        setdate(1, 1, 1970);
    }
    bool isleapyear(int year) {
        if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
            return true;
        }
        else {
            return false;
        }

    }
    int setdate(int _day, int _month, int _year) {
        char months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (isleapyear(year)) {
            months[1] = 29;
        }
        if ((_day < 1) || (_day > months[_month - 1])) {
            std::cout << "11111" << std::endl;
            return 0;
        }
        if ((_month < 1) || (_month > 12)) {
            std::cout << "2222";
            return 0;
        }
        if ((_year < 0) || (_year > 2023)) {
            std::cout << "3333";
            return 0;
        }
        day = _day;
        month = _month;
        year = _year;
        return 1;

    }
    string printdate() {
        string datestring;
        if (day < 10) {
            datestring += "0" + to_string(day) + ".";
        }
        else {
            datestring += to_string(day) + ".";
        }
        if (month < 10) {
            datestring += "0" + to_string(month) + ".";
        }
        else {
            datestring += to_string(month) + ".";
        }
        datestring += to_string(year);
        return datestring;
    }
    int getyear() {
        return this->year;
    }

};
