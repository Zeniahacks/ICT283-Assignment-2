#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

/**
 * @class Date
 * @brief Represents a specific point in time (day, month, year, hour, minute).
 *
 * This class stores date and time components and provides utility methods
 * for access, modification, string conversion, and comparison, specifically
 * designed to work with pointer comparisons needed by the Bst class.
 */
class Date {
private:
	int day;    ///< The day of the month (1-31).
	int month;  ///< The month of the year (1-12).
	int year;   ///< The year (e.g., 2024).
	int hour;   ///< The hour of the day (0-23).
	int minute; ///< The minute of the hour (0-59).

public:
	/**
	 * @brief Default constructor. Initializes date/time members to default values (e.g., 0).
	 */
	Date();

	/**
	 * @brief Parameterized constructor.
	 * @param d The day.
	 * @param m The month.
	 * @param y The year.
	 * @param h The hour (default is 0).
	 * @param min The minute (default is 0).
	 */
	Date(int d, int m, int y, int h = 0, int min = 0);

	/**
	 * @brief Gets the day component of the Date object.
	 * @return int The day.
	 */
	int GetDay() const;

	/**
	 * @brief Gets the month component of the Date object.
	 * @return int The month.
	 */
	int GetMonth() const;

	/**
	 * @brief Gets the year component of the Date object.
	 * @return int The year.
	 */
	int GetYear() const;

	/**
	 * @brief Gets the hour component of the Date object.
	 * @return int The hour.
	 */
	int GetHour() const { return hour; }

	/**
	 * @brief Gets the minute component of the Date object.
	 * @return int The minute.
	 */
	int GetMinute() const { return minute; }

	/**
	 * @brief Sets the day component of the Date object.
	 * @param d The new day value.
	 */
	void SetDay(int d);

	/**
	 * @brief Sets the month component of the Date object.
	 * @param m The new month value.
	 */
	void SetMonth(int m);

	/**
	 * @brief Sets the year component of the Date object.
	 * @param y The new year value.
	 */
	void SetYear(int y);

	/**
	 * @brief Sets the hour component of the Date object.
	 * @param h The new hour value.
	 */
	void SetHour(int h) { hour = h; }

	/**
	 * @brief Sets the minute component of the Date object.
	 * @param min The new minute value.
	 */
	void SetMinute(int min) { minute = min; }

	/**
	 * @brief Converts the Date object into a dynamically allocated string representation.
	 * @return std::string* Pointer to the new string object containing the formatted date/time.
	 */
	std::string* toString() const;

	// Comparison operators (reference params so Bst comparisons compile)
	/**
	 * @brief Comparison operator to check if this Date is chronologically less than another.
	 * @param other A constant pointer to the other Date object.
	 * @return bool True if this Date is earlier than the other, false otherwise.
	 */
	bool operator<(const Date* other) const;

	/**
	 * @brief Comparison operator to check if this Date is chronologically greater than another.
	 * @param other A constant pointer to the other Date object.
	 * @return bool True if this Date is later than the other, false otherwise.
	 */
	bool operator>(const Date* other) const;

	/**
	 * @brief Comparison operator to check if this Date is chronologically equal to another.
	 * @param other A constant pointer to the other Date object.
	 * @return bool True if both Date objects represent the exact same time, false otherwise.
	 */
	bool operator==(const Date* other) const;

	/**
	 * @brief Friend function for output stream operator overload.
	 * @param os The output stream reference.
	 * @param date A constant pointer to the Date object to output.
	 * @return std::ostream& Reference to the output stream.
	 */
	friend std::ostream& operator<<(std::ostream& os, const Date* date);
};

#endif // DATE_H
