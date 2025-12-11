#ifndef LINEARREG
# define LINEARREG
# define EPSILON 1e-9
# define MINGRAD 1e-6
# define ITERATION 100000
# define LEARNINGRATE 0.01

# include <vector>
# include <cmath>
# include <iostream>
# include <fstream>
# include <sstream>
# include <algorithm>
# include "MathUtils.hpp"
# include "DataPoint.hpp"
# include "Theta.hpp"

class LinearReg
{
    
    private:
        /* data */
        std::vector<DataPoint> _data;
        std::vector<Theta> _theta;
        double _meanMile;
        double _stderrMile;
        double _meanPrice;
        double _stderrPrice;

        double _estimatePrice(const Theta t, int mileage);
        void _computeTheta();
        double _computeCost(const Theta t);
        void _normalizeData();
        void _deNormalizeData(Theta *theta);

    public:
        LinearReg(std::vector<DataPoint> data);
        ~LinearReg();
        std::vector<DataPoint>  GetData();
        void                    SetData(std::vector<DataPoint> data);
        void                    ProcessTheta();
        void                    ExportTheta();
};
#endif