cmake_minimum_required(VERSION 3.13)
project(MatricesAndVectorsClient)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/lib/googletest/googletest/include
        ${PROJECT_SOURCE_DIR}/lib/googletest/googletest)
include_directories(${PROJECT_SOURCE_DIR}/lib/MatricesAndVectors/include
        ${PROJECT_SOURCE_DIR}/lib/MatricesAndVectors)

set(PROJECT_SOURCES src/main.cpp src/MatricesClient.cpp src/MatricesClient.hpp src/Client.cpp src/Client.hpp src/Constants.cpp src/Constants.hpp src/VariableManager.cpp src/VariableManager.hpp)
add_executable(MatricesAndVectorsClient ${PROJECT_SOURCES})

target_link_libraries(MatricesAndVectorsClient gtest gtest_main pthread)