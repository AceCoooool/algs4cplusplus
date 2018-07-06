cmake_minimum_required(VERSION 3.8)
project(10_TrieSET)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/LSD.h ../head/MSD.h ../head/TST.h ../head/AmericanFlag.h ../head/AmericanFlagX.h)
add_executable(10_TrieSET ${SOURCE_FILES})