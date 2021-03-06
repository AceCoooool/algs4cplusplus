# Algorithms
Algorithms, 4th edition textbook code (using c++)

> official java code: [Algorithms, 4th Edition](https://algs4.cs.princeton.edu/home/)

**Note：**

1. based on STL Library
2. using C++17
3. **Not support** drawing
4. Welcome to point out the error, and pull better code

### TODO

- [ ] check ch1
- [ ] check ch2
- [ ] check ch3
- [ ] check ch4
- [ ] check ch5
- [ ] add ch6

## Tutorial: run demo code

### terminal

```shell
# for example 
cd ch1
g++ 1_BinarySearch/main.cpp -o binary
./binary
```

### IDE(clion)

You sholud Edit the Configurations：（Due to the relative file path）

```shell
Working directory: youroot/algs4cplusplus/ch1
```

## ch1. Fundamentals

|                             REF                              |                          PROGRAM                          |       DESCRIPTION / C++DOC       |                             REF                              |                        PROGRAM                        |      DESCRIPTION / C++DOC       |
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

|                             REF                              |                           PROGRAM                            |       DESCRIPTION / C++DOC        |                             REF                              |                           PROGRAM                            |      DESCRIPTION /C++DOC      |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :-------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :---------------------------: |
| [2.1](https://algs4.cs.princeton.edu/21elementary/index.php#2.1) |             [Insertion.h](ch2/head/Insertion.h)              |          insertion sort           | [-](https://algs4.cs.princeton.edu/21elementary/index.php#-) |            [InsertionX.h](ch2/head/InsertionX.h)             |  insertion sort (optimized)   |
| [-](https://algs4.cs.princeton.edu/21elementary/index.php#-) |          [BinaryInsertion.h](ch2/head/InsertionX.h)          |       binary insertion sort       | [2.2](https://algs4.cs.princeton.edu/21elementary/index.php#2.2) |             [Selection.h](ch2/head/InsertionX.h)             |        selection sort         |
| [2.3](https://algs4.cs.princeton.edu/21elementary/index.php#2.3) | [Shell.java](https://algs4.cs.princeton.edu/21elementary/Shell.java.html) |             shellsort             | [2.4](https://algs4.cs.princeton.edu/22mergesort/index.php#2.4) | [Merge.java](https://algs4.cs.princeton.edu/22mergesort/Merge.java.html) |      top-down mergesort       |
| [-](https://algs4.cs.princeton.edu/22mergesort/index.php#-)  |               [MergeBU.h](ch2/head/MergeBU.h)                |        bottom-up mergesort        | [-](https://algs4.cs.princeton.edu/22mergesort/index.php#-)  |                [MergeX.h](ch2/head/MergeX.h)                 |      optimized mergesort      |
| [-](https://algs4.cs.princeton.edu/22mergesort/index.php#-)  |            [Inversions.h](ch2/head/Inversions.h)             |       number of inversions        | [2.5](https://algs4.cs.princeton.edu/23quicksort/index.php#2.5) |                 [Quick.h](ch2/head/Quick.h)                  |           quicksort           |
| [-](https://algs4.cs.princeton.edu/23quicksort/index.php#-)  |             [Quick3way.h](ch2/head/Quick3way.h)              | quicksort with 3-way partitioning | [-](https://algs4.cs.princeton.edu/23quicksort/index.php#-)  |                [QuickX.h](ch2/head/QuickX.h)                 |   optimized 2-way quicksort   |
| [-](https://algs4.cs.princeton.edu/23quicksort/index.php#-)  |   [QuickBentleyMcIlroy.h](ch2/head/QuickBentleyMcIlroy.h)    |     optimized 3-way quicksort     |     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |               [TopM.cpp](ch2/14_TopM/main.cpp)               |     priority queue client     |
|   [2.6](https://algs4.cs.princeton.edu/24pq/index.php#2.6)   |                 [MaxPQ.h](ch2/head/MaxPQ.h)                  |      max heap priority queue      |     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |                 [MinPQ.h](ch2/head/MinPQ.h)                  |    min heap priority queue    |
|     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |            [IndexMinPQ.h](ch2/head/IndexMinPQ.h)             |   index min heap priority queue   |     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |            [IndexMaxPQ.h](ch2/head/IndexMaxPQ.h)             | index max heap priority queue |
|     [-](https://algs4.cs.princeton.edu/24pq/index.php#-)     |              [Multiway.h](ch2/head/Multiway.h)               |          multiway merge           |   [2.7](https://algs4.cs.princeton.edu/24pq/index.php#2.7)   |                  [Heap.h](ch2/head/Heap.h)                   |           heapsort            |

## ch3. Searching

|                             REF                              |                         PROGRAM                         |   DESCRIPTION / C++DOC    |                             REF                              |                           PROGRAM                            |     DESCRIPTION /C++DOC      |
| :----------------------------------------------------------: | :-----------------------------------------------------: | :-----------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :--------------------------: |
| [-](https://algs4.cs.princeton.edu/31elementary/index.php#-) | [FrequencyCounter.cpp](ch3/1_FrequencyCounter/main.cpp) |     frequency counter     | [3.1](https://algs4.cs.princeton.edu/31elementary/index.php#3.1) |    [SequentialSearchST.h](ch3/head/SequentialSearchST.h)     |      sequential search       |
| [3.2](https://algs4.cs.princeton.edu/31elementary/index.php#3.2) |      [BinarySearchST.h](ch3/head/BinarySearchST.h)      |       binary search       |  [3.3](https://algs4.cs.princeton.edu/32bst/index.php#3.3)   |                   [BST.h](ch3/head/BST.h)                    |      binary search tree      |
| [3.4](https://algs4.cs.princeton.edu/33balanced/index.php#3.4) |         [RedBlackBST.h](ch3/head/RedBlackBST.h)         |      red-black tree       |  [3.5](https://algs4.cs.princeton.edu/34hash/index.php#3.5)  | [SeparateChainingHashST.h](ch3/head/SeparateChainingHashST.h) | separate chaining hash table |
|  [3.6](https://algs4.cs.princeton.edu/34hash/index.php#3.6)  | [LinearProbingHashST.h](ch3/head/LinearProbingHashST.h) | linear probing hash table | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |                    [ST.h](ch3/head/ST.h)                     |     ordered symbol table     |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |                 [SET.h](ch3/head/SET.h)                 |        ordered set        | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |              [DeDup.cpp](ch3/10_DeDup/main.cpp)              |      remove duplicates       |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |     [WhiteFilter.cpp](ch3/11_WhiteFilter/main.cpp)      |     whitelist filter      | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |            [BlackFilter.cpp](ch3/12_BlackFilter)             |       blacklist filter       |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |       [LookupCSV.cpp](ch3/13_LookupCSV/main.cpp)        |     dictionary lookup     | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |        [LookupIndex.cpp](ch3/14_LookupIndex/main.cpp)        |   index and inverted index   |
| [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |       [FileIndex.cpp](ch3/15_FileIndex/main.cpp)        |       file indexing       | [-](https://algs4.cs.princeton.edu/35applications/index.php#-) |          [SparseVector.h](ch3/head/SparseVector.h)           |        sparse vector         |

## ch4. Graphs

|                             REF                              |                           PROGRAM                            |       DESCRIPTION / C++DOC       |                             REF                              |                           PROGRAM                            |         DESCRIPTION / C++DOC         |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------: |
|   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |                 [Graph.h](ch4/head/Graph.h)                  |         undirected graph         |   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    | [GraphGenerator.java](https://algs4.cs.princeton.edu/41graph/GraphGenerator.java.html) |        generate random graphs        |
|   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |      [DepthFirstSearch.h](ch4/head/DepthFirstSearch.h)       |  depth-first search in a graph   |   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |       [NonrecursiveDFS.h](ch4/head/NonrecursiveDFS.h)        |    DFS in a graph (nonrecursive)     |
| [4.1](https://algs4.cs.princeton.edu/41graph/index.php#4.1)  |       [DepthFirstPaths.h](ch4/head/DepthFirstPaths.h)        |      paths in a graph (DFS)      | [4.2](https://algs4.cs.princeton.edu/41graph/index.php#4.2)  |     [BreadthFirstPaths.h](ch4/head/BreadthFirstPaths.h)      |        paths in a graph (BFS)        |
| [4.3](https://algs4.cs.princeton.edu/41graph/index.php#4.3)  |                    [CC.h](ch4/head/CC.h)                     | connected components of a graph  |   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |             [Bipartite.h](ch4/head/Bipartite.h)              |     bipartite or odd cycle (DFS)     |
|   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |            [BipartiteX.h](ch4/head/BipartiteX.h)             |   bipartite or odd cycle (BFS)   |   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |                 [Cycle.h](ch4/head/Cycle.h)                  |           cycle in a graph           |
|   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |         [EulerianCycle.h](ch4/head/EulerianCycle.h)          |    Eulerian cycle in a graph     |   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |          [EulerianPath.h](ch4/head/EulerianPath.h)           |       Eulerian path in a graph       |
|   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    |           [SymbolGraph.h](ch4/head/SymbolGraph.h)            |           symbol graph           |   [-](https://algs4.cs.princeton.edu/41graph/index.php#-)    | [DegreesOfSeparation.cpp](ch4/14_DegreesOfSeparation/main.cpp) |        degrees of separation         |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |               [Digraph.h](ch4/head/Digraph.h)                |          directed graph          |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |      [DigraphGenerator.h](ch4/head/DigraphGenerator.h)       |       generate random digraphs       |
| [4.4](https://algs4.cs.princeton.edu/42digraph/index.php#4.4) |           [DirectedDFS.h](ch4/head/DirectedDFS.h)            | depth-first search in a digraph  |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   | [NonrecursiveDirectedDFS.h](ch4/head/NonrecursiveDirectedDFS.h) |   DFS in a digraph (nonrecursive)    |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   | [DepthFirstDirectedPaths.h](ch4/head/DepthFirstDirectedPaths.h) |     paths in a digraph (DFS)     |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   | [BreadthFirstDirectedPaths.h](ch4/head/BreadthFirstDirectedPaths.h) |       paths in a digraph (BFS)       |
|     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |         [DirectedCycle.h](ch4/head/DirectedCycle.h)          |        cycle in a digraph        |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |        [DirectedCycleX.h](ch4/head/DirectedCycleX.h)         |  cycle in a digraph (nonrecursive)   |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   | [DirectedEulerianCycle.h](ch4/head/DirectedEulerianCycle.h)  |   Eulerian cycle in a digraph    |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |  [DirectedEulerianPath.h](ch4/head/DirectedEulerianPath.h)   |      Eulerian path in a digraph      |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |       [DepthFirstOrder.h](ch4/head/DepthFirstOrder.h)        |  depth-first order in a digraph  | [4.5](https://algs4.cs.princeton.edu/42digraph/index.php#4.5) |           [Topological.h](ch4/head/Topological.h)            |      topological order in a DAG      |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |          [TopologicalX.h](ch4/head/TopologicalX.h)           | topological order (nonrecursive) |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |     [TransitiveClosure.h](ch4/head/TransitiveClosure.h)      |          transitive closure          |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |         [SymbolDigraph.h](ch4/head/SymbolDigraph.h)          |          symbol digraph          | [4.6](https://algs4.cs.princeton.edu/42digraph/index.php#4.6) |     [KosarajuSharirSCC.h](ch4/head/KosarajuSharirSCC.h)      | strong components (Kosaraju–Sharir)  |
|  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |             [TarjanSCC.h](ch4/head/TarjanSCC.h)              |    strong components (Tarjan)    |  [-](https://algs4.cs.princeton.edu/42digraph/index.php#-)   |              [GabowSCC.h](ch4/head/GabowSCC.h)               |      strong components (Gabow)       |
|    [-](https://algs4.cs.princeton.edu/43mst/index.php#-)     |     [EdgeWeightedGraph.h](ch4/head/EdgeWeightedGraph.h)      |       edge-weighted graph        |    [-](https://algs4.cs.princeton.edu/43mst/index.php#-)     |                  [Edge.h](ch4/head/Edge.h)                   |            weighted edge             |
|    [-](https://algs4.cs.princeton.edu/43mst/index.php#-)     |           [LazyPrimMST.h](ch4/head/LazyPrimMST.h)            |         MST (lazy Prim)          |  [4.7](https://algs4.cs.princeton.edu/43mst/index.php#4.7)   |               [PrimMST.h](ch4/head/PrimMST.h)                |              MST (Prim)              |
|  [4.8](https://algs4.cs.princeton.edu/43mst/index.php#4.8)   |            [KruskalMST.h](ch4/head/KruskalMST.h)             |          MST (Kruskal)           |    [-](https://algs4.cs.princeton.edu/43mst/index.php#-)     |            [BoruvkaMST.h](ch4/head/BoruvkaMST.h)             |            MST (Boruvka)             |
|     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |   [EdgeWeightedDigraph.h](ch4/head/EdgeWeightedDigraph.h)    |      edge-weighted digraph       |     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |          [DirectedEdge.h](ch4/head/DirectedEdge.h)           |       weighted, directed edge        |
|   [4.9](https://algs4.cs.princeton.edu/44sp/index.php#4.9)   |            [DijkstraSP.h](ch4/head/DijkstraSP.h)             |    shortest paths (Dijkstra)     |     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |  [DijkstraUndirectedSP.h](ch4/head/DijkstraUndirectedSP.h)   | undirected shortest paths (Dijkstra) |
|     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |    [DijkstraAllPairsSP.h](ch4/head/DijkstraAllPairsSP.h)     |     all-pairs shortest paths     |  [4.10](https://algs4.cs.princeton.edu/44sp/index.php#4.10)  |             [AcyclicSP.h](ch4/head/AcyclicSP.h)              |       shortest paths in a DAG        |
|     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |             [AcyclicLP.h](ch4/head/AcyclicLP.h)              |      longest paths in a DAG      |     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |                [CPM.cpp](ch4/46_CPM/main.cpp)                |         critical path method         |
|  [4.11](https://algs4.cs.princeton.edu/44sp/index.php#4.11)  |         [BellmanFordSP.h](ch4/head/BellmanFordSP.h)          |  shortest paths (Bellman–Ford)   |     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     | [EdgeWeightedDirectedCycle.h](ch4/head/EdgeWeightedDirectedCycle.h) |  cycle in an edge-weighted digraph   |
|     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |          [Arbitrage.cpp](ch4/49_Arbitrage/main.cpp)          |       arbitrage detection        |     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     |         [FloydWarshall.h](ch4/head/FloydWarshall.h)          |   all-pairs shortest paths (dense)   |
|     [-](https://algs4.cs.princeton.edu/44sp/index.php#-)     | [AdjMatrixEdgeWeightedDigraph.h](ch4/head/AdjMatrixEdgeWeightedDigraph.h) |   edge-weighted graph (dense)    |                                                              |                                                              |                                      |

## ch5. Strings

|                             REF                              |                           PROGRAM                            |      DESCRIPTION / C++DOC      |                             REF                              |                           PROGRAM                            |         DESCRIPTION / C++DOC          |
| :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: | :-----------------------------------: |
|  [-](https://algs4.cs.princeton.edu/50strings/index.php#-)   | [Alphabet.java](https://algs4.cs.princeton.edu/50strings/Alphabet.java.html) |            alphabet            |  [-](https://algs4.cs.princeton.edu/50strings/index.php#-)   | [Count.java](https://algs4.cs.princeton.edu/50strings/Count.java.html) |            alphabet client            |
| [5.1](https://algs4.cs.princeton.edu/51radix/index.php#5.1)  |                   [LSD.h](ch5/head/LSD.h)                    |         LSD radix sort         | [5.2](https://algs4.cs.princeton.edu/51radix/index.php#5.2)  |                   [MSD.h](ch5/head/MSD.h)                    |            MSD radix sort             |
|   [-](https://algs4.cs.princeton.edu/51radix/index.php#-)    |            [InplaceMSD.h](ch5/head/InplaceMSD.h)             |    In-place MSD radix sort1    | [5.3](https://algs4.cs.princeton.edu/51radix/index.php#5.3)  |          [Quick3string.h](ch5/head/Quick3string.h)           |        3-way string quicksort         |
|   [-](https://algs4.cs.princeton.edu/51radix/index.php#-)    |          [AmericanFlag.h](ch5/head/AmericanFlag.h)           |      American flag sort1       |   [-](https://algs4.cs.princeton.edu/51radix/index.php#-)    |         [AmericanFlagX.h](ch5/head/AmericanFlagX.h)          |   non-recursive American flag sort1   |
|  [5.4](https://algs4.cs.princeton.edu/52trie/index.php#5.4)  |                [TrieST.h](ch5/head/TrieST.h)                 |   multiway trie symbol table   |    [-](https://algs4.cs.princeton.edu/52trie/index.php#-)    |               [TrieSET.h](ch5/head/TrieSET.h)                |           multiway trie set           |
|  [5.5](https://algs4.cs.princeton.edu/52trie/index.php#5.5)  |                 [TST.h](ch5/head/TrieSET.h)                  |      ternary search trie       | [5.6](https://algs4.cs.princeton.edu/53substring/index.php#5.6) |                   [KMP.h](ch5/head/KMP.h)                    | substring search (Knuth–Morris–Pratt) |
| [5.7](https://algs4.cs.princeton.edu/53substring/index.php#5.7) |            [BoyerMoore.h](ch5/head/BoyerMoore.h)             | substring search (Boyer–Moore) | [5.8](https://algs4.cs.princeton.edu/53substring/index.php#5.8) |             [RabinKarp.h](ch5/head/RabinKarp.h)              |     substring search (Rabin–Karp)     |
| [5.9](https://algs4.cs.princeton.edu/54regexp/index.php#5.9) |                   [NFA.h](ch5/head/NFA.h)                    |  NFA for regular expressions   |   [-](https://algs4.cs.princeton.edu/54regexp/index.php#-)   |               [GREP.cpp](ch5/16_GREP/main.cpp)               |                 grep                  |
| [-](https://algs4.cs.princeton.edu/55compression/index.php#-) |         [BinaryDump.cpp](ch5/17_BinaryDump/main.cpp)         |          binary dump           |                                                              |                                                              |                                       |

