cmake_minimum_required(VERSION 3.14)
project(Ft_LinearRegression VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header directory
include_directories(include)

add_executable(Train)
target_sources(Train
    PRIVATE
        ./src/train.cpp
        ./src/CsvUtils.cpp
        ./src/MathUtils.cpp
        ./src/LinearReg.cpp
)

add_executable(Predict)
target_sources(Predict
    PRIVATE
        ./src/predict.cpp
        ./src/CsvUtils.cpp
        ./src/MathUtils.cpp
        ./src/PredictionModel.cpp
)