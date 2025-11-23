// WeatherRecord.cpp
//
// Implements the WeatherRecord class, which holds a single observation of weather data
// (date/time, wind speed, temperature, solar radiation), and its associated
// comparison logic and collection helpers.

#include "WeatherRecord.h"
#include <iostream>

	/**
	 * @brief Constructor for WeatherRecord.
	 *
	 * Initializes a weather record with specific values and takes ownership of the provided Date object.
	 *
	 * @param  d - Pointer to the Date object (ownership is transferred).
	 * @param  ws - Wind speed.
	 * @param  temp - Temperature.
	 * @param  sr - Solar radiation.
	 * @return void
	 */
WeatherRecord::WeatherRecord(Date* d, double ws, double temp, double sr)
    : date(d), windSpeed(ws), temperature(temp), solarRadiation(sr) {}

	/**
	 * @brief Destructor for WeatherRecord.
	 *
	 * Deletes the owned Date object.
	 *
	 * @return void
	 */
WeatherRecord::~WeatherRecord() {
    delete date;
}

	/**
	 * @brief Copy constructor for WeatherRecord.
	 *
	 * Performs a deep copy of the Date object to ensure records are independent.
	 *
	 * @param  other - The WeatherRecord object to copy from.
	 * @return void
	 */
WeatherRecord::WeatherRecord(const WeatherRecord& other)
    : date(new Date(*(other.date))),
      windSpeed(other.windSpeed),
      temperature(other.temperature),
      solarRadiation(other.solarRadiation) {}

	/**
	 * @brief Assignment operator for WeatherRecord.
	 *
	 * Cleans up the existing Date object and performs a deep copy assignment.
	 *
	 * @param  other - The WeatherRecord object to assign from.
	 * @return WeatherRecord& - Reference to the updated object.
	 */
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

	/**
	 * @brief Less-than comparison operator.
	 *
	 * Compares two WeatherRecord objects based on their Date and Time.
	 *
	 * @param  other - The other WeatherRecord to compare against.
	 * @return bool - True if this record is chronologically before the other.
	 */
bool WeatherRecord::operator<(const WeatherRecord& other) const {
    // date is Date*, other.date is Date*
    return date->operator<(other.date);
}

	/**
	 * @brief Greater-than comparison operator.
	 *
	 * Compares two WeatherRecord objects based on their Date and Time.
	 *
	 * @param  other - The other WeatherRecord to compare against.
	 * @return bool - True if this record is chronologically after the other.
	 */
bool WeatherRecord::operator>(const WeatherRecord& other) const {
    return date->operator>(other.date);
}

	/**
	 * @brief Equality comparison operator.
	 *
	 * Compares two WeatherRecord objects based on their Date and Time (used as the primary key).
	 *
	 * @param  other - The other WeatherRecord to compare against.
	 * @return bool - True if both records have the same date and time.
	 */
bool WeatherRecord::operator==(const WeatherRecord& other) const {
    return date->operator==(other.date);
}

	/**
	 * @brief Standalone print function used for generic BST traversal.
	 *
	 * Prints the details of a single weather record to standard output.
	 *
	 * @param  record - Pointer to the WeatherRecord to be printed.
	 * @return void
	 */
void printWeatherRecord(const WeatherRecord* record) {
    std::cout << record->date << " | WS: " << record->windSpeed
              << " | Temp: " << record->temperature
              << " | Solar: " << record->solarRadiation << std::endl;
}

	/**
	 * @brief Traversal helper function to collect records matching a target month across all years.
	 *
	 * If the record's month matches the context's target month, a deep copy of the record is added to the context vector.
	 * This function is designed to be used by the BST's inOrder traversal.
	 *
	 * @param  record - Pointer to the current WeatherRecord during traversal.
	 * @param  context - Pointer to the CollectionContext struct containing the target month and the results vector.
	 * @return void
	 */
void collectByMonth(const WeatherRecord* record, void* context) {
    CollectionContext* ctx = static_cast<CollectionContext*>(context);
    if (record->date->GetMonth() == ctx->targetMonth) {
        ctx->records->push_back(new WeatherRecord(*record));
    }
}

	/**
	 * @brief Traversal helper function to collect records matching a specific year and month.
	 *
	 * If the record's year and month match the context's target, a deep copy of the record is added to the context vector.
	 * This function is designed to be used by the BST's inOrder traversal.
	 *
	 * @param  record - Pointer to the current WeatherRecord during traversal.
	 * @param  context - Pointer to the CollectionContext struct containing the target year/month and the results vector.
	 * @return void
	 */
void collectByYearMonth(const WeatherRecord* record, void* context) {
    CollectionContext* ctx = static_cast<CollectionContext*>(context);
    if (record->date->GetYear() == ctx->targetYear && record->date->GetMonth() == ctx->targetMonth) {
        ctx->records->push_back(new WeatherRecord(*record));
    }
}

	/**
	 * @brief Overloads the stream insertion operator for WeatherRecord pointers.
	 *
	 * Provides a convenient way to output WeatherRecord data to an output stream.
	 *
	 * @param  os - The output stream.
	 * @param  wr - Pointer to the WeatherRecord object to output.
	 * @return std::ostream& - Reference to the output stream.
	 */
std::ostream& operator<<(std::ostream& os, const WeatherRecord* wr) {
    os << wr->date << " | WS: " << wr->windSpeed
       << " | Temp: " << wr->temperature
       << " | Solar: " << wr->solarRadiation;
    return os;
}
