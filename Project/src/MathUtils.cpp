#include "MathUtils.hpp"

double Mean(std::vector<double> a) {
    double sum = 0.0;
    
    for (double x : a) {
        sum += x;
    }
    return sum / a.size();
}

double StdErr(std::vector<double> a) {
    double mean = Mean(a);
    double variance = 0.0;

    for (double x : a) {
        variance += (x - mean) * (x - mean);
    }
    variance = variance / a.size();
    return std::sqrt(variance);
}