cmake_minimum_required(VERSION 3.8)
project(13_LookupCSV)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/ST.h ../head/SequentialSearchST.h ../head/BinarySearchST.h ../head/BST.h ../head/RedBlackBST.h ../head/SeparateChainingHashST.h ../head/LinearProbingHashST.h ../head/SET.h)
add_executable(13_LookupCSV ${SOURCE_FILES})