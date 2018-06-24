cmake_minimum_required(VERSION 3.8)
project(6_Merge)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Insertion.h ../head/InsertionX.h)
add_executable(6_Merge ${SOURCE_FILES})