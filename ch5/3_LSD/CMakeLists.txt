cmake_minimum_required(VERSION 3.8)
project(3_LSD)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h ../head/InplaceMSD.h ../head/Quick3string.h ../head/TrieST.h ../head/temp.h ../head/TrieSET.h)
add_executable(3_LSD ${SOURCE_FILES})