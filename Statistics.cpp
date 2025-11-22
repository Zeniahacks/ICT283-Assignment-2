#include "Statistics.h"
#include <cmath>

namespace Statistics {
    double calculateMean(const std::vector<double>* values) {
        if (values->empty()) return 0.0;
        double sum = 0.0;
        for (double val : *values) {
            sum += val;
        }
        return sum / values->size();
    }

    double calculateStdDev(const std::vector<double>* values) {
        if (values->size() < 2) return 0.0;
        double mean = calculateMean(values);
        double sumSq = 0.0;
        for (double val : *values) {
            sumSq += (val - mean) * (val - mean);
        }
        return std::sqrt(sumSq / (values->size() - 1));
    }

    double calculateMAD(const std::vector<double>* values) {
        if (values->empty()) return 0.0;
        double mean = calculateMean(values);
        double sumAbs = 0.0;
        for (double val : *values) {
            sumAbs += std::abs(val - mean);
        }
        return sumAbs / values->size();
    }

    double calculateSPCC(const std::vector<double>* x, const std::vector<double>* y) {
        if (x->size() != y->size() || x->size() < 2) return 0.0;

        int n = x->size();
        double sum_x = 0.0, sum_y = 0.0;
        double sum_xy = 0.0, sum_x2 = 0.0, sum_y2 = 0.0;

        for (int i = 0; i < n; ++i) {
            sum_x += (*x)[i];
            sum_y += (*y)[i];
            sum_xy += (*x)[i] * (*y)[i];
            sum_x2 += (*x)[i] * (*x)[i];
            sum_y2 += (*y)[i] * (*y)[i];
        }

        double numerator = n * sum_xy - sum_x * sum_y;
        double denominator = std::sqrt((n * sum_x2 - sum_x * sum_x) * (n * sum_y2 - sum_y * sum_y));

        if (std::abs(denominator) < 1e-10) return 0.0;
        return numerator / denominator;
    }
}
