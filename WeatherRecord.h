#ifndef WEATHERRECORD_H
#define WEATHERRECORD_H

#include "Date.h"
#include <vector>
#include <iostream>

class WeatherRecord {
public:
    Date* date;
    double windSpeed;
    double temperature;
    double solarRadiation;

    WeatherRecord(Date* d, double ws, double temp, double sr);
    ~WeatherRecord();

    // Copy constructor and assignment operator (deep copy of Date)
    WeatherRecord(const WeatherRecord& other);
    WeatherRecord& operator=(const WeatherRecord& other);

    // Comparison operators must be reference-based so Bst template can call them like: *a < *b
    bool operator<(const WeatherRecord& other) const;
    bool operator>(const WeatherRecord& other) const;
    bool operator==(const WeatherRecord& other) const;
};

// Print function used by Bst traversal (function pointer)
void printWeatherRecord(const WeatherRecord* record);

// CollectionContext for traversal-with-context helpers (if needed)
struct CollectionContext {
    std::vector<WeatherRecord*>* records;
    int targetMonth;
    int targetYear;
};

// Traversal helper functions (used with pointer-style traversals)
void collectByMonth(const WeatherRecord* record, void* context);
void collectByYearMonth(const WeatherRecord* record, void* context);

// Stream operator that takes pointer (matches pointer-usage elsewhere)
std::ostream& operator<<(std::ostream& os, const WeatherRecord* wr);

#endif // WEATHERRECORD_H
