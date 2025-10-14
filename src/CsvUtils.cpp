#include "CsvUtils.hpp"

std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();
    return data;
}

std::vector<std::vector<int>> ParseData(std::vector<std::vector<std::string>> readData) {
    std::vector<std::vector<int>> retTable = {};
    for (const auto& row : readData) {
        if ( row.size() == 2 && !row[1].empty() && !row[0].empty() )
            try {
                retTable.push_back({std::stoi(row[0]), std::stoi(row[1])});
            }
            catch (...) {
                std::cout << "fail to parse " << row[0] << " " << row[1] << std::endl;
            }
    }
    return retTable;
}