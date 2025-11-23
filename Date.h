// Date.h (CLEANED and MODIFIED to include time)
#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;
    int hour;    // Added time component
    int minute;  // Added time component

public:
    Date();
    // Updated constructor to accept time (with default values)
    Date(int d, int m, int y, int h = 0, int min = 0);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    int GetHour() const { return hour; }    // Getter for hour
    int GetMinute() const { return minute; } // Getter for minute

    void SetDay(int d);
    void SetMonth(int m);
    void SetYear(int y);
    void SetHour(int h) { hour = h; }       // Setter for hour
    void SetMinute(int min) { minute = min; } // Setter for minute

    std::string* toString() const;

    // Comparison operators (reference params so Bst comparisons compile)
    bool operator<(const Date* other) const;
    bool operator>(const Date* other) const;
    bool operator==(const Date* other) const;

    friend std::ostream& operator<<(std::ostream& os, const Date* date);
};

#endif // DATE_H
