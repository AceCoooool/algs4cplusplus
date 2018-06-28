# Algorithms
Algorithms, 4th edition textbook code (using c++)

**Note：**

1. based on STL Library
2. using C++14
3. **Not support** drawing
4. Welcome to point out the error, and pull better code

> the code is writed and debug in CLion IDE，and not test in terminal（I will check it after finish more code）

## ch1. Fundamentals

|                             REF                              |                          PROGRAM                          |      DESCRIPTION / JAVADOC       |                             REF                              |                        PROGRAM                        |      DESCRIPTION / JAVADOC      |
| :----------------------------------------------------------: | :-------------------------------------------------------: | :------------------------------: | :----------------------------------------------------------: | :---------------------------------------------------: | :-----------------------------: |
|   [-](https://algs4.cs.princeton.edu/11model/index.php#-)    |         [BinarySearch.h](ch1/head/BinarySearch.h)         |          binary search           |   [-](https://algs4.cs.princeton.edu/11model/index.php#-)    |       [RandomSeq.cpp](ch1/2_RandomSeq/main.cpp)       | random numbers in a given range |
|   [-](https://algs4.cs.princeton.edu/11model/index.php#-)    |           [Average.cpp](ch1/3_Average/main.cpp)           | average of a sequence of numbers |   [-](https://algs4.cs.princeton.edu/11model/index.php#-)    |             [Cat.cpp](ch1/4_Cat/main.cpp)             |        concatenate files        |
|   [-](https://algs4.cs.princeton.edu/11model/index.php#-)    |                [Knuth.h](ch1/head/Knuth.h)                |          Knuth shuffle           |    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |            [Counter.h](ch1/head/Counter.h)            |             counter             |
|    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |      [StaticSETofInts.h](ch1/head/StaticSETofInts.h)      |         set of integers          |    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |       [Whitelist.cpp](ch1/8_Whitelist/main.cpp)       |        whitelist client         |
|    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |               [Vector.h](ch1/head/Vector.h)               |         Euclidean vector         |    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |               [Date.h](ch1/head/Date.h)               |              date               |
|    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |          [Transaction.h](ch1/head/Transaction.h)          |           transaction            |    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |            [Point2D.h](ch1/head/Point2D.h)            |              point              |
|    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |               [RectHV.h](ch1/head/RectHV.h)               |      axis-aligned rectangle      |    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |         [Interval1D.h](ch1/head/Interval1D.h)         |           1d interval           |
|    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |           [Interval2D.h](ch1/head/Interval2D.h)           |           2d interval            |    [-](https://algs4.cs.princeton.edu/12oop/index.php#-)     |        [Accumulator.h](ch1/head/Accumulator.h)        |   running average and stddev    |
| [1.1](https://algs4.cs.princeton.edu/13stacks/index.php#1.1) |   [ResizingArrayStack.h](ch1/head/ResizingArrayStack.h)   |   LIFO stack (resizing array)    | [1.2](https://algs4.cs.princeton.edu/13stacks/index.php#1.2) |        [LinkedStack.h](ch1/head/LinkedStack.h)        |    LIFO stack (linked list)     |
|   [-](https://algs4.cs.princeton.edu/13stacks/index.php#-)   |                [Stack.h](ch1/head/Stack.h)                |            LIFO stack            |   [-](https://algs4.cs.princeton.edu/13stacks/index.php#-)   | [ResizingArrayQueue.h](ch1/head/ResizingArrayQueue.h) |   FIFO queue (resizing array)   |
| [1.3](https://algs4.cs.princeton.edu/13stacks/index.php#1.3) |          [LinkedQueue.h](ch1/head/LinkedQueue.h)          |     FIFO queue (linked list)     |   [-](https://algs4.cs.princeton.edu/13stacks/index.php#-)   |              [Queue.h](ch1/head/Queue.h)              |           FIFO queue            |
|   [-](https://algs4.cs.princeton.edu/13stacks/index.php#-)   |     [ResizingArrayBag.h](ch1/head/ResizingArrayBag.h)     |    multiset (resizing array)     | [1.4](https://algs4.cs.princeton.edu/13stacks/index.php#1.4) |          [LinkedBag.h](ch1/head/LinkedBag.h)          |     multiset (linked list)      |
|   [-](https://algs4.cs.princeton.edu/13stacks/index.php#-)   |                  [Bag.h](ch1/head/Bag.h)                  |             multiset             |  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |          [Stopwatch.h](ch1/head/Stopwatch.h)          |        timer (wall time)        |
|  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |                    [StopwatchCPU.h]()                     |         timer (CPU time)         |  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |   [LinearRegression.h](ch1/head/LinearRegression.h)   |    simple linear regression     |
|  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |             [ThreeSum.h](ch1/head/ThreeSum.h)             |      brute-force three sum       |  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |       [ThreeSumFast.h](ch1/head/ThreeSumFast.h)       |        faster three sum         |
|  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |         [DoublingTest.h](ch1/head/DoublingTest.h)         |          doubling test           |  [-](https://algs4.cs.princeton.edu/14analysis/index.php#-)  |  [DoublingRatio.cpp](ch1/32_DoublingRatio/main.cpp)   |         doubling ratio          |
|     [-](https://algs4.cs.princeton.edu/15uf/index.php#-)     |          [QuickFindUF.h](ch1/head/QuickFindUF.h)          |            quick find            |     [-](https://algs4.cs.princeton.edu/15uf/index.php#-)     |       [QuickUnionUF.h](ch1/head/QuickUnionUF.h)       |           quick union           |
|   [1.5](https://algs4.cs.princeton.edu/15uf/index.php#1.5)   | [WeightedQuickUnionUF.h](ch1/head/WeightedQuickUnionUF.h) |       weighted quick union       |     [-](https://algs4.cs.princeton.edu/15uf/index.php#-)     |                 [UF.h](ch1/head/UF.h)                 | union-by-rank with path halving |

## ch2. Sorting

|                             REF                              |                           PROGRAM                            |       DESCRIPTION / JAVADOC       |                             REF                              |                           PROGRAM                            |     DESCRIPTION / JAVADOC     |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :-------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :---------------------------: |
| [2.1](https://algs4.cs.princeton.edu/21elementary/index.php#2.1) |             [Insertion.h](ch2/head/Insertion.h)              |          insertion sort           | [-](https://algs4.cs.princeton.edu/21elementary/index.php#-) |            [InsertionX.h](ch2/head/InsertionX.h)             |  insertion sort (optimized)   |
| [-](https://algs4.cs.princeton.edu/21elementary/index.php#-) |          [BinaryInsertion.h](ch2/head/InsertionX.h)          |       binary insertion sort       | [2.2](https://algs4.cs.princeton.edu/21elementary/index.php#2.2) |             [Selection.h](ch2/head/InsertionX.h)             |        selection sort         |
| [2.3](https://algs4.cs.princeton.edu/21elementary/index.php#2.3) | [Shell.java](https://algs4.cs.princeton.edu/21elementary/Shell.java.html) |             shellsort             | [2.4](https://algs4.cs.princeton.edu/22mergesort/index.php#2.4) | [Merge.java](https://algs4.cs.princeton.edu/22mergesort/Merge.java.html) |      top-down mergesort       |
| [-](https://algs4.cs.princeton.edu/22mergesort/index.php#-)  |               [MergeBU.h](ch2/head/MergeBU.h)                |        bottom-up mergesort        | [-](https://algs4.cs.princeton.edu/22mergesort/index.php#-)  |                [MergeX.h](ch2/head/MergeX.h)                 |      optimized mergesort      |
| [-](https://algs4.cs.princeton.edu/22mergesort/index.php#-)  | [Inversions.java](https://algs4.cs.princeton.edu/22mergesort/Inversions.java.html) |       number of inversions        | [2.5](https://algs4.cs.princeton.edu/23quicksort/index.php#2.5) |                 [Quick.h](ch2/head/Quick.h)                  |           quicksort           |
| [-](https://algs4.cs.princeton.edu/23quicksort/index.php#-)  |             [Quick3way.h](ch2/head/Quick3way.h)              | quicksort with 3-way partitioning | [-](https://algs4.cs.princeton.edu/23quicksort/index.php#-)  |                [QuickX.h](ch2/head/QuickX.h)                 |   optimized 2-way quicksort   |
| [-](https://algs4.cs.princeton.edu/23quicksort/index.php#-)  |   [QuickBentleyMcIlroy.h](ch2/head/QuickBentleyMcIlroy.h)    |     optimized 3-way quicksort     |     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |               [TopM.cpp](ch2/14_TopM/main.cpp)               |     priority queue client     |
|   [2.6](https://algs4.cs.princeton.edu/24pq/index.php#2.6)   |                 [MaxPQ.h](ch2/head/MaxPQ.h)                  |      max heap priority queue      |     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |                 [MinPQ.h](ch2/head/MinPQ.h)                  |    min heap priority queue    |
|     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |            [IndexMinPQ.h](ch2/head/IndexMinPQ.h)             |   index min heap priority queue   |     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |            [IndexMaxPQ.h](ch2/head/IndexMaxPQ.h)             | index max heap priority queue |
|     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |              [Multiway.h](ch2/head/Multiway.h)               |          multiway merge           |   [2.7](https://algs4.cs.princeton.edu/24pq/index.php#2.7)   |                  [Heap.h](ch2/head/Heap.h)                   |           heapsort            |

## ch3. Searching

|                             REF                              |                         PROGRAM                         |   DESCRIPTION / JAVADOC   |                             REF                              |                           PROGRAM                            |    DESCRIPTION / JAVADOC     |
| :----------------------------------------------------------: | :-----------------------------------------------------: | :-----------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :--------------------------: |
| [-](https://algs4.cs.princeton.edu/31elementary/index.php#-) | [FrequencyCounter.cpp](ch3/1_FrequencyCounter/main.cpp) |     frequency counter     | [3.1](https://algs4.cs.princeton.edu/31elementary/index.php#3.1) |    [SequentialSearchST.h](ch3/head/SequentialSearchST.h)     |      sequential search       |
| [3.2](https://algs4.cs.princeton.edu/31elementary/index.php#3.2) |      [BinarySearchST.h](ch3/head/BinarySearchST.h)      |       binary search       |  [3.3](https://algs4.cs.princeton.edu/32bst/index.php#3.3)   |                   [BST.h](ch3/head/BST.h)                    |      binary search tree      |
| [3.4](https://algs4.cs.princeton.edu/33balanced/index.php#3.4) |         [RedBlackBST.h](ch3/head/RedBlackBST.h)         |      red-black tree       |  [3.5](https://algs4.cs.princeton.edu/34hash/index.php#3.5)  | [SeparateChainingHashST.h](ch3/head/SeparateChainingHashST.h) | separate chaining hash table |
|  [3.6](https://algs4.cs.princeton.edu/34hash/index.php#3.6)  | [LinearProbingHashST.h](ch3/head/LinearProbingHashST.h) | linear probing hash table | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |                    [ST.h](ch3/head/ST.h)                     |     ordered symbol table     |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |                 [SET.h](ch3/head/SET.h)                 |        ordered set        | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |              [DeDup.cpp](ch3/10_DeDup/main.cpp)              |      remove duplicates       |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |     [WhiteFilter.cpp](ch3/11_WhiteFilter/main.cpp)      |     whitelist filter      | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |            [BlackFilter.cpp](ch3/12_BlackFilter)             |       blacklist filter       |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |       [LookupCSV.cpp](ch3/13_LookupCSV/main.cpp)        |     dictionary lookup     | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |        [LookupIndex.cpp](ch3/14_LookupIndex/main.cpp)        |   index and inverted index   |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |       [FileIndex.cpp](ch3/15_FileIndex/main.cpp)        |       file indexing       | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |          [SparseVector.h](ch3/head/SparseVector.h)           |        sparse vector         |

