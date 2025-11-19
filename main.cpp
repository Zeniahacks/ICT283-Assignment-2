#include <iostream>
#include <string>
#include "WeatherData.h"

using namespace std;

class Assignment2App
{
private:
    WeatherDataCollection weatherData;
    bool dataLoaded;

public:
    Assignment2App() : weatherData(), dataLoaded(false) {}

    void run()
    {
        int choice;
        do
        {
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;
            processChoice(choice);
        }

        while (choice != 8);
    }

private:

    void displayMenu()
    {
        cout << "\n=== Assignment 2 Weather Data Analysis ===" << endl;
        cout << "1. Load Weather Data Files" << endl;
        cout << "2. Display Average Wind Speed and Standard Deviation" << endl;
        cout << "3. Display Monthly Temperature Averages and Standard Deviations" << endl;
        cout << "4. Calculate Pearson Correlation Coefficients" << endl;
        cout << "5. Generate Monthly Statistics Report" << endl;
        cout << "6. Display Data Structure Information" << endl;
        cout << "7. Display All Data" << endl;
        cout << "8. Exit" << endl;
        cout << "==========================================" << endl;
    }

    // Switch choices following the above display menu as provided
    void processChoice(int choice)
    {
        switch(choice)
        {
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
            displayStructuredinfo();
            break;
        case 7:
            displayData();
            break;
        case 8:
            cout << "Exiting application. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }


    void loadData()
    {
        string filename;
        cout << "Enter the data source file name: ";
        cin >> filename;

        weatherData.loadFromFiles(filename);
        dataLoaded = true;
        cout << "File name found. Data loading completed." << endl;
    }

    void displayData()
    {
        if (!dataLoaded)
        {
            cout << "Please load the data first (Option 1)." << endl;
            return;
        }

        weatherData.displayAllData();
    }

    /// Tasked for assignment 2
    void displayAverageWindSpeed() {
        if (!dataLoaded) {
            cout << "Please load the data first (Option 1)." << endl;
            return;
        }

        int year, month;
        cout << "Enter year: ";
        cin >> year;
        cout << "Enter month (1-12): ";
        cin >> month;

        if (month < 1 || month > 12) {
            cout << "Invalid month. Please try again." << endl;
            return;
        }

        weatherData.displayAverageWindSpeed(year, month);
    }

    /// Also tasked for assignment 2
    void displayMonthlyTemperatures() {
        if (!dataLoaded) {
            cout << "Please load the data first (Option 1)." << endl;
            return;
        }

        int year;
        cout << "Enter year: ";
        cin >> year;

        weatherData.displayMonthlyTemperatures(year);
    }

    void calculateCorrelations()
    {
        if (!dataLoaded)
        {
            cout << "Please load the data first (Option 1)." << endl;
            return;
        }

        int month;
        cout << "Enter month (1-12): ";
        cin >> month;

        if (month < 1 || month > 12)
        {
            cout << "You have entered an invalid month. Please try again." << endl;
            return;
        }

        cout << "\nSample Pearson Correlation Coefficient for Month" << endl;
        cout << "S_T: " << weatherData.calculateSPCC(month, "S_T") << endl;
        cout << "S_R: " << weatherData.calculateSPCC(month, "S_R") << endl;
        cout << "T_R: " << weatherData.calculateSPCC(month, "T_R") << endl;
    }

    void generateReport()
    {
        if (!dataLoaded)
        {
            cout << "Please load the data first (Option 1)." << endl;
            return;
        }

        int year;
        cout << "Enter year for report: ";
        cin >> year;

        weatherData.generateMonthlyStats(year, "WindTempSolar.csv");
        cout << "Report generated: WindTempSolar.csv" << endl;
    }

    void displayStructuredinfo()
    {
        if (!dataLoaded)
        {
            cout << "Please load the data first (Option 1)." << endl;
            return;
        }

        cout << "\n=== Data Structure Information ===" << endl;
        cout << "Total records: " << weatherData.getTotalRecords() << endl;

        // Demonstration of map usage
        Map<string, int> testMap;
        testMap.insert("test", 42);
        cout << "Custom Map test: " << testMap.at("test") << endl;
    }
};




int main()
{
    cout << "ICT283 Lab 11 Exercise" << endl;
    cout << "======================" << endl;

    Assignment2App app;
    app.run();

    return 0;
}
