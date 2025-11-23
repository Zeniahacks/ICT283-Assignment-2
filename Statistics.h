#ifndef STATISTICS_H
#define STATISTICS_H

#include <vector>

/**
 * @brief Namespace for statistical calculations using pointer-based vectors.
 *
 * This namespace provides several static functions for common statistical
 * calculations, specifically designed to accept constant pointers to
 * standard C++ vectors of doubles.
 */
namespace Statistics {
	/**
	 * @brief Calculates the arithmetic mean (average) of a set of values.
	 * @param values A constant pointer to the vector of double values.
	 * @return double The calculated mean. Returns 0.0 if the vector is empty.
	 */
	double calculateMean(const std::vector<double>* values);

	/**
	 * @brief Calculates the sample standard deviation of a set of values.
	 * @param values A constant pointer to the vector of double values.
	 * @return double The calculated standard deviation. Returns 0.0 if size < 2.
	 */
	double calculateStdDev(const std::vector<double>* values);

	/**
	 * @brief Calculates the Median Absolute Deviation (MAD) of a set of values.
	 *
	 * Note: The actual median calculation must be handled within the implementation.
	 * @param values A constant pointer to the vector of double values.
	 * @return double The calculated Median Absolute Deviation.
	 */
	double calculateMAD(const std::vector<double>* values);

	/**
	 * @brief Calculates the Sample Pearson Correlation Coefficient (SPCC) between two data sets.
	 * @param x A constant pointer to the vector of double values for the X variable.
	 * @param y A constant pointer to the vector of double values for the Y variable.
	 * @return double The calculated SPCC. Returns 0.0 if the vectors are not the same size or size < 2.
	 */
	double calculateSPCC(const std::vector<double>* x, const std::vector<double>* y);
}

#endif // STATISTICS_H
