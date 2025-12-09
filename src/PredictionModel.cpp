#include "PredictionModel.hpp"

PredictionModel::PredictionModel(std::vector<DataPoint> data, double theta0, double theta1, double meanMile, double stderrMile, double meanPrice, double stderrPrice) {
    _data = data;
    _theta.x = theta0;
    _theta.y = theta1;
    _meanMile = meanMile;
    _stderrMile = stderrMile;
    _meanPrice = meanPrice;
    _stderrPrice = stderrPrice;
}

PredictionModel::~PredictionModel() {
}

std::vector<DataPoint> PredictionModel::GetData() {
    return _data;
}

void PredictionModel::SetData(std::vector<DataPoint> data){
    _data = data;
}

double PredictionModel::_estimatePrice(double mileage) {
    return _theta.x + _theta.y * mileage;
}

void PredictionModel::Predict() {
    std::ofstream out("predict.csv");
    out << "km,price\n";
    for (DataPoint& d : _data) {
        double price = _estimatePrice(d.mileage);
        out << d.mileage << "," << price << "\n";
        std::cout << "Estimated price: " << price  << std::endl;
        std::cout << "Real price:      " << d.price << std::endl;
    }
    out << std::endl;
    out.close();
}