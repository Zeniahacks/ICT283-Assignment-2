// Date.cpp

// Implements the Date class methods for initialization, access, comparison,
// and string representation of a specific timestamp.

#include "Date.h"
#include <string>

	/**
	 * @brief Default constructor.
	 *
	 * Initializes date to 1/1/2000 at 00:00.
	 *
	 * @return void
	 */
Date::Date() : day(1), month(1), year(2000), hour(0), minute(0) {}

	/**
	 * @brief Parameterized constructor.
	 *
	 * @param  d - The day (1-31).
	 * @param  m - The month (1-12).
	 * @param  y - The year.
	 * @param  h - The hour (0-23).
	 * @param  min - The minute (0-59).
	 * @return void
	 */
Date::Date(int d, int m, int y, int h, int min) : day(d), month(m), year(y), hour(h), minute(min) {}

	/**
	 * @brief Retrieves the day component.
	 *
	 * @return int - The day (1-31).
	 */
int Date::GetDay() const { return day; }

	/**
	 * @brief Retrieves the month component.
	 *
	 * @return int - The month (1-12).
	 */
int Date::GetMonth() const { return month; }

	/**
	 * @brief Retrieves the year component.
	 *
	 * @return int - The year.
	 */
int Date::GetYear() const { return year; }

	/**
	 * @brief Sets the day component.
	 *
	 * @param  d - The new day value.
	 * @return void
	 */
void Date::SetDay(int d) { day = d; }

	/**
	 * @brief Sets the month component.
	 *
	 * @param  m - The new month value.
	 * @return void
	 */
void Date::SetMonth(int m) { month = m; }

	/**
	 * @brief Sets the year component.
	 *
	 * @param  y - The new year value.
	 * @return void
	 */
void Date::SetYear(int y) { year = y; }

	/**
	 * @brief Returns a pointer to a string representation of the date and time.
	 *
	 * The format is "D/M/Y H:MIN".
	 *
	 * @return std::string* - Pointer to the formatted date string.
	 */
std::string* Date::toString() const {
	// Include time in the string representation
	return new std::string(std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year) +
						   " " + std::to_string(hour) + ":" + std::to_string(minute));
}

	/**
	 * @brief Overloads the less-than operator for Date comparison.
	 *
	 * Compares dates based on year, then month, day, hour, and minute.
	 *
	 * @param  other - Pointer to the Date object to compare against.
	 * @return bool - True if this date is chronologically before the other date.
	 */
bool Date::operator<(const Date* other) const {
	if (year != other->year)
		return year < other->year;

	if (month != other->month)
		return month < other->month;

	if (day != other->day)
		return day < other->day;

	// Compare by time for uniqueness
	if (hour != other->hour) return hour < other->hour;

	return minute < other->minute;
}

	/**
	 * @brief Overloads the greater-than operator for Date comparison.
	 *
	 * @param  other - Pointer to the Date object to compare against.
	 * @return bool - True if this date is chronologically after the other date.
	 */
bool Date::operator>(const Date* other) const {
	return other->operator<(this);
}

	/**
	 * @brief Overloads the equality operator for Date comparison.
	 *
	 * @param  other - Pointer to the Date object to compare against.
	 * @return bool - True if all date and time components are equal.
	 */
bool Date::operator==(const Date* other) const {
	// Compare all components
	return day == other->day && month == other->month && year == other->year &&
		   hour == other->hour && minute == other->minute;
}

	/**
	 * @brief Overloads the stream insertion operator (<<) for Date objects.
	 *
	 * Prints the date and time in D/M/Y H:MIN format to the output stream.
	 *
	 * @param  os - The output stream.
	 * @param  date - Pointer to the Date object to print.
	 * @return std::ostream& - Reference to the output stream.
	 */
std::ostream& operator<<(std::ostream& os, const Date* date) {
	// Print with time
	os << date->day << "/" << date->month << "/" << date->year << " "
	   << date->hour << ":" << date->minute;
	return os;
}
