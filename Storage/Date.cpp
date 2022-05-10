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