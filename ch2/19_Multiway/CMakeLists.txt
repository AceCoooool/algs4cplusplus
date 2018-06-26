cmake_minimum_required(VERSION 3.8)
project(19_Multiway)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Insertion.h ../head/InsertionX.h ../head/Quick3way.h)
add_executable(19_Multiway ${SOURCE_FILES})