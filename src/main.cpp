#include "CsvUtils.hpp"
#include "LinearReg.hpp"
int main(int argc, char** argv) {
    if (argc != 2 || argv[1] == nullptr)
        throw new std::invalid_argument("missing path to csv");

    auto data = readCSV(argv[1]);
    
    auto d = ParseData(data);

    LinearReg reg(d);
    
    auto ret = reg.ProcessTheta();
    return 0;
}