cmake_minimum_required(VERSION 3.12)
project(10_Date)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp  ../head/Date.h ../head/ResizingArrayBag.h)
add_executable(10_Date ${SOURCE_FILES})