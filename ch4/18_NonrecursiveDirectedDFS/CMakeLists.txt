cmake_minimum_required(VERSION 3.8)
project(18_NonrecursiveDirectedDFS)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/EulerianCycle.h ../head/EulerianPath.h ../head/SymbolGraph.h)
add_executable(18_NonrecursiveDirectedDFS ${SOURCE_FILES})