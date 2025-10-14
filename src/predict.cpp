#include <iostream>
#include <fstream>
#include "MathUtils.hpp"
#include "CsvUtils.hpp"

double estimatePrice(double mileage, double theta0, double theta1) {
    return theta0 + theta1 * mileage;
}

int main(int argc, char** argv) {
    double theta0 = 0.0, theta1 = 0.0;
    
    if (argc != 2 || argv[1] == nullptr)
        throw new std::invalid_argument("missing path to csv");

    //load csv data
    std::vector<DataPoint> data = readCSV(argv[1]);
    
    // Load trained parameters
    std::ifstream in("/sgoinfre/goinfre/Perso/tcosse/ft_linear_regression/thetas.txt");
    if (in.is_open())
        in >> theta0 >> theta1;
    in.close();

    for (DataPoint& d : data) {
        double price = estimatePrice(d.mileage, theta0, theta1);
        std::cout << "Estimated price: " << price  << std::endl;
        std::cout << "Real price:      " << d.price << std::endl;
    }
}
