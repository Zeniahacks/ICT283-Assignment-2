#ifndef WEATHERRECORD_H
#define WEATHERRECORD_H

#include "Date.h"
#include <vector>
#include <iostream>

/**
 * @class WeatherRecord
 * @brief Represents a single weather data observation at a specific date and time.
 *
 * This class holds the date, wind speed, temperature, and solar radiation for
 * a single recorded observation. It includes comparison operators essential for
 * storage within the Binary Search Tree (BST).
 */
class WeatherRecord {
public:
	/**
	 * @brief Pointer to the Date and time of the record.
	 */
	Date* date;

	/**
	 * @brief Wind speed recorded (in m/s).
	 */
	double windSpeed;

	/**
	 * @brief Air temperature recorded (in degrees Celsius).
	 */
	double temperature;

	/**
	 * @brief Solar radiation recorded (in W/m^2).
	 */
	double solarRadiation;

	/**
	 * @brief Constructor.
	 * @param d Pointer to the Date object.
	 * @param ws Wind speed value.
	 * @param temp Temperature value.
	 * @param sr Solar radiation value.
	 */
	WeatherRecord(Date* d, double ws, double temp, double sr);

	/**
	 * @brief Destructor.
	 *
	 * Ensures the dynamically allocated Date object is properly deleted.
	 */
	~WeatherRecord();

	/**
	 * @brief Copy constructor. Performs a deep copy of the Date object.
	 * @param other The WeatherRecord object to copy from.
	 */
	WeatherRecord(const WeatherRecord& other);

	/**
	 * @brief Assignment operator. Performs a deep copy of the Date object.
	 * @param other The WeatherRecord object to assign from.
	 * @return WeatherRecord& A reference to the current object.
	 */
	WeatherRecord& operator=(const WeatherRecord& other);

	/**
	 * @brief Less-than comparison operator.
	 *
	 * Compares two WeatherRecord objects primarily based on their Date.
	 * @param other The WeatherRecord to compare against.
	 * @return bool True if this record is chronologically less than the other.
	 */
	bool operator<(const WeatherRecord& other) const;

	/**
	 * @brief Greater-than comparison operator.
	 *
	 * Compares two WeatherRecord objects primarily based on their Date.
	 * @param other The WeatherRecord to compare against.
	 * @return bool True if this record is chronologically greater than the other.
	 */
	bool operator>(const WeatherRecord& other) const;

	/**
	 * @brief Equality comparison operator.
	 *
	 * Compares two WeatherRecord objects for equality based on their Date.
	 * @param other The WeatherRecord to compare against.
	 * @return bool True if both records have the same Date.
	 */
	bool operator==(const WeatherRecord& other) const;
};

/**
 * @brief Utility function to print the details of a WeatherRecord.
 *
 * Designed to be used as a function pointer argument in BST traversals.
 * @param record A constant pointer to the WeatherRecord to be printed.
 */
void printWeatherRecord(const WeatherRecord* record);

/**
 * @struct CollectionContext
 * @brief Context structure used during BST traversals to filter and collect records.
 *
 * This structure holds a pointer to a result vector and optional filtering
 * criteria (target month and year).
 */
struct CollectionContext {
	/**
	 * @brief Pointer to the vector where collected WeatherRecord pointers are stored.
	 */
	std::vector<WeatherRecord*>* records;

	/**
	 * @brief The target month (1-12) used for filtering.
	 */
	int targetMonth;

	/**
	 * @brief The target year used for filtering.
	 */
	int targetYear;
};

/**
 * @brief Traversal helper function to collect records based only on the target month.
 *
 * Designed to be passed to a BST traversal function.
 * @param record A constant pointer to the current WeatherRecord during traversal.
 * @param context A void pointer to a CollectionContext structure.
 */
void collectByMonth(const WeatherRecord* record, void* context);

/**
 * @brief Traversal helper function to collect records based on both the target year and month.
 *
 * Designed to be passed to a BST traversal function.
 * @param record A constant pointer to the current WeatherRecord during traversal.
 * @param context A void pointer to a CollectionContext structure.
 */
void collectByYearMonth(const WeatherRecord* record, void* context);

/**
 * @brief Overloads the stream insertion operator to print a WeatherRecord pointer.
 *
 * Outputs the record's details to the output stream.
 * @param os The output stream.
 * @param wr A constant pointer to the WeatherRecord to print.
 * @return std::ostream& Reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const WeatherRecord* wr);

#endif // WEATHERRECORD_H
