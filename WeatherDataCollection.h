#ifndef WEATHERDATACOLLECTION_H
#define WEATHERDATACOLLECTION_H

#include "Bst.h"
#include "Map.h"
#include "WeatherRecord.h"
#include "Statistics.h"
#include <string>
#include <vector>

class WeatherDataCollection {
private:
    Bst<WeatherRecord>* weatherDataBST;
    Map<int, std::vector<WeatherRecord*>>* dataByMonth;

public:
    WeatherDataCollection();
    ~WeatherDataCollection();

    // Copy control
    WeatherDataCollection(const WeatherDataCollection& other);
    WeatherDataCollection& operator=(const WeatherDataCollection& other);

    // MAIN FUNCTIONS USING POINTERS
    void addWeatherRecord(WeatherRecord* record);
    void loadFromFiles(std::string* filename); // simple pointer interface kept

    std::vector<WeatherRecord*>* getDataForMonth(int* month) const;
    std::vector<WeatherRecord*>* getDataForYearMonth(int* year, int* month) const;
    std::vector<WeatherRecord*>* getDataForSpecificMonthYear(int* year, int* month) const;

    // Simple SPCC placeholder (pointer styles)
    double calculateSPCC(int* year, int* month, std::string* type) const;

    void displayAverageWindSpeed(int* year, int* month) const;
    void displayMonthlyTemperatures(int* year) const;
    void generateMonthlyStats(int* year, std::string* filename) const;

    void displayAllData() const;
    int getTotalRecords() const;

    // Traversal print func prototype (so cpp-scope function is declared)
    friend void printRecordForTraversal(const WeatherRecord* record);

private:
    void parseAndAddRecord(std::string* line);
    Date* parseDate(std::string* dateTimeString);
};

#endif // WEATHERDATACOLLECTION_H
