#ifndef WEATHERDATACOLLECTION_H
#define WEATHERDATACOLLECTION_H

#include "Bst.h"
#include "Map.h"
#include "WeatherRecord.h"
#include "Statistics.h"
#include <string>
#include <vector>

/**
 * @brief Collection of weather data with BST storage and month mapping.
 */
class WeatherDataCollection {
private:
    Bst<WeatherRecord>* weatherDataBST; ///< Binary search tree of all records
    Map<int, std::vector<WeatherRecord*>>* dataByMonth; ///< Map of month to records

public:
    WeatherDataCollection();
    ~WeatherDataCollection();

    WeatherDataCollection(const WeatherDataCollection& other);
    WeatherDataCollection& operator=(const WeatherDataCollection& other);

    void addWeatherRecord(WeatherRecord* record);
    void loadFromFiles(std::string* filename);

    std::vector<WeatherRecord*>* getDataForMonth(int* month) const;
    std::vector<WeatherRecord*>* getDataForYearMonth(int* year, int* month) const;
    std::vector<WeatherRecord*>* getDataForSpecificMonthYear(int* year, int* month) const;

    double calculateSPCC(int* year, int* month, std::string* type) const;

    void displayAverageWindSpeed(int* year, int* month) const;
    void displayMonthlyTemperatures(int* year) const;
    void generateMonthlyStats(int* year, std::string* filename) const;

    void displayAllData() const;
    int getTotalRecords() const;

private:
    void parseAndAddRecord(std::string* line);
    Date* parseDate(std::string* dateTimeString);
};

#endif
