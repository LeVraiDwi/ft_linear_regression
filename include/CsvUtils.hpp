#ifndef CSVUTILS
# define CSVUTILS
# include <iterator>
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
#include <stdexcept>

std::vector<std::vector<std::string>> readCSV(const std::string& filename);
std::vector<std::vector<int>> ParseData(std::vector<std::vector<std::string>> readData);
#endif