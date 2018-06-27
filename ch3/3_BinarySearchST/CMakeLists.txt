cmake_minimum_required(VERSION 3.8)
project(3_BinarySearchST)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/ST.h ../head/SequentialSearchST.h)
add_executable(3_BinarySearchST ${SOURCE_FILES})