#include "Date.h"
#include <string>

Date::Date() : day(1), month(1), year(2000) {}
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

int Date::GetDay() const { return day; }
int Date::GetMonth() const { return month; }
int Date::GetYear() const { return year; }

void Date::SetDay(int d) { day = d; }
void Date::SetMonth(int m) { month = m; }
void Date::SetYear(int y) { year = y; }

std::string* Date::toString() const {
    return new std::string(std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year));
}

bool Date::operator<(const Date* other) const {
    if (year != other->year) return year < other->year;
    if (month != other->month) return month < other->month;
    return day < other->day;
}

bool Date::operator>(const Date* other) const {
    return other->operator<(this);
}

bool Date::operator==(const Date* other) const {
    return day == other->day && month == other->month && year == other->year;
}

std::ostream& operator<<(std::ostream& os, const Date* date) {
    os << date->day << "/" << date->month << "/" << date->year;
    return os;
}
