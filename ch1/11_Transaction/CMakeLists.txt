cmake_minimum_required(VERSION 3.12)
project(11_Transaction)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp ../head/Transaction.h)
add_executable(11_Transaction ${SOURCE_FILES})