#ifndef PREDICTIONMODEL
# define PREDICTIONMODEL

# include <vector>
# include <cmath>
# include <iostream>
# include <fstream>
# include <sstream>
# include "MathUtils.hpp"
# include "DataPoint.hpp"
# include "Theta.hpp"

class PredictionModel
{
    
    private:
        /* data */
        std::vector<DataPoint> _data;
        Theta _theta;
        double _meanMile;
        double _stderrMile;
        double _meanPrice;
        double _stderrPrice;

        double _estimatePrice(int mileage);
        void _normalizeData();

    public:
        PredictionModel(std::vector<DataPoint> data, double theta0, double theta1, double meanMile, double stderrMile, double meanPrice, double stderrPrice);
        ~PredictionModel();
        std::vector<DataPoint>   GetData();
        void                     SetData(std::vector<DataPoint> data);
        void                     Predict();
};
#endif