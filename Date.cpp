// Date.cpp (CLEANED and MODIFIED to include time)
#include "Date.h"
#include <string>

Date::Date() : day(1), month(1), year(2000), hour(0), minute(0) {}
// Updated constructor implementation
Date::Date(int d, int m, int y, int h, int min) : day(d), month(m), year(y), hour(h), minute(min) {}

int Date::GetDay() const { return day; }
int Date::GetMonth() const { return month; }
int Date::GetYear() const { return year; }

void Date::SetDay(int d) { day = d; }
void Date::SetMonth(int m) { month = m; }
void Date::SetYear(int y) { year = y; }

std::string* Date::toString() const {
    // Include time in the string representation
    return new std::string(std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year) +
                           " " + std::to_string(hour) + ":" + std::to_string(minute));
}

bool Date::operator<(const Date* other) const {
    if (year != other->year)
        return year < other->year;

    if (month != other->month)
        return month < other->month;

    if (day != other->day)
        return day < other->day;

    // Compare by time for uniqueness
    if (hour != other->hour) return hour < other->hour;

    return minute < other->minute;
}

bool Date::operator>(const Date* other) const {
    return other->operator<(this);
}

bool Date::operator==(const Date* other) const {
    // Compare all components
    return day == other->day && month == other->month && year == other->year &&
           hour == other->hour && minute == other->minute;
}

std::ostream& operator<<(std::ostream& os, const Date* date) {
    // Print with time
    os << date->day << "/" << date->month << "/" << date->year << " "
       << date->hour << ":" << date->minute;
    return os;
}
