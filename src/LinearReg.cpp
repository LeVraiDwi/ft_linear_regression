#include "LinearReg.hpp"

LinearReg::LinearReg(std::vector<DataPoint> data) {
    _data = data;
    _theta.x = 0.0;
    _theta.y = 0.0;
    _normalizeData();
}

LinearReg::~LinearReg() {
}

std::vector<DataPoint> LinearReg::GetData() {
    return _data;
}

void LinearReg::SetData(std::vector<DataPoint> data){
    _data = data;
}


double LinearReg::_estimatePrice(int mileage){
    return _theta.x + (_theta.y * mileage);
}

double LinearReg::_computeCost() {
    double cost = 0.0;
    for (DataPoint &d : _data) {
        double pred = LinearReg::_estimatePrice(d.mileage);
        cost += std::pow(pred - d.price, 2);
    }
    return cost / (2 * _data.size());
}

void LinearReg::_computeTheta(){
    double     tmpThataX = 0.0;
    double     tmpThataY = 0.0;
    int        dataSize = _data.size();
    
    double prevCost = _computeCost();
    
    for (int i = 0; i < ITERATION; i++) {
        double sumErrorX = 0.0;
        double sumErrorY = 0.0;

        for (DataPoint& p: _data) {
             double pred = LinearReg::_estimatePrice(p.mileage);
            sumErrorX += pred - p.price;
            sumErrorY += (pred - p.price) * p.mileage;
        }
        tmpThataX = (LEARNINGRATE / dataSize) * sumErrorX;
        tmpThataY = (LEARNINGRATE / dataSize) * sumErrorY;
        
        _theta.x-= tmpThataX;
        _theta.y -= tmpThataY;
        double cost = LinearReg::_computeCost();
        
        if (std::fabs(prevCost - cost) <  EPSILON)
            std::cout << "Converged after " << i << " iterations.\n";
            break;
        prevCost = cost;
    }
    
}

void LinearReg::_normalizeData() {
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

Theta LinearReg::ProcessTheta() {
    _computeTheta();
    
    std::ofstream out("thetas.txt");
    out << _theta.x - _theta.y << " " << _theta.y << " " << _meanMile << " " << _stderrMile << " " << _meanPrice << " " << _stderrPrice;
    out.close();

    std::cout << "Training complete.\n";
    std::cout << "θ0 = " << _theta.x - _theta.y << ", θ1 = " << _theta.y << std::endl;
    return _theta;
}