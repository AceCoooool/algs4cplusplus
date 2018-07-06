cmake_minimum_required(VERSION 3.8)
project(9_TrieST)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h)
add_executable(9_TrieST ${SOURCE_FILES})