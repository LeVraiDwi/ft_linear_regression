cmake_minimum_required(VERSION 3.14)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header directory
include_directories(include)

# Source files
set(COMMON_SOURCES
    src/CsvUtils.cpp
    src/MathUtils.cpp
)

add_executable(train src/train.cpp src/LinearReg.cpp ${COMMON_SOURCES})
add_executable(predict src/predict.cpp ${COMMON_SOURCES})