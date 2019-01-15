cmake_minimum_required(VERSION 3.13)
project(MatricesAndVectorsClient)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/lib/googletest/googletest/include
        ${PROJECT_SOURCE_DIR}/lib/googletest/googletest)
include_directories(${PROJECT_SOURCE_DIR}/lib/MatricesAndVectors/include
        ${PROJECT_SOURCE_DIR}/lib/MatricesAndVectors)
include_directories(${PROJECT_SOURCE_DIR}/include)

set(PROJECT_SOURCES src/main.cpp src/MatricesClient.cpp src/Client.cpp include/Client.hpp src/Constants.cpp src/VariableManager.cpp)
add_executable(MatricesAndVectorsClient ${PROJECT_SOURCES})

target_link_libraries(MatricesAndVectorsClient gtest gtest_main pthread)