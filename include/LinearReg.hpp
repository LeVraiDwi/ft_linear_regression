#ifndef LINEARREG
# define LINEARREG

# include <vector>

class LinearReg
{
private:
    /* data */
    std::vector<std::vector<int>> _data;
    double _thetaX = 0;
    double _thetaY = 0;

    double _estimatePrice(int mileage);
    double _computeTheta(double learningRate, int gradiantIteration);
    double _computeGradiantThetaX();
    double _computeGradiantThetaY();

public:
    LinearReg(std::vector<std::vector<int>> data);
    ~LinearReg();
    std::vector<std::vector<int>>   GetData();
    void                            SetData(std::vector<std::vector<int>> data);
    std::vector<double>             ProcessTheta();
};
#endif