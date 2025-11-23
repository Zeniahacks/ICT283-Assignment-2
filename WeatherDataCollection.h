#ifndef WEATHERDATACOLLECTION_H
#define WEATHERDATACOLLECTION_H

#include "Bst.h"
#include "Map.h"
#include "WeatherRecord.h"
#include "Statistics.h"
#include <string>
#include <vector>

/**
 * @class WeatherDataCollection
 * @brief Collection of weather data with BST storage and month mapping.
 *
 * This class manages weather data records, storing them in a Binary Search Tree (BST)
 * sorted by date, and additionally maintaining a map for quick access by month.
 * It provides functionality for loading data, performing statistical calculations,
 * and generating reports.
 */
class WeatherDataCollection {
private:
	/**
	 * @brief Binary search tree containing all WeatherRecord objects, ordered by date.
	 */
	Bst<WeatherRecord>* weatherDataBST; ///< Binary search tree of all records

	/**
	 * @brief Map where the key is the month (1-12) and the value is a vector of pointers
	 * to WeatherRecord objects that occurred in that month.
	 */
	Map<int, std::vector<WeatherRecord*>>* dataByMonth; ///< Map of month to records

public:
	/**
	 * @brief Default constructor.
	 *
	 * Initializes the internal BST and Map structures.
	 */
	WeatherDataCollection();

	/**
	 * @brief Destructor.
	 *
	 * Cleans up and deletes dynamically allocated memory for the BST and Map.
	 */
	~WeatherDataCollection();

	/**
	 * @brief Copy constructor (Rule of Three).
	 * @param other The WeatherDataCollection object to copy from.
	 */
	WeatherDataCollection(const WeatherDataCollection& other);

	/**
	 * @brief Assignment operator (Rule of Three).
	 * @param other The WeatherDataCollection object to assign from.
	 * @return WeatherDataCollection& A reference to the current object.
	 */
	WeatherDataCollection& operator=(const WeatherDataCollection& other);

	/**
	 * @brief Adds a single weather record to the collection.
	 *
	 * Inserts the record into the BST and updates the dataByMonth map.
	 * @param record A pointer to the WeatherRecord to add.
	 */
	void addWeatherRecord(WeatherRecord* record);

	/**
	 * @brief Loads weather data from a file specified by the filename.
	 *
	 * Reads, parses, and adds each record to the collection.
	 * @param filename A constant pointer to the string containing the path to the data file.
	 */
	void loadFromFiles(std::string* filename);

	/**
	 * @brief Retrieves a vector of pointers to all records for a given month, across all years.
	 * @param month A constant pointer to the integer representing the month (1-12).
	 * @return std::vector<WeatherRecord*>* A pointer to the vector of records, or null if month is invalid/no data.
	 */
	std::vector<WeatherRecord*>* getDataForMonth(int* month) const;

	/**
	 * @brief Retrieves a vector of pointers to records for a specific year and month.
	 * @param year A constant pointer to the integer representing the year.
	 * @param month A constant pointer to the integer representing the month (1-12).
	 * @return std::vector<WeatherRecord*>* A pointer to the vector of records.
	 * @note This is typically implemented by iterating through the month data and filtering by year.
	 */
	std::vector<WeatherRecord*>* getDataForYearMonth(int* year, int* month) const;

	/**
	 * @brief Retrieves a vector of pointers to records for a specific year and month (alternative function name).
	 * @param year A constant pointer to the integer representing the year.
	 * @param month A constant pointer to the integer representing the month (1-12).
	 * @return std::vector<WeatherRecord*>* A pointer to the vector of records.
	 */
	std::vector<WeatherRecord*>* getDataForSpecificMonthYear(int* year, int* month) const;

	/**
	 * @brief Calculates the Sample Pearson Correlation Coefficient (SPCC) for data points
	 * of a specific year and month, based on the correlation type requested.
	 * @param year A constant pointer to the integer representing the year (or sentinel for all years).
	 * @param month A constant pointer to the integer representing the month (1-12).
	 * @param type A constant pointer to the string indicating the correlation type (e.g., "S_T", "S_R", "T_R").
	 * @return double The calculated SPCC value.
	 */
	double calculateSPCC(int* year, int* month, std::string* type) const;

	/**
	 * @brief Displays the average wind speed and its standard deviation for a given year and month.
	 * @param year A constant pointer to the integer representing the year.
	 * @param month A constant pointer to the integer representing the month (1-12).
	 */
	void displayAverageWindSpeed(int* year, int* month) const;

	/**
	 * @brief Displays the average and standard deviation of temperature for each month of a given year.
	 * @param year A constant pointer to the integer representing the year.
	 */
	void displayMonthlyTemperatures(int* year) const;

	/**
	 * @brief Generates and writes a comprehensive monthly statistics report to a file.
	 * @param year A constant pointer to the integer representing the year.
	 * @param filename A constant pointer to the output filename string.
	 */
	void generateMonthlyStats(int* year, std::string* filename) const;

	/**
	 * @brief Displays all weather data records stored in the collection (typically using an inorder traversal of the BST).
	 */
	void displayAllData() const;

	/**
	 * @brief Returns the total number of weather records stored in the collection.
	 * @return int The count of records.
	 */
	int getTotalRecords() const;

private:
	/**
	 * @brief Internal helper function to parse a single line of raw data and create a WeatherRecord.
	 * @param line A pointer to the raw data string line.
	 */
	void parseAndAddRecord(std::string* line);

	/**
	 * @brief Internal helper function to parse a date/time string into a Date object.
	 * @param dateTimeString A pointer to the raw date/time string.
	 * @return Date* A pointer to the newly created Date object.
	 */
	Date* parseDate(std::string* dateTimeString);
};

#endif
