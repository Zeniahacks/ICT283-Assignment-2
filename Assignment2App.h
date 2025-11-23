// Assignment2App.h

// This file is relevant for all code that you write
// Follow the commenting style in this document, based on ModelFile.h.

//Doxygen comments are placed in .h files

//---------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_APP_H
#define ASSIGNMENT_2_APP_H

//---------------------------------------------------------------------------------

#include "WeatherDataCollection.h"

using namespace std;

	/**
	 * @class Assignment2App
	 * @brief  The main application class for Assignment 2, managing the user interface and data processing flow.
	 *
	 * This class handles the main menu loop, user input, and delegates data-related tasks
	 * to the `WeatherDataCollection` object. It ensures data is loaded before analysis options are offered.
	 *
	 * @author [Your Name Here]
	 * @version 01
	 * @date 23/11/2025 Started
	 *
	 * @todo Implement input validation for all user prompts (e.g., check for non-numeric input).
	 * @todo Separate the UI logic from the data processing logic further for better modularity.
	 */

class Assignment2App
{
public:

		/**
		 * @brief Constructor for the Assignment2App class.
		 *
		 * Initializes the `WeatherDataCollection` object and sets the `dataLoaded` flag to false.
		 *
		 * @return void
		 */
	Assignment2App();

		/**
		 * @brief Runs the main application loop.
		 *
		 * Displays the menu, takes user input, and processes the selected choice until the exit option (7) is chosen.
		 *
		 * @return void
		 */
	void run();


private:
		/// An instance of the WeatherDataCollection class to hold and process all weather records.
	WeatherDataCollection weatherData;

		/// Flag to indicate whether weather data has been successfully loaded from files.
	bool dataLoaded;

		/**
		 * @brief Displays the main application menu to the console.
		 *
		 * @return void
		 */
	void displayMenu();

		/**
		 * @brief Processes the user's choice from the menu.
		 *
		 * Calls the appropriate member function based on the menu choice.
		 *
		 * @param  choice - The integer value corresponding to the menu option selected by the user.
		 * @return void
		 */
	void processChoice(int choice);

		/**
		 * @brief Handles the loading of weather data from the user-specified file.
		 *
		 * Prompts the user for a filename, loads the data into `weatherData`, and sets `dataLoaded` to true.
		 *
		 * @return void
		 */
	void loadData();

		/**
		 * @brief Displays all loaded weather data records.
		 *
		 * Calls `weatherData.displayAllData()`. Checks if data is loaded first.
		 *
		 * @return void
		 */
	void displayData();

		/**
		 * @brief Calculates and displays the average wind speed and standard deviation for a specific year and month.
		 *
		 * Prompts for year and month, then calls `weatherData.displayAverageWindSpeed()`. Checks if data is loaded first.
		 *
		 * @return void
		 */
	void displayAverageWindSpeed();

		/**
		 * @brief Displays the monthly temperature averages and standard deviations for a specified year.
		 *
		 * Prompts for the year, then calls `weatherData.displayMonthlyTemperatures()`. Checks if data is loaded first.
		 *
		 * @return void
		 */
	void displayMonthlyTemperatures();

		/**
		 * @brief Calculates and displays Pearson Correlation Coefficients for the specified month across all years.
		 *
		 * Prompts for the month, calculates S_T, S_R, and T_R correlation coefficients, and displays the results. Checks if data is loaded first.
		 *
		 * @return void
		 */
	void calculateCorrelations();

		/**
		 * @brief Generates a monthly statistics report file for a specified year.
		 *
		 * Prompts for the year, then calls `weatherData.generateMonthlyStats()` to create a CSV file. Checks if data is loaded first.
		 *
		 * @return void
		 */
	void generateReport();
};

#endif
