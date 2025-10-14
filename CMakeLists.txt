cmake_minimum_required(VERSION 3.14)
project(MyProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header directory
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/CsvUtils.cpp
    src/LinearReg.cpp
)

add_executable(MyProject ${SOURCES})