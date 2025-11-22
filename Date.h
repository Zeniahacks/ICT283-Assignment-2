#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;

    void SetDay(int d);
    void SetMonth(int m);
    void SetYear(int y);

    std::string* toString() const;  // Return pointer

    // Note: comparison operators take pointer to Date (this matches your design)
    bool operator<(const Date* other) const;
    bool operator>(const Date* other) const;
    bool operator==(const Date* other) const;

    friend std::ostream& operator<<(std::ostream& os, const Date* date); // prints date pointer nicely
};

#endif // DATE_H
