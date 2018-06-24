cmake_minimum_required(VERSION 3.8)
project(7_MergeBU)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Insertion.h ../head/InsertionX.h)
add_executable(7_MergeBU ${SOURCE_FILES})