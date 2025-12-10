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
    
    if (argc != 3 || argv[1] == nullptr ||  argv[2] == nullptr)
        throw new std::invalid_argument("missing mileage");

    //load csv data
    std::vector<DataPoint> data;
    double ToPredict;
    
    try
    {
        ToPredict = std::stod(argv[1]);
        std::ifstream in(argv[2]);
        if (in.is_open())
            in >> theta0 >> theta1;
        in.close();
        PredictionModel predModel(data, theta0, theta1);
        double result = predModel.Predict(ToPredict);
        std::cout << "price is: " << predModel.Predict(ToPredict) << std::endl;
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
}
