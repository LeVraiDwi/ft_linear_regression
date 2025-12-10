#include "CsvUtils.hpp"
#include "LinearReg.hpp"

int main(int argc, char** argv) {
    if (argc != 2 || argv[1] == nullptr)
        throw new std::invalid_argument("missing path to csv");

    try
    {
        std::vector<DataPoint> data = readCSV(argv[1]);
    
        LinearReg reg(data);

        reg.ProcessTheta();
        reg.ExportTheta();
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(1);
    }
    
}