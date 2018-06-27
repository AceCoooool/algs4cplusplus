cmake_minimum_required(VERSION 3.8)
project(ch3)

set(CMAKE_CXX_STANDARD 14)

include_directories(head)

add_subdirectory(1_FrequencyCounter)
add_subdirectory(2_SequentialSearchST)
add_subdirectory(3_BinarySearchST)
add_subdirectory(4_BST)
add_subdirectory(5_RedBlackBST)
add_subdirectory(6_SeparateChainingHashST)
add_subdirectory(7_LinearProbingHashST)
add_subdirectory(8_ST)