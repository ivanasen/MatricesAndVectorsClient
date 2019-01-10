cmake_minimum_required(VERSION 3.13)
project(MatricesAndVectorsClient)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/lib/MatricesAndVectors/include
        ${PROJECT_SOURCE_DIR}/lib/MatricesAndVectors)

add_executable(MatricesAndVectorsClient src/main.cpp src/MatricesClient.cpp src/MatricesClient.hpp src/Client.cpp src/Client.hpp)
