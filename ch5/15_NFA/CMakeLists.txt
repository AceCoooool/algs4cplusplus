cmake_minimum_required(VERSION 3.8)
project(15_NFA)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h ../head/TST.h)
add_executable(15_NFA ${SOURCE_FILES})