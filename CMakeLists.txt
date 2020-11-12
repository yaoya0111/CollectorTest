cmake_minimum_required(VERSION 3.5.1)
project(CollectorTtest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pthread")
set_directory_properties(${PROJECT_SOURCE_DIR}/bin)
include_directories(/usr/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
#include_directories(/usr/local/include/log4cpp)
add_executable(Collectortest
        main.cpp
        include/csapp.h src/csapp.cpp
        include/Collector.h src/Collector.cpp include/Collector.h src/Collector.cpp)