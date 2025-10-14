#ifndef LINEARREG
# define LINEARREG
# define EPSILON 1e-6
# define ITERATION 10000
# define LEARNINGRATE 0.0001

# include <vector>
# include <cmath>
# include <iostream>
# include <fstream>
# include <sstream>
# include "MathUtils.hpp"
# include "DataPoint.hpp"

struct Theta
{
    /* data */
    double x;
    double y;
};


class LinearReg
{
    
    private:
        /* data */
        std::vector<DataPoint> _data;
        Theta _theta;
        double _mean;
        double _stderr;

        double _estimatePrice(int mileage);
        void _computeTheta();
        double _computeCost();
        void _normalizeData();

    public:
        LinearReg(std::vector<DataPoint> data);
        ~LinearReg();
        std::vector<DataPoint>   GetData();
        void                     SetData(std::vector<DataPoint> data);
        Theta ProcessTheta();
};
#endif