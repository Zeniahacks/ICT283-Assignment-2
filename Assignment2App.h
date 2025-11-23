#ifndef ASSIGNMENT2APP_H
#define ASSIGNMENT2APP_H

#include "WeatherDataCollection.h"
#include <iostream>
#include <string>

class Assignment2App {
private:
    WeatherDataCollection weatherData;
    bool dataLoaded;

public:
    Assignment2App();
    void run();

private:
    void displayMenu();
    void processChoice(int choice);
    void loadData();
    void displayData();
    void displayAverageWindSpeed();
    void displayMonthlyTemperatures();
    void calculateCorrelations();
    void generateReport();
};

#endif // ASSIGNMENT2APP_H
