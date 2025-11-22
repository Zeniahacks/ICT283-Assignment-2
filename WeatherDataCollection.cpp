#include "WeatherDataCollection.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cmath>


// Forward-declare or define the traversal function used by BST (free function)
void printRecordForTraversal(const WeatherRecord* record) {
    // reuse the printWeatherRecord helper from WeatherRecord.cpp
    printWeatherRecord(record);
}

// Constructor
WeatherDataCollection::WeatherDataCollection()
    : weatherDataBST(new Bst<WeatherRecord>()),
      dataByMonth(new Map<int, std::vector<WeatherRecord*>>()) {}

// Destructor
WeatherDataCollection::~WeatherDataCollection() {
    // Clean up: delete allocated WeatherRecord pointers stored in the map
    // iterate map and delete vectors and contained WeatherRecord*
    for (auto it = dataByMonth->begin(); it != dataByMonth->end(); ++it) {
        std::vector<WeatherRecord*>& vec = it->second;
        for (WeatherRecord* wr : vec) {
            delete wr;
        }
    }
    delete dataByMonth;

    // Bst destructor should delete nodes and their WeatherRecord* since Node destructor deletes data.
    delete weatherDataBST;
}

// Copy constructor (deep-ish copy: reuses Bst copy ctor and Map copy ctor)
WeatherDataCollection::WeatherDataCollection(const WeatherDataCollection& other)
    : weatherDataBST(new Bst<WeatherRecord>(*other.weatherDataBST)),
      dataByMonth(new Map<int, std::vector<WeatherRecord*>>(*other.dataByMonth)) {}

// Assignment operator
WeatherDataCollection& WeatherDataCollection::operator=(const WeatherDataCollection& other) {
    if (this != &other) {
        delete weatherDataBST;
        delete dataByMonth;
        weatherDataBST = new Bst<WeatherRecord>(*other.weatherDataBST);
        dataByMonth = new Map<int, std::vector<WeatherRecord*>>(*other.dataByMonth);
    }
    return *this;
}

// Add a WeatherRecord* to BST and month map (takes ownership of pointer)
void WeatherDataCollection::addWeatherRecord(WeatherRecord* record) {
    if (record == nullptr) return;

    weatherDataBST->insert(record);

    int monthKey = record->date->GetMonth();
    if (!dataByMonth->contains(&monthKey)) {
        std::vector<WeatherRecord*> emptyVec;
        dataByMonth->insert(&monthKey, &emptyVec);
        // Note: above inserted a copy of the empty vector into the internal map
    }

    std::vector<WeatherRecord*>* monthRecords = dataByMonth->at(&monthKey);
    monthRecords->push_back(record);
}

// Very simple display of all data using BST traversal and the free function
void WeatherDataCollection::displayAllData() const {
    std::cout << "=== All Weather Data (" << getTotalRecords() << " records) ===" << std::endl;
    weatherDataBST->inOrder(printRecordForTraversal);
}

// Returns number of nodes in BST (calls template size())
int WeatherDataCollection::getTotalRecords() const {
    return weatherDataBST->size();
}

// Placeholder loader: provided for completeness; expects data source file listing names (not fully implemented)
void WeatherDataCollection::loadFromFiles(std::string* filename) {
    if (filename == nullptr) return;
    std::ifstream ds(*filename);
    if (!ds.is_open()) {
        std::cerr << "Could not open data source file: " << *filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(ds, line)) {
        std::string file = line;
        if (file.empty()) continue;
        // open each data file and parse (left as exercise)
        // For now, we skip actual parsing to keep compile-safe
    }
    ds.close();
}

// Very simple getDataForMonth: collects records by month (deep-copied)
std::vector<WeatherRecord*>* WeatherDataCollection::getDataForMonth(int* month) const {
    if (month == nullptr) return new std::vector<WeatherRecord*>();
    std::vector<WeatherRecord*>* result = new std::vector<WeatherRecord*>();

    CollectionContext ctx;
    ctx.records = result;
    ctx.targetMonth = *month;
    ctx.targetYear = -1;

    weatherDataBST->inOrder(collectByMonth, &ctx);
    return result;
}

std::vector<WeatherRecord*>* WeatherDataCollection::getDataForYearMonth(int* year, int* month) const {
    std::vector<WeatherRecord*>* result = new std::vector<WeatherRecord*>();
    if (year == nullptr || month == nullptr) return result;

    CollectionContext ctx;
    ctx.records = result;
    ctx.targetMonth = *month;
    ctx.targetYear = *year;

    weatherDataBST->inOrder(collectByYearMonth, &ctx);
    return result;
}

std::vector<WeatherRecord*>* WeatherDataCollection::getDataForSpecificMonthYear(int* year, int* month) const {
    return getDataForYearMonth(year, month);
}

// Simple SPCC placeholder: returns 0.0 if not implemented
double WeatherDataCollection::calculateSPCC(int* year, int* month, std::string* type) const {
    // To implement properly: gather arrays of doubles based on 'type' (S_T, S_R, T_R)
    // and call Statistics::calculateSPCC(&vecX, &vecY).
    // For now, return 0.0 to maintain compile.
    (void)year;
    (void)month;
    (void)type;

    return 0.0;
}

// Compute and display average wind speed for specific year/month (simple implementation)
void WeatherDataCollection::displayAverageWindSpeed(int* year, int* month) const {
    if (year == nullptr || month == nullptr) {
        std::cout << "Invalid year/month pointers." << std::endl;
        return;
    }

    std::vector<WeatherRecord*>* recs = getDataForSpecificMonthYear(year, month);
    if (recs->empty()) {
        std::cout << *month << "/" << *year << ": No Data" << std::endl;
        delete recs;
        return;
    }

    double sum = 0.0;
    for (WeatherRecord* r : *recs) sum += r->windSpeed;
    double avg = sum / recs->size();

    // sample stdev
    double varSum = 0.0;
    for (WeatherRecord* r : *recs) varSum += (r->windSpeed - avg) * (r->windSpeed - avg);
    double stdev = (recs->size() > 1) ? std::sqrt(varSum / (recs->size() - 1)) : 0.0;

    std::cout << *month << "/" << *year << ":" << std::endl;
    std::cout << "Average speed: " << avg << " km/h" << std::endl;
    std::cout << "Sample stdev: " << stdev << std::endl;

    // cleanup deep copies
    for (WeatherRecord* r : *recs) delete r;
    delete recs;
}

void WeatherDataCollection::displayMonthlyTemperatures(int* year) const {
    if (year == nullptr) return;
    // Minimal implementation: iterate months 1..12 and print placeholder or No Data.
    std::cout << *year << std::endl;
    for (int m = 1; m <= 12; ++m) {
        int mm = m;
        std::vector<WeatherRecord*>* recs = getDataForSpecificMonthYear(year, &mm);
        if (recs->empty()) {
            std::cout << "Month " << m << ": No Data" << std::endl;
        } else {
            double sum = 0.0;
            for (WeatherRecord* r : *recs) sum += r->temperature;
            double avg = sum / recs->size();
            // sample stdev
            double varSum = 0.0;
            for (WeatherRecord* r : *recs) varSum += (r->temperature - avg) * (r->temperature - avg);
            double stdev = (recs->size() > 1) ? std::sqrt(varSum / (recs->size() - 1)) : 0.0;
            std::cout << "Month " << m << ": average: " << avg << " degrees C, stdev: " << stdev << std::endl;
        }
        for (WeatherRecord* r : *recs) delete r;
        delete recs;
    }
}

void WeatherDataCollection::generateMonthlyStats(int* year, std::string* filename) const {
    (void)year; (void)filename;
    // left as exercise; implement file output per assignment spec
}

// Minimal helpers (parsing not fully implemented)
void WeatherDataCollection::parseAndAddRecord(std::string* line) {
    (void)line;
    // parse CSV record line and create WeatherRecord* and call addWeatherRecord(...)
}

Date* WeatherDataCollection::parseDate(std::string* dateTimeString) {
    (void)dateTimeString;
    // Return a placeholder date (should parse actual string)
    return new Date(1,1,2000);
}
