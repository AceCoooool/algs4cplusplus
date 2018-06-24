cmake_minimum_required(VERSION 3.8)
project(1_Insertion)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/BinaryInsertion.h ../head/Shell.h ../head/Merge.h ../head/MergeBU.h ../head/MergeX.h)
add_executable(1_Insertion ${SOURCE_FILES})