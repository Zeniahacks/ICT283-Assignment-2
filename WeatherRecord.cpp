#include "WeatherRecord.h"
#include <iostream>

// Constructor (takes ownership of Date*)
WeatherRecord::WeatherRecord(Date* d, double ws, double temp, double sr)
    : date(d), windSpeed(ws), temperature(temp), solarRadiation(sr) {}

WeatherRecord::~WeatherRecord() {
    delete date;
}

// Deep copy
WeatherRecord::WeatherRecord(const WeatherRecord& other)
    : date(new Date(*(other.date))),
      windSpeed(other.windSpeed),
      temperature(other.temperature),
      solarRadiation(other.solarRadiation) {}

// Assignment
WeatherRecord& WeatherRecord::operator=(const WeatherRecord& other) {
    if (this != &other) {
        delete date;
        date = new Date(*(other.date));
        windSpeed = other.windSpeed;
        temperature = other.temperature;
        solarRadiation = other.solarRadiation;
    }
    return *this;
}

// Comparison operators (reference params so Bst comparisons compile)
bool WeatherRecord::operator<(const WeatherRecord& other) const {
    // date is Date*, other.date is Date*
    return date->operator<(other.date);
}

bool WeatherRecord::operator>(const WeatherRecord& other) const {
    return date->operator>(other.date);
}

bool WeatherRecord::operator==(const WeatherRecord& other) const {
    return date->operator==(other.date);
}

// print function used by Bst traversal
void printWeatherRecord(const WeatherRecord* record) {
    std::cout << record->date << " | WS: " << record->windSpeed
              << " | Temp: " << record->temperature
              << " | Solar: " << record->solarRadiation << std::endl;
}

// Traversal helpers: add deep-copied records into provided context vector
void collectByMonth(const WeatherRecord* record, void* context) {
    CollectionContext* ctx = static_cast<CollectionContext*>(context);
    if (record->date->GetMonth() == ctx->targetMonth) {
        ctx->records->push_back(new WeatherRecord(*record));
    }
}

void collectByYearMonth(const WeatherRecord* record, void* context) {
    CollectionContext* ctx = static_cast<CollectionContext*>(context);
    if (record->date->GetYear() == ctx->targetYear && record->date->GetMonth() == ctx->targetMonth) {
        ctx->records->push_back(new WeatherRecord(*record));
    }
}

// ostream operator accepting pointer (matches your pointer-oriented printing)
std::ostream& operator<<(std::ostream& os, const WeatherRecord* wr) {
    os << wr->date << " | WS: " << wr->windSpeed
       << " | Temp: " << wr->temperature
       << " | Solar: " << wr->solarRadiation;
    return os;
}
