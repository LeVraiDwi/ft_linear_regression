#include "LinearReg.hpp"

LinearReg::LinearReg(std::vector<std::vector<int>> data) {
    _data = data;
}

LinearReg::~LinearReg() {
}

std::vector<std::vector<int>>   LinearReg::GetData() {
    return _data;
}

void                            LinearReg::SetData(std::vector<std::vector<int>> data){
    _data = data;
}


double LinearReg::_estimatePrice(int mileage){
    return _thetaX + (_thetaY * mileage);
}

double LinearReg::_computeTheta(double learningRate, int gradiantIteration){
    double  tmpThataX;
    double  tmpThataY;
    int     dataSize = _data.size();

    for (int i = 0; i < gradiantIteration; i++) {
        
        tmpThataX = learningRate * _computeGradiantThetaX();
        tmpThataY = learningRate * _computeGradiantThetaY();
        _thetaX = tmpThataX;
        _thetaY = tmpThataY;
    }
    
}

double LinearReg::_computeGradiantThetaX() {
    int     dataSize = _data.size();
    double  sum = 0;
    
    for (std::vector<int> v : _data) {
        sum += LinearReg::_estimatePrice(v[0]) * - v[1];
    }
    return sum / dataSize;
}

double LinearReg::_computeGradiantThetaY() {
    int     dataSize = _data.size();
    double  sum = 0;
    
    for (std::vector<int> v : _data) {
        sum += (LinearReg::_estimatePrice(v[0]) * - v[1]) * v[0];
    }
    return sum / dataSize;
}

std::vector<double> LinearReg::ProcessTheta() {
    _computeTheta(0.1, 1000);
    return {_thetaX, _thetaY};
}