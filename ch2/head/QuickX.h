#ifndef CH2_QUICKX_H
#define CH2_QUICKX_H

#include <iostream>
#include <vector>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code QuickX} class provides static methods for sorting an array
 *  using an optimized version of quicksort (using Hoare's 2-way partitioning
 *  algorithm, median-of-3 to choose the partitioning element, and cutoff
 *  to insertion sort).
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/23quick">Section 2.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class QuickX {
public:
    QuickX() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        // StdRandom.shuffle(a);
        sort(a, 0, a.size() - 1);
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

        // cutoff to insertion sort (Insertion.sort() uses half-open intervals)
        int n = hi - lo + 1;
        if (n <= INSERTION_SORT_CUTOFF) {
            insertionSort(a, lo, hi + 1);
            return;
        }

        int j = partition(a, lo, hi);
        sort(a, lo, j - 1);
        sort(a, j + 1, hi);
    }

    // partition the subarray a[lo..hi] so that a[lo..j-1] <= a[j] <= a[j+1..hi]
    // and return the index j.
    template<typename T>
    static int partition(vector<T> &a, int lo, int hi) {
        static auto median3 = [](vector<T> &a, int i, int j, int k) {
            return a[i] < a[j] ? (a[j] < a[k] ? j : (a[i] < a[k] ? k : i)) : (a[k] < a[j] ? j : (a[k] < a[i] ? k : i));
        };
        int n = hi - lo + 1;
        int m = median3(a, lo, lo + n / 2, hi);
        swap(a[m], a[lo]);

        int i = lo;
        int j = hi + 1;
        T v = a[lo];

        // a[lo] is unique largest element
        while (a[++i] < v) {
            if (i == hi) {
                swap(a[lo], a[hi]);
                return hi;
            }
        }

        // a[lo] is unique smallest element
        while (v < a[--j]) {
            if (j == lo + 1) return lo;
        }

        // the main loop
        while (i < j) {
            swap(a[i], a[j]);
            while (a[++i] < v);
            while (v < a[--j]);
        }

        // put partitioning item v at a[j]
        swap(a[lo], a[j]);

        // now, a[lo .. j-1] <= a[j] <= a[j+1 .. hi]
        return j;
    }

    // sort from a[lo] to a[hi] using insertion sort
    template<typename T>
    static void insertionSort(vector<T> &a, int lo, int hi) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && a[j] < a[j - 1]; j--)
                swap(a[j], a[j - 1]);
    }

private:
    // cutoff to insertion sort, must be >= 1
    static int INSERTION_SORT_CUTOFF;
};

int QuickX::INSERTION_SORT_CUTOFF;

#endif //CH2_QUICKX_H
