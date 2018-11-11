cmake_minimum_required(VERSION 3.12)
project(12_Point2D)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp ../head/Point2D.h)
add_executable(12_Point2D ${SOURCE_FILES})