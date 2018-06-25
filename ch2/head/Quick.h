#ifndef CH2_QUICK_H
#define CH2_QUICK_H

#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <stdexcept>

using std::vector;
using std::swap;
using std::cout;
using std::endl;
using std::to_string;
using std::random_device;
using std::mt19937;
using std::shuffle;
using std::runtime_error;

random_device rd;
mt19937 g(rd());

/**
 *  The {@code Quick} class provides static methods for sorting an
 *  array and selecting the ith smallest element in an array using quicksort.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/23quick">Section 2.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Quick {
public:
    // This class should not be instantiated.
    Quick() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        shuffle(a.begin(), a.end(), g);
        sort(a, 0, a.size() - 1);
    }

    /**
     * Rearranges the array so that {@code a[k]} contains the kth smallest key;
     * {@code a[0]} through {@code a[k-1]} are less than (or equal to) {@code a[k]}; and
     * {@code a[k+1]} through {@code a[n-1]} are greater than (or equal to) {@code a[k]}.
     *
     * @param  a the array
     * @param  k the rank of the key
     * @return the key of rank {@code k}
     * @throws IllegalArgumentException unless {@code 0 <= k < a.length}
     */
    template<typename T>
    static T select(vector<T> &a, int k) {
        if (k < 0 || k >= a.size()) {
            throw runtime_error("index is not between 0 and " + to_string(a.size()) + ": " + to_string(k));
        }
        shuffle(a.begin(), a.end(), g);
        int lo = 0, hi = a.size() - 1;
        while (hi > lo) {
            int i = partition(a, lo, hi);
            if (i > k) hi = i - 1;
            else if (i < k) lo = i + 1;
            else return a[i];
        }
        return a[lo];
    }

    // print array to standard output
    template<typename T>
    static void show(vector<T> &a) {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << endl;
        }
    }


private:
    // quicksort the subarray from a[lo] to a[hi]
    template<typename T>
    static void sort(vector<T> &a, int lo, int hi) {
        if (hi <= lo) return;
        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
    }

    // partition the subarray a[lo..hi] so that a[lo..j-1] <= a[j] <= a[j+1..hi]
    // and return the index j.
    template<typename T>
    static int partition(vector<T> &a, int lo, int hi) {
        int i = lo;
        int j = hi + 1;
        T v = a[lo];
        while (true) {
            // find item on lo to swap
            while (a[++i] < v) {
                if (i == hi) break;
            }

            // find item on hi to swap
            while (v < a[--j]) {
                if (j == lo) break;      // redundant since a[lo] acts as sentinel
            }

            // check if pointers cross
            if (i >= j) break;

            swap(a[i], a[j]);
        }

        // put partitioning item v at a[j]
        swap(a[lo], a[j]);

        // now, a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
        return j;
    }
};

#endif //CH2_QUICK_H
