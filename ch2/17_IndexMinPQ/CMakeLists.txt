cmake_minimum_required(VERSION 3.8)
project(17_IndexMinPQ)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Insertion.h ../head/InsertionX.h ../head/Quick3way.h)
add_executable(17_IndexMinPQ ${SOURCE_FILES})