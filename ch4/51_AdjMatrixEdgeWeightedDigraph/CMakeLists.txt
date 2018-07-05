cmake_minimum_required(VERSION 3.8)
project(51_AdjMatrixEdgeWeightedDigraph)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/EulerianCycle.h ../head/EulerianPath.h ../head/SymbolGraph.h)
add_executable(51_AdjMatrixEdgeWeightedDigraph ${SOURCE_FILES})