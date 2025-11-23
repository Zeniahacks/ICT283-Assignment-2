// Assignment2App.cpp

// Implements the main application logic, user interface, and flow control
// for the weather data analysis program.

#include "Assignment2App.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

//----------------------FOLLOW THE INDENTATION USED---

	/**
	 * @brief Constructor for the Assignment2App class.
	 *
	 * Initializes the `WeatherDataCollection` object and sets the `dataLoaded` flag to false.
	 *
	 * @return void
	 */
Assignment2App::Assignment2App()
    : weatherData(), // Initialize the WeatherDataCollection object
      dataLoaded(false) // Initialize the boolean flag
{
    // Constructor body is now empty
}

	/**
	 * @brief Runs the main application loop.
	 *
	 * Displays the menu, takes user input, and processes the selected choice until the exit option (7) is chosen.
	 *
	 * @return void
	 */
void Assignment2App::run() {
    int choice = 0;

    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;
        processChoice(choice);
    }
    while (choice != 7); // EXIT OPTION
}

	/**
	 * @brief Displays the main application menu to the console.
	 *
	 * @return void
	 */
void Assignment2App::displayMenu()
{
        cout << "\n=== Assignment 2 Weather Data Analysis ===" << endl;
        cout << "1. Load Weather Data Files" << endl;
        cout << "2. Display Average Wind Speed and Standard Deviation" << endl;
        cout << "3. Display Monthly Temperature Averages and Standard Deviations" << endl;
        cout << "4. Calculate Pearson Correlation Coefficients" << endl;
        cout << "5. Generate Monthly Statistics Report" << endl;
        cout << "6. Display All Data" << endl;
        cout << "7. Exit" << endl;
        cout << "==========================================" << endl;
}

	/**
	 * @brief Processes the user's choice from the menu.
	 *
	 * Calls the appropriate member function based on the menu choice.
	 *
	 * @param  choice - The integer value corresponding to the menu option selected by the user.
	 * @return void
	 */
void Assignment2App::processChoice(int choice) {
    switch (choice) {
        case 1:
            loadData();
            break;

        case 2:
            displayAverageWindSpeed();
            break;

        case 3:
            displayMonthlyTemperatures();
            break;

        case 4:
            calculateCorrelations();
            break;

        case 5:
            generateReport();
            break;

        case 6:
            displayData();
            break;

        case 7:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
    }
}

	/**
	 * @brief Handles the loading of weather data from the user-specified file.
	 *
	 * Prompts the user for a filename, loads the data into `weatherData`, and sets `dataLoaded` to true.
	 *
	 * @return void
	 */
void Assignment2App::loadData() {
    string filename;
    cout << "Enter data filename: ";
    cin >> filename;

    weatherData.loadFromFiles(&filename);

    dataLoaded = true;
    cout << "Data loaded successfully.\n";
}

	/**
	 * @brief Displays all loaded weather data records.
	 *
	 * Calls `weatherData.displayAllData()`. Checks if data is loaded first.
	 *
	 * @return void
	 */
void Assignment2App::displayData() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    weatherData.displayAllData();
}

	/**
	 * @brief Calculates and displays the average wind speed and standard deviation for a specific year and month.
	 *
	 * Prompts for year and month, then calls `weatherData.displayAverageWindSpeed()`. Checks if data is loaded first.
	 *
	 * @return void
	 */
void Assignment2App::displayAverageWindSpeed() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    int year, month;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month (1-12): ";
    cin >> month;

    weatherData.displayAverageWindSpeed(&year, &month);
}

	/**
	 * @brief Displays the monthly temperature averages and standard deviations for a specified year.
	 *
	 * Prompts for the year, then calls `weatherData.displayMonthlyTemperatures()`. Checks if data is loaded first.
	 *
	 * @return void
	 */
void Assignment2App::displayMonthlyTemperatures() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    int year;
    cout << "Enter year: ";
    cin >> year;

    weatherData.displayMonthlyTemperatures(&year);
}

	/**
	 * @brief Calculates and displays Pearson Correlation Coefficients for the specified month across all years.
	 *
	 * Prompts for the month, calculates S_T, S_R, and T_R correlation coefficients, and displays the results. Checks if data is loaded first.
	 *
	 * @return void
	 */
void Assignment2App::calculateCorrelations() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    // Set year to 0 to signal the collection function to use ALL years for the month.
    int year = 0;
    int month;

    // Removed prompt for year
    // cout << "Enter year: ";
    // cin >> year;

    cout << "Enter month (1-12): ";
    cin >> month;

    if (cin.fail() || month < 1 || month > 12) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid month entered." << endl;
        return;
    }

    string s_t = "S_T";
    string s_r = "S_R";
    string t_r = "T_R";

    // Updated display message to reflect "All Years"
    cout << "\nSample Pearson Correlation Coefficient for Month " << month << " (All Years)" << endl;

    // Pass the sentinel year value (0)
    cout << "S_T: " << weatherData.calculateSPCC(&year, &month, &s_t) << endl;
    cout << "S_R: " << weatherData.calculateSPCC(&year, &month, &s_r) << endl;
    cout << "T_R: " << weatherData.calculateSPCC(&year, &month, &t_r) << endl;
}

	/**
	 * @brief Generates a monthly statistics report file for a specified year.
	 *
	 * Prompts for the year, then calls `weatherData.generateMonthlyStats()` to create a CSV file. Checks if data is loaded first.
	 *
	 * @return void
	 */
void Assignment2App::generateReport() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    int year;
    cout << "Enter year for report: ";
    cin >> year;

    string filename = "WindTempSolar.csv";

    weatherData.generateMonthlyStats(&year, &filename);

    cout << "Report generated: " << filename << endl;
}
