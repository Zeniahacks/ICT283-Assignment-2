// Statistics.cpp

// Implements various statistical calculation functions, including mean,
// standard deviation, mean absolute deviation (MAD), and Sample Pearson
// Correlation Coefficient (SPCC).

#include "Statistics.h"
#include <cmath>

namespace Statistics {
	/**
	 * @brief Calculates the arithmetic mean (average) of a set of values.
	 *
	 * @param  values - Pointer to the vector of double values.
	 * @return double - The calculated mean, or 0.0 if the vector is empty.
	 */
	double calculateMean(const std::vector<double>* values) {
		if (values->empty()) return 0.0;
		double sum = 0.0;
		for (double val : *values) {
			sum += val;
		}
		return sum / values->size();
	}

	/**
	 * @brief Calculates the Sample Standard Deviation of a set of values.
	 *
	 * Uses the N-1 method (Bessel's correction).
	 *
	 * @param  values - Pointer to the vector of double values.
	 * @return double - The calculated standard deviation, or 0.0 if there is less than two values.
	 */
	double calculateStdDev(const std::vector<double>* values) {
		if (values->size() < 2) return 0.0;
		double mean = calculateMean(values);
		double sumSq = 0.0;
		for (double val : *values) {
			sumSq += (val - mean) * (val - mean);
		}
		return std::sqrt(sumSq / (values->size() - 1));
	}

	/**
	 * @brief Calculates the Mean Absolute Deviation (MAD) of a set of values.
	 *
	 * The average of the absolute differences between each value and the mean.
	 *
	 * @param  values - Pointer to the vector of double values.
	 * @return double - The calculated MAD, or 0.0 if the vector is empty.
	 */
	double calculateMAD(const std::vector<double>* values) {
		if (values->empty()) return 0.0;
		double mean = calculateMean(values);
		double sumAbs = 0.0;
		for (double val : *values) {
			sumAbs += std::abs(val - mean);
		}
		return sumAbs / values->size();
	}

	/**
	 * @brief Calculates the Sample Pearson Correlation Coefficient (SPCC) between two datasets.
	 *
	 * @param  x - Pointer to the first vector (independent variable).
	 * @param  y - Pointer to the second vector (dependent variable).
	 * @return double - The calculated SPCC (range [-1, 1]), or 0.0 if datasets are too small or unequal size.
	 */
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
