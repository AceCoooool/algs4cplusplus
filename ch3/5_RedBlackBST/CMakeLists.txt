cmake_minimum_required(VERSION 3.8)
project(5_RedBlackBST)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/ST.h ../head/SequentialSearchST.h)
add_executable(5_RedBlackBST ${SOURCE_FILES})