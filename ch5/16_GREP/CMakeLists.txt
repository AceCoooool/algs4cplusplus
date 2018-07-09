cmake_minimum_required(VERSION 3.8)
project(16_GREP)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h ../head/TST.h)
add_executable(16_GREP ${SOURCE_FILES})