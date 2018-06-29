cmake_minimum_required(VERSION 3.8)
project(7_CC)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h)
add_executable(7_CC ${SOURCE_FILES})