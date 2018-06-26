#ifndef CH2_HEAP_H
#define CH2_HEAP_H

#include <vector>
#include <iostream>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code Heap} class provides a static methods for heapsorting
 *  an array.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Heap {
public:
    // This class should not be instantiated.
    Heap() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param pq the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &pq) {
        int n = pq.size();
        for (int k = n / 2; k >= 1; k--)
            sink(pq, k, n);
        while (n > 1) {
            exch(pq, 1, n--);
            sink(pq, 1, n);
        }
    }

    // print array to standard output
    template<typename T>
    static void show(vector<T> &a) {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }

private:
    /***************************************************************************
    * Helper functions to restore the heap invariant.
    ***************************************************************************/
    template<typename T>
    static void sink(vector<T> &pq, int k, int n) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && less(pq, j, j + 1)) j++;
            if (!less(pq, k, j)) break;
            exch(pq, k, j);
            k = j;
        }
    }

    /***************************************************************************
    * Helper functions for comparisons and swaps.
    * Indices are "off-by-one" to support 1-based indexing.
    ***************************************************************************/
    template<typename T>
    static void exch(vector<T> &pq, int i, int j) {
        swap(pq[i - 1], pq[j - 1]);
    }

    template<typename T>
    static bool less(vector<T> &pq, int i, int j) {
        return pq[i - 1] < pq[j - 1];
    }
};


#endif //CH2_HEAP_H
