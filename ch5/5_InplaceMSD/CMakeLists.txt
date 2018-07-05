cmake_minimum_required(VERSION 3.8)
project(5_InplaceMSD)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h)
add_executable(5_InplaceMSD ${SOURCE_FILES})