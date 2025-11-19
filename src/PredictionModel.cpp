#include "PredictionModel.hpp"

PredictionModel::PredictionModel(std::vector<DataPoint> data, double theta0, double theta1, double meanMile, double stderrMile, double meanPrice, double stderrPrice) {
    _data = data;
    _theta.x = theta0;
    _theta.y = theta1;
    _meanMile = meanMile;
    _stderrMile = stderrMile;
    _meanPrice = meanPrice;
    _stderrPrice = stderrPrice;
    _normalizeData();
}

PredictionModel::~PredictionModel() {
}

std::vector<DataPoint> PredictionModel::GetData() {
    return _data;
}

void PredictionModel::SetData(std::vector<DataPoint> data){
    _data = data;
}

double _estimatePrice(double mileage) {
    return _theta.x + _theta.y * mileage;
}

double PredictionModel::_estimatePrice(int mileage){
    return _theta.x + (_theta.y * mileage);
}

void PredictionModel::_normalizeData() {
    std::vector<double> mileages;
    std::vector<double> prices;

    mileages.reserve(_data.size()); // optimise les allocations
    for (const auto &d : _data)
    {
        mileages.push_back(d.mileage);
        prices.push_back(d.price);
    }
    _meanMile = Mean(mileages);
    _stderrMile = StdErr(mileages);

    _meanPrice = Mean(prices);
    _stderrPrice = StdErr(prices);

    for (auto &d : _data) {
        d.mileage = (d.mileage - _meanMile) / _stderrMile;
        d.mileage = (d.mileage - _meanPrice) / _stderrPrice;
    }
}

void Predict() {
        for (DataPoint& d : _data) {
        double price = _estimatePrice(d.mileage);
        std::cout << "Estimated price: " << price  << std::endl;
        std::cout << "Real price:      " << d.price << std::endl;
    }
}