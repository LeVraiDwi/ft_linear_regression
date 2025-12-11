#include "LinearReg.hpp"

LinearReg::LinearReg(std::vector<DataPoint> data) {
    _data = data;
    _theta.push_back(new Theta(0.0,0.0));
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


double LinearReg::_estimatePrice(const Theta t, int mileage) {
    return t.x + (t.y * mileage);
}

double LinearReg::_computeCost(const Theta t) {
    double cost = 0.0;
    for (DataPoint &d : _data) {
        double pred = LinearReg::_estimatePrice(t, d.mileage);
        cost += (pred - d.price) * (pred - d.price);
    }
    return cost / _data.size();
}

void LinearReg::_computeTheta(){
    double      tmpThataX = 0.0;
    double      tmpThataY = 0.0;
    Theta       theta(0.0, 0.0);
    int         dataSize = _data.size();
    
    double prevCost = 0.0;
    
    for (int i = 0; i < ITERATION; i++) {
        double errorX = 0.0;
        double errorY = 0.0;

        for (DataPoint& p: _data) {
            double pred = _estimatePrice(theta, p.mileage);
            errorX += pred - p.price;
            errorY += (pred - p.price) * p.mileage;
        }
        
        errorX /= dataSize;
        errorY /= dataSize;

        theta.x -= LEARNINGRATE * errorX; 
        theta.y -= LEARNINGRATE * errorY;
        Theta toAdd = new Theta(&theta);
        _deNormalizeData(&toAdd);
        _theta.push_back(toAdd);

        double cost = LinearReg::_computeCost(toAdd);
        
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

void LinearReg::_deNormalizeData(Theta *theta) {
    theta->y =  theta->y * (_stderrPrice / _stderrMile);
    theta->x = theta->x * _stderrPrice + _meanPrice - theta->y * _meanMile;
}

void LinearReg::ProcessTheta() {
    _computeTheta();
    std::cout << "Training complete.\n";
}

void LinearReg::ExportTheta() {
    std::ofstream out("thetasHisto.csv");
    
    out << "theta0,theta1\n";
    for(Theta t : _theta) {
        out << t.x << "," << t.y << "\n";
    }
    out.close();
    std::cout << "historic of thetas export to thetasHisto.csv" << std::endl;
    
    std::ofstream ThetaOut("thetas.txt");
    
    ThetaOut << _theta.crbegin()->x << " " << _theta.crbegin()->y << "\n";
    ThetaOut.close();
    std::cout << "theta export to thetas.txt" << std::endl;
}