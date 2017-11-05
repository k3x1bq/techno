cmake_minimum_required(VERSION 3.8)
project(multimap)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp multimap.cpp multimap.hpp)
add_executable(multimap ${SOURCE_FILES})