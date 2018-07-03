cmake_minimum_required(VERSION 3.8)
project(10_Cycle)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/EulerianCycle.h ../head/EulerianPath.h ../head/SymbolGraph.h ../head/Digraph.h ../head/DirectedDFS.h ../head/NonrecursiveDirectedDFS.h ../head/DepthFirstDirectedPaths.h ../head/BreadthFirstDirectedPaths.h ../head/DirectedCycle.h ../head/DirectedCycleX.h ../head/DigraphGenerator.h ../head/DirectedEulerianCycle.h ../head/DirectedEulerianPath.h ../head/DepthFirstOrder.h ../head/Topological.h ../head/TopologicalX.h)
add_executable(10_Cycle ${SOURCE_FILES})