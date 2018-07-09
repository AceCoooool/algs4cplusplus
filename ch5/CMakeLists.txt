cmake_minimum_required(VERSION 3.8)
project(ch5)

set(CMAKE_CXX_STANDARD 14)

include_directories(head)
include_directories(data)

add_subdirectory(3_LSD)
add_subdirectory(4_MSD)
add_subdirectory(5_InplaceMSD)
add_subdirectory(6_Quick3string)
add_subdirectory(7_AmericanFlag)
add_subdirectory(8_AmericanFlagX)
add_subdirectory(9_TrieST)
add_subdirectory(10_TrieSET)
add_subdirectory(11_TST)
add_subdirectory(12_KMP)
add_subdirectory(13_BoyerMoore)
add_subdirectory(14_RabinKarp)
add_subdirectory(15_NFA)
add_subdirectory(16_GREP)
add_subdirectory(17_BinaryDump)


# add_subdirectory(temp)
