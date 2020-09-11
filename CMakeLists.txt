cmake_minimum_required(VERSION 3.10)

project(dcppa VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(spdlog REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_executable(dcppa main.cpp ${SOURCES})

target_link_libraries(dcppa spdlog::spdlog)
target_link_libraries(dcppa opus)