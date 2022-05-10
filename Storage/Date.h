#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
using namespace std;

class Date {
private:
    int year;
    int month;
    int day;
public:
    Date(int year = 1900, int month = 1, int day = 1);

    Date& operator=(const Date& other);

    int get_year() const;
    int get_month() const;
    int get_day() const;

    void compare(const Date other);
};