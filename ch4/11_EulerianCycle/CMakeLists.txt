cmake_minimum_required(VERSION 3.8)
project(11_EulerianCycle)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/EulerianCycle.h)
add_executable(11_EulerianCycle ${SOURCE_FILES})