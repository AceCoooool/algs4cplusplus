cmake_minimum_required(VERSION 3.12)
project(13_RectHV)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp ../head/RectHV.h)
add_executable(13_RectHV ${SOURCE_FILES})