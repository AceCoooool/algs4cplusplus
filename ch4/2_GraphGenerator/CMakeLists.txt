cmake_minimum_required(VERSION 3.8)
project(2_GraphGenerator)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Graph.h ../head/GraphGenerator.h ../head/DepthFirstSearch.h ../head/NonrecursiveDFS.h ../head/DepthFirstPaths.h ../head/BreadthFirstPaths.h ../head/CC.h ../head/Bipartite.h)
add_executable(2_GraphGenerator ${SOURCE_FILES})