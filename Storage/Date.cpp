#include "Date.h"

Date::Date(int y, int m, int d) : year(y), month(m), day(d) {}

int Date:: get_day() const {
    return day;
}

int Date :: get_month() const {
    return month;
}

int Date :: get_year() const {
    return year;
}

Date& Date::operator=(const Date& other) {
    year = other.year;
    month = other.month;
    day = other.day;

    return *this;
}

bool Date::compare(const Date& other) {
    if (year == other.year) {
        if (month == other.month) {
            if (day == other.day) return true;
            else return false;
        }
        else return false;
    } 
    else return false;
}

bool Date::isExpiringSoon(const Date& other) {

    if (year > other.year) return false;

    else if (year == other.year) {
        if (month > other.month) return false;

        else if (month == other.month) {
            if (other.day - day < 5) 
                return true;
            
            else return false;
        }
        else return true;
    }
    else return true;
}

bool Date::isBetween(const Date& first, const Date& second) {
    if (year >= first.year && year <= second.year) {
        if (month >= first.month && month <= second.month) {
            if (day >= first.day && day <= second.day) {
                return true;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}