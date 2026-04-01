#ifndef UTILS_H
#define UTILS_H

#include <cstddef>

namespace utils {

// Compute Euclidean distance between two points
double compute_distance(double x1, double y1, double x2, double y2);

// Compute average of array of values
double compute_average(const double* values, size_t count);

// Compute nth Fibonacci number
int fibonacci(int n);

// Check if number is prime
bool is_prime(unsigned int n);

} // namespace utils

#endif // UTILS_H
