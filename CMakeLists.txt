cmake_minimum_required(VERSION 3.10)

project(dcppa VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(spdlog REQUIRED)

add_executable(dcapp main.cpp)
target_link_libraries(dcapp PRIVATE spdlog::spdlog)