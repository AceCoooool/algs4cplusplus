cmake_minimum_required(VERSION 3.8)
project(10_Cycle)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/EulerianCycle.h)
add_executable(10_Cycle ${SOURCE_FILES})