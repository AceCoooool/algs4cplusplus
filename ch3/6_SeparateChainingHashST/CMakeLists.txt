cmake_minimum_required(VERSION 3.8)
project(6_SeparateChainingHashST)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/ST.h ../head/SequentialSearchST.h)
add_executable(6_SeparateChainingHashST ${SOURCE_FILES})