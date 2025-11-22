#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

namespace Statistics {
    double calculateMean(const std::vector<double>* values);
    double calculateStdDev(const std::vector<double>* values);
    double calculateMAD(const std::vector<double>* values);
    double calculateSPCC(const std::vector<double>* x, const std::vector<double>* y);
}

#endif // STATISTICS_H
