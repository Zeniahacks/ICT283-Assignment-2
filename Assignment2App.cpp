#include "Assignment2App.h"
#include <iostream>
#include <string>

using namespace std;

Assignment2App::Assignment2App() {
    dataLoaded = false;
}

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

void Assignment2App::displayMenu() {
    cout << "\n===== WEATHER DATA ANALYSIS SYSTEM =====\n";
    cout << "1. Load Data\n";
    cout << "2. Display All Data\n";
    cout << "3. Display Average Wind Speed\n";
    cout << "4. Display Monthly Temperatures\n";
    cout << "5. Calculate Correlations\n";
    cout << "6. Generate Monthly Stats\n";
    cout << "7. Exit Program\n";
    cout << "========================================\n";
}

void Assignment2App::processChoice(int choice) {
    switch (choice) {
        case 1:
            loadData();
            break;

        case 2:
            displayData();
            break;

        case 3:
            displayAverageWindSpeed();
            break;

        case 4:
            displayMonthlyTemperatures();
            break;

        case 5:
            calculateCorrelations();
            break;

        case 6:
            generateReport();
            break;

        case 7:
            cout << "Exiting program..." << endl;
            break;

        default:
            cout << "Invalid choice! Try again." << endl;
    }
}

void Assignment2App::loadData() {
    string filename;
    cout << "Enter data filename: ";
    cin >> filename;

    weatherData.loadFromFiles(&filename);

    dataLoaded = true;
    cout << "Data loaded successfully.\n";
}

void Assignment2App::displayData() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    weatherData.displayAllData();
}

void Assignment2App::displayAverageWindSpeed() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    int year, month;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month (1–12): ";
    cin >> month;

    weatherData.displayAverageWindSpeed(&year, &month);
}

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

void Assignment2App::calculateCorrelations() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    int year, month;
    cout << "Enter year: ";
    cin >> year;
    cout << "Enter month (1–12): ";
    cin >> month;

    string s_t = "S_T";
    string s_r = "S_R";
    string t_r = "T_R";

    cout << "\nSample Pearson Correlation Coefficient for " << month << "/" << year << endl;
    cout << "S_T: " << weatherData.calculateSPCC(&year, &month, &s_t) << endl;
    cout << "S_R: " << weatherData.calculateSPCC(&year, &month, &s_r) << endl;
    cout << "T_R: " << weatherData.calculateSPCC(&year, &month, &t_r) << endl;
}

void Assignment2App::generateReport() {
    if (!dataLoaded) {
        cout << "Please load the data first (Option 1)." << endl;
        return;
    }

    int year;
    cout << "Enter year for report: ";
    cin >> year;

    string filename = "MonthlyStats_" + to_string(year) + ".txt";

    weatherData.generateMonthlyStats(&year, &filename);

    cout << "Report generated: " << filename << endl;
}
