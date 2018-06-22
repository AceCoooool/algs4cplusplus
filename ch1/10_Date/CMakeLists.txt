cmake_minimum_required(VERSION 3.8)
project(10_Date)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/BinarySearch.h ../head/Knuth.h ../head/Counter.h ../head/StaticSetofInts.h ../head/Vector.h ../head/Date.h ../head/Transaction.h ../head/Point2D.h ../head/Interval1D.h ../head/Interval2D.h ../head/RectHV.h)
add_executable(10_Date ${SOURCE_FILES})