cmake_minimum_required(VERSION 3.8)
project(6_BreadthFirstPaths)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h)
add_executable(6_BreadthFirstPaths ${SOURCE_FILES})