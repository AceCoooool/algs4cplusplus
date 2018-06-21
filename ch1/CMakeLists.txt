cmake_minimum_required(VERSION 3.8)
project(ch1)

set(CMAKE_CXX_STANDARD 14)

#add_subdirectory(head)
include_directories(head)
include_directories(data)

add_subdirectory(1_BinarySearch)
add_subdirectory(2_RandomSeq)
add_subdirectory(3_Average)
add_subdirectory(4_Cat)
add_subdirectory(5_Knuth)
add_subdirectory(6_Counter)
add_subdirectory(7_StaticSETofInts)
add_subdirectory(8_Whitelist)
add_subdirectory(9_vector)
add_subdirectory(10_Date)
add_subdirectory(11_Transaction)
add_subdirectory(12_Point2D)

add_subdirectory(14_Interval1D)

add_subdirectory(16_Accumulator)