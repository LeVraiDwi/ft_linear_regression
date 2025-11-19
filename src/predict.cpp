#include <iostream>
#include <fstream>
#include "MathUtils.hpp"
#include "PredictionModel.hpp"
#include "CsvUtils.hpp"

double estimatePrice(double mileage, double theta0, double theta1) {
    return theta0 + theta1 * mileage;
}

int main(int argc, char** argv) {
    double theta0 = 0.0, theta1 = 0.0;
    double meanMile = 0.0, stderrMile = 0.0;
    double meanPrice = 0.0, stderrPrice = 0.0;
    
    if (argc != 2 || argv[1] == nullptr)
        throw new std::invalid_argument("missing path to csv");

    //load csv data
    std::vector<DataPoint> data = readCSV(argv[1]);
    
    // Load trained parameters
    std::ifstream in("./thetas.txt");
    if (in.is_open())
        in >> theta0 >> theta1 >> meanMile >> stderrMile >> meanPrice >> stderrPrice;
    in.close();
    PredictionModel predModel(data, theta0, theta1, meanMile, stderrMile, meanPrice, stderrPrice);
    predModel.Predict();
}
