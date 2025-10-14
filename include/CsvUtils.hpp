#ifndef CSVUTILS
# define CSVUTILS
# include <iterator>
# include <iostream>
# include <fstream>
# include <sstream>
# include <vector>
# include <string>
# include "DataPoint.hpp"
# include <stdexcept>

std::vector<DataPoint> readCSV(const std::string& filename);
#endif