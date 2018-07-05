cmake_minimum_required(VERSION 3.8)
project(ch5)

set(CMAKE_CXX_STANDARD 14)

include_directories(head)
include_directories(data)

add_subdirectory(3_LSD)
add_subdirectory(4_MSD)
add_subdirectory(5_InplaceMSD)

