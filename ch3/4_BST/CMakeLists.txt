cmake_minimum_required(VERSION 3.8)
project(4_BST)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/ST.h ../head/SequentialSearchST.h)
add_executable(4_BST ${SOURCE_FILES})