cmake_minimum_required(VERSION 3.8)
project(10_Quick)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/Insertion.h ../head/InsertionX.h ../head/Quick3way.h ../head/QuickX.h ../head/QuickBentleyMcIlroy.h ../head/MaxPQ.h ../head/MinPQ.h ../head/MinPQ.h ../head/IndexMinPQ.h ../head/IndexMaxPQ.h ../head/Multiway.h ../head/Heap.h)
add_executable(10_Quick ${SOURCE_FILES})