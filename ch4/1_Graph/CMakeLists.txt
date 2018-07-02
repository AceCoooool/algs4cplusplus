cmake_minimum_required(VERSION 3.8)
project(1_Graph)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/NonrecursiveDFS.h ../head/DepthFirstPaths.h ../head/BreadthFirstPaths.h ../head/CC.h ../head/Bipartite.h ../head/BipartiteX.h ../head/Cycle.h)
add_executable(1_Graph ${SOURCE_FILES})