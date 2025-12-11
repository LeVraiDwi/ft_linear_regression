#include "PredictionModel.hpp"

PredictionModel::PredictionModel(std::vector<DataPoint> data, double theta0, double theta1) {
    _data = data;
    _theta.x = theta0;
    _theta.y = theta1;
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

double PredictionModel::Predict(double mileage) {
    return _estimatePrice(mileage);
}