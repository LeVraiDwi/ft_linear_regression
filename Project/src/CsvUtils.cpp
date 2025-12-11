#include "CsvUtils.hpp"

std::vector<DataPoint> readCSV(const std::string& filename) {
    std::vector<DataPoint> data;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return data;
    }
    
    //skip first line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        double mileage, price;
        char comma;

        if (ss >> mileage >> comma >> price)
            data.push_back({mileage, price});
    }

    file.close();
    return data;
}