cmake_minimum_required(VERSION 3.8)
project(1_Graph)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h)
add_executable(1_Graph ${SOURCE_FILES})