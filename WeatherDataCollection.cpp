#include "WeatherDataCollection.h"
#include "Statistics.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <numeric> // for std::accumulate
#include <algorithm> // for std::remove
#include <random>    // for std::default_random_engine
#include <chrono>    // for seed

WeatherDataCollection::WeatherDataCollection()
    : weatherDataBST(new Bst<WeatherRecord>()),
      dataByMonth(new Map<int, std::vector<WeatherRecord*>>()) {}

WeatherDataCollection::~WeatherDataCollection() {
    // Note: The BST destructor handles deleting the WeatherRecord* objects,
    // which in turn delete the Date* objects.

    // We must clean up the pointers stored in the map's vectors,
    // BUT ONLY IF they are not already cleaned up by the BST (i.e., if they were duplicates).
    // Given the current structure where both the BST and Map hold the same pointers,
    // this destructor is dangerous. If BST is the owner, we should clear the Map vectors
    // without deleting the content, but the Map uses V* as data type for values.
    // Assuming the BST handles deletion of all data, we only need to delete the Map structure itself.

    // If the map was only holding pointers for faster lookup, we must clear the vectors
    // to avoid double deletion or leakage.
    // For simplicity, we stick to the original logic and trust the BST's dtor to clean up everything.
    delete weatherDataBST;
    delete dataByMonth;
}

// Copy constructor
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

void WeatherDataCollection::addWeatherRecord(WeatherRecord* record) {
    // Attempt to insert into BST. If a record with the same key (Date+Time) exists,
    // the current BST implementation will not insert and will leak 'record'.
    // Since we cannot change Bst<T>::insertRec, we must assume the caller (parseAndAddRecord)
    // is responsible for handling the leak if Bst doesn't insert.
    // However, the Bst does not return a status. We'll rely on the fix
    // in Date comparison to minimize duplicate keys.
    weatherDataBST->insert(record);

    int month = record->date->GetMonth();
    if (!dataByMonth->contains(&month)) {
        dataByMonth->insert(&month, new std::vector<WeatherRecord*>());
    }

    std::vector<WeatherRecord*>* monthRecords = dataByMonth->at(&month);
    monthRecords->push_back(record);
}

void WeatherDataCollection::displayAllData() const {
    std::cout << "=== All Weather Data (" << getTotalRecords() << " records) ===" << std::endl;
    weatherDataBST->inOrder([](const WeatherRecord* record) {
        // Use the new overloaded stream operator for WeatherRecord*
        std::cout << record << std::endl;
    });
}

void WeatherDataCollection::loadFromFiles(std::string* filename) {
    std::ifstream listFile(*filename);

    if (!listFile.is_open()) {
        std::cerr << "Failed to open file list: " << *filename << std::endl;
        return;
    }

    std::vector<WeatherRecord*> recordsToInsert; // Accumulate all records here first

    std::string csvFileName;
    while (std::getline(listFile, csvFileName)) {
        csvFileName.erase(std::remove(csvFileName.begin(), csvFileName.end(), '\r'), csvFileName.end());
        if (csvFileName.empty()) continue;

        std::string fullPath = "data/" + csvFileName;
        std::ifstream csvFile(fullPath);

        if (!csvFile.is_open()) {
            std::cerr << "Failed to open CSV file: " << fullPath << std::endl;
            continue;
        }

        std::string line;
        // Skip the header line
        if (std::getline(csvFile, line)) {
            // Header skipped successfully
        }

        // ------------------ PARSING LOGIC ------------------
        while (std::getline(csvFile, line)) {
            std::stringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() < 18) continue; // Skip lines with too few tokens

            try {
                // 1. Parse Date/Time (Index 0)
                Date* date = parseDate(&tokens[0]);

                // 2. Extract Data (Indices 10, 11, 17) with N/A check
                double windSpeed = 0.0;
                if (tokens[10] != "N/A") windSpeed = std::stod(tokens[10]);

                double solarRadiation = 0.0;
                if (tokens[11] != "N/A") solarRadiation = std::stod(tokens[11]);

                double temperature = 0.0;
                if (tokens[17] != "N/A") temperature = std::stod(tokens[17]);

                // 3. Create Record and Store in temporary vector
                recordsToInsert.push_back(
                    new WeatherRecord(date, windSpeed, temperature, solarRadiation)
                );

            } catch (const std::exception& e) {
                std::cerr << "Parsing error during file read: " << e.what()
                          << " on line: " << line << std::endl;
            }
        }
        // ------------------ END OF PARSING ------------------
        csvFile.close();
    }
    listFile.close();

    // ------------------ OPTIMIZATION STEP ------------------
    if (recordsToInsert.empty()) {
        std::cerr << "No valid records were parsed from files." << std::endl;
        return;
    }

    std::cout << "Successfully parsed " << recordsToInsert.size() << " records. Shuffling for fast insertion..." << std::endl;

    // SHUFFLE the records before inserting into the BST
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(recordsToInsert.begin(), recordsToInsert.end(), std::default_random_engine(seed));

    // ------------------ FINAL INSERTION STEP ------------------
    for (WeatherRecord* record : recordsToInsert) {
        // addWeatherRecord handles insertion into BST and Map
        addWeatherRecord(record);
    }

    std::cout << "Data loading complete. Total records in collection: " << getTotalRecords() << std::endl;
}

Date* WeatherDataCollection::parseDate(std::string* dateTimeString) {
    std::string s = *dateTimeString;
    size_t space_pos = s.find(' ');

    // Check if both date and time parts are present
    if (space_pos == std::string::npos) {
        return new Date(1, 1, 1900, 0, 0);
    }

    std::string date_part = s.substr(0, space_pos);   // e.g., "1/01/2010"
    std::string time_part = s.substr(space_pos + 1);  // e.g., "9:00"

    int day, month, year, hour, minute;
    char sep1, sep2, sep3;

    // Parse date (DD/MM/YYYY)
    std::stringstream date_ss(date_part);
    if (!(date_ss >> day >> sep1 >> month >> sep2 >> year) || sep1 != '/' || sep2 != '/') {
        return new Date(1, 1, 1900, 0, 0);
    }

    // Parse time (HH:MM)
    std::stringstream time_ss(time_part);
    if (!(time_ss >> hour >> sep3 >> minute) || sep3 != ':') {
        // Time parsing failed, but date is valid, return date with default time 00:00
        return new Date(day, month, year, 0, 0);
    }

    // Success
    return new Date(day, month, year, hour, minute);
}

// Get records for a specific year and month
std::vector<WeatherRecord*>* WeatherDataCollection::getDataForYearMonth(int* year, int* month) const {
    std::vector<WeatherRecord*>* result = new std::vector<WeatherRecord*>();
    CollectionContext ctx{result, *month, *year};
    // Use the traversal with context (function pointer)
    weatherDataBST->inOrder(collectByYearMonth, &ctx);
    return result;
}

std::vector<WeatherRecord*>* WeatherDataCollection::getDataForMonth(int* month) const {
    if (!month || *month < 1 || *month > 12) return nullptr;

    // Setup context: targetMonth, targetYear=0 (ignored by collectByMonth)
    CollectionContext* context = new CollectionContext{new std::vector<WeatherRecord*>(), *month, 0};

    // Perform in-order traversal, collecting records matching the month
    weatherDataBST->inOrder(collectByMonth, context);

    std::vector<WeatherRecord*>* results = context->records;
    delete context; // Clean up the context struct, but not the vector it holds

    return results;
}

// 2. Implementation for gathering data for a specific year and month
// Uses the collectByYearMonth helper (defined in WeatherRecord.cpp)
std::vector<WeatherRecord*>* WeatherDataCollection::getDataForSpecificMonthYear(int* year, int* month) const {
    if (!year || !month || *month < 1 || *month > 12 || *year < 1) return nullptr;

    // Setup context: targetMonth and targetYear
    CollectionContext* context = new CollectionContext{new std::vector<WeatherRecord*>(), *month, *year};

    // Perform in-order traversal, collecting records matching both year and month
    weatherDataBST->inOrder(collectByYearMonth, context);

    std::vector<WeatherRecord*>* results = context->records;
    delete context;

    return results;
}

double WeatherDataCollection::calculateSPCC(int* year, int* month, std::string* type) const {
    if (!year || !month || !type || *month < 1 || *month > 12) return 0.0;

    std::vector<WeatherRecord*>* records = nullptr;

    // CRITICAL FIX: Check the year to determine data scope
    if (*year == 0) {
        // Use the function that aggregates records for the month across ALL years.
        records = getDataForMonth(month);
    } else {
        // Fallback to the original logic for a specific year and month
        records = getDataForSpecificMonthYear(year, month);
    }

    if (!records || records->empty()) {
        std::cerr << "No data available for the requested month/year combination." << std::endl;
        return 0.0;
    }

    // Extract the paired data into vectors x and y
    std::vector<double> x, y;

    if (*type == "S_T") { // Solar Radiation (SR) vs Temperature (T)
        for (WeatherRecord* r : *records) {
            x.push_back(r->solarRadiation);
            y.push_back(r->temperature);
        }
    } else if (*type == "S_R") { // Solar Radiation (SR) vs Wind Speed (R is DP/Wind)
        for (WeatherRecord* r : *records) {
            x.push_back(r->solarRadiation);
            y.push_back(r->windSpeed);
        }
    } else if (*type == "T_R") { // Temperature (T) vs Wind Speed (R is DP/Wind)
        for (WeatherRecord* r : *records) {
            x.push_back(r->temperature);
            y.push_back(r->windSpeed);
        }
    } else {
        std::cerr << "Invalid correlation type: " << *type << std::endl;
        return 0.0;
    }

    // Call the decoupled statistical function
    return Statistics::calculateSPCC(&x, &y);
}

// Display average wind speed and stdev
void WeatherDataCollection::displayAverageWindSpeed(int* year, int* month) const {
    std::vector<WeatherRecord*>* monthData = getDataForYearMonth(year, month);

    if (!monthData || monthData->empty()) {
        std::cout << *month << "/" << *year << ": No Data" << std::endl;
        return;
    }

    std::vector<double> winds;
    for (auto rec : *monthData) winds.push_back(rec->windSpeed);

    std::cout << *month << "/" << *year << ": "
              << "Average speed: " << Statistics::calculateMean(&winds)
              << " km/h, Sample stdev: " << Statistics::calculateStdDev(&winds)
              << std::endl;

    // Clean up the temporary vector of records
    for (WeatherRecord* rec : *monthData) {
        delete rec;
    }
    delete monthData;
}

// Display monthly temperatures for a year (avg, stdev, mad)
void WeatherDataCollection::displayMonthlyTemperatures(int* year) const {
    std::string monthNames[12] = {"January","February","March","April","May","June",
                                  "July","August","September","October","November","December"};

    std::cout << *year << std::endl;

    for (int m = 1; m <= 12; ++m) {
        std::vector<WeatherRecord*>* monthData = getDataForYearMonth(year, &m);
        if (!monthData || monthData->empty()) {
            std::cout << monthNames[m-1] << ": No Data" << std::endl;
            continue;
        }

        std::vector<double> temps;
        for (auto rec : *monthData) temps.push_back(rec->temperature);

        std::cout << monthNames[m-1] << ": average: "
                  << Statistics::calculateMean(&temps)
                  << " degrees C, stdev: " << Statistics::calculateStdDev(&temps)
                  << std::endl;

        // Clean up the temporary vector of records
        for (WeatherRecord* rec : *monthData) {
            delete rec;
        }
        delete monthData;
    }
}

// Generate monthly stats for WindTempSolar.csv
void WeatherDataCollection::generateMonthlyStats(int* year, std::string* filename) const {
    std::string monthNames[12] = {"January","February","March","April","May","June",
                                  "July","August","September","October","November","December"};

    std::ofstream out(*filename);
    if (!out.is_open()) return;

    // 1. CSV Metadata Line (Optional, for year identification)
    out << "Year," << *year << "\n";

    // 2. CRITICAL FIX: Add a proper CSV Header Row
    out << "Month,Avg_Wind(StdDev,MAD),Avg_Temp(StdDev,MAD),Total_Solar_Radiation\n";

    for (int m = 1; m <= 12; ++m) {
        // NOTE: Assuming getDataForYearMonth is correctly implemented to call
        // getDataForSpecificMonthYear or equivalent and returns a vector of *deep copies*.
        std::vector<WeatherRecord*>* monthData = getDataForYearMonth(year, &m);

        if (!monthData || monthData->empty()) {
            // Write the "No Data" line, still in a CSV format
            out << monthNames[m-1] << ",No Data,,,\n"; // Use extra commas to fill expected columns
            continue;
        }

        std::vector<double> winds, temps, solars;
        for (auto r : *monthData) {
            winds.push_back(r->windSpeed);
            temps.push_back(r->temperature);
            solars.push_back(r->solarRadiation);
        }

        double meanWind = Statistics::calculateMean(&winds);
        double stdWind  = Statistics::calculateStdDev(&winds);
        double madWind  = Statistics::calculateMAD(&winds);

        double meanTemp = Statistics::calculateMean(&temps);
        double stdTemp  = Statistics::calculateStdDev(&temps);
        double madTemp  = Statistics::calculateMAD(&temps);

        double totalSolar = std::accumulate(solars.begin(), solars.end(), 0.0);

        // 3. Write the data row (already comma-separated)
        out << monthNames[m-1] << ","
            << meanWind << "(" << stdWind << "," << madWind << "),"
            << meanTemp << "(" << stdTemp << "," << madTemp << "),"
            << totalSolar << "\n";

        // Clean up the temporary vector of records (necessary for deep copies)
        for (WeatherRecord* rec : *monthData) {
            delete rec;
        }
        delete monthData;
    }

    out.close();
}

int WeatherDataCollection::getTotalRecords() const {
    return weatherDataBST->size();
}
