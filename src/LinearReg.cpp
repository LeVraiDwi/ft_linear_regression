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
        cost += (pred - d.price) * (pred - d.price);
    }
    return cost / _data.size();
}

void LinearReg::_computeTheta(){
    double     tmpThataX = 0.0;
    double     tmpThataY = 0.0;
    int        dataSize = _data.size();
    
    double prevCost = 0.0;
    
    for (int i = 0; i < ITERATION; i++) {
        double errorX = 0.0;
        double errorY = 0.0;

        for (DataPoint& p: _data) {
            double pred = LinearReg::_estimatePrice(p.mileage);
            errorX += pred - p.price;
            errorY += (pred - p.price) * p.mileage;
        }
        
        errorX /= dataSize;
        errorY /= dataSize;

        _theta.x -= LEARNINGRATE * errorX;
        _theta.y -= LEARNINGRATE * errorY;

        double cost = LinearReg::_computeCost();
        
        if (i != 0 && std::fabs(prevCost - cost) <  EPSILON or (std::fabs(errorX) < MINGRAD && std::fabs(errorY) < MINGRAD)) {
            std::cout << "Converged after " << i << " iterations.\n";
            break;
        }
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
        d.price = (d.price - _meanPrice) / _stderrPrice;
    }
}

void LinearReg::_deNormalizeData() {
    _theta.y =  _theta.y * (_stderrPrice / _stderrMile);
    _theta.x = _theta.x * _stderrPrice + _meanPrice - _theta.y * _meanMile;
}

Theta LinearReg::ProcessTheta() {
    _computeTheta();
    
    _deNormalizeData();
    std::ofstream out("thetas.txt");
    out << _theta.x - _theta.y << " " << _theta.y << EOF;
    out.close();

    std::cout << "Training complete.\n";
    std::cout << "θ0 = " << _theta.x - _theta.y << ", θ1 = " << _theta.y << std::endl;
    return _theta;
}