cmake_minimum_required(VERSION 3.8)
project(7_AmericanFlag)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h)
add_executable(7_AmericanFlag ${SOURCE_FILES})