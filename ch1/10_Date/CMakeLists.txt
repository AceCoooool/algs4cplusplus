cmake_minimum_required(VERSION 3.8)
project(10_Date)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ../head/BinarySearch.h ../head/Knuth.h ../head/Counter.h ../head/StaticSetofInts.h ../head/Vector.h ../head/Date.h ../head/Transaction.h ../head/Point2D.h ../head/Interval1D.h ../head/Interval2D.h ../head/RectHV.h ../head/Accumulator.h ../head/ResizingArrayStack.h ../head/LinkedStack.h ../head/Stack.h ../head/ResizingArrayQueue.h ../head/LinkedQueue.h ../head/Queue.h ../head/ResizingArrayBag.h ../head/LinkedBag.h ../head/Bag.h ../head/Stopwatch.h ../head/ThreeSum.h ../head/ThreeSumFast.h ../head/DoublingTest.h ../head/QuickFindUF.h ../head/QuickUnionUF.h ../head/WeightedQuickUnionUF.h ../head/UF.h ../head/LinearRegression.h)
add_executable(10_Date ${SOURCE_FILES})