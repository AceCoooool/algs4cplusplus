#ifndef CH1_THREESUMFAST_H
#define CH1_THREESUMFAST_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using std::vector;
using std::cout;
using std::endl;
using std::sort;
using std::binary_search;
using std::runtime_error;

/**
 *  The {@code ThreeSumFast} class provides static methods for counting
 *  and printing the number of triples in an array of distinct integers that
 *  sum to 0 (ignoring integer overflow).
 *  <p>
 *  This implementation uses sorting and binary search and takes time
 *  proportional to n^2 log n, where n is the number of integers.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/14analysis">Section 1.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class ThreeSumFast {
public:
    ThreeSumFast() = delete;

    // returns true if the sorted array a[] contains any duplicated integers
    static bool containsDuplicates(vector<int> &a) {
        for (int i = 1; i < a.size(); i++)
            if (a[i] == a[i - 1]) return true;
        return false;
    }

    /**
      * Prints to standard output the (i, j, k) with {@code i < j < k}
      * such that {@code a[i] + a[j] + a[k] == 0}.
      *
      * @param a the array of integers
      * @throws IllegalArgumentException if the array contains duplicate integers
      */
    static void printAll(vector<int> &a) {
        int n = a.size();
        sort(a.begin(), a.end());
        if (containsDuplicates(a)) throw runtime_error("array contains duplicate integers");
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool k = binary_search(a.begin() + j, a.end(), -(a[i] + a[j]));
                if (k)
                    cout << a[i] << " " << a[j] << " " << -(a[i] + a[j]) << endl;
            }
        }
    }

    /**
     * Returns the number of triples (i, j, k) with {@code i < j < k}
     * such that {@code a[i] + a[j] + a[k] == 0}.
     *
     * @param a the array of integers
     * @return the number of triples (i, j, k) with {@code i < j < k}
     * such that {@code a[i] + a[j] + a[k] == 0}
     */
    static int count(vector<int> &a) {
        int n = a.size();
        sort(a.begin(), a.end());
        if (containsDuplicates(a)) throw runtime_error("array contains duplicate integers");
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                bool k = binary_search(a.begin() + j, a.end(), -(a[i] + a[j]));
                if (k) count++;
            }
        }
        return count;
    }
};

#endif //CH1_THREESUMFAST_H
