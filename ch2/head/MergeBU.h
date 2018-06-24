#ifndef CH2_MERGEBU_H
#define CH2_MERGEBU_H

#include <vector>
#include <iostream>
#include <cmath>

using std::vector;
using std::cout;
using std::endl;
using std::min;

/**
 *  The {@code MergeBU} class provides static methods for sorting an
 *  array using bottom-up mergesort.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class MergeBU {
public:
    // This class should not be instantiated.
    MergeBU() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        int n = a.size();
        vector<T> aux(n);
        for (int len = 1; len < n; len *= 2) {
            for (int lo = 0; lo < n - len; lo += (len + len)) {
                int mid = lo + len - 1;
                int hi = min(lo + len + len - 1, n - 1);
                merge(a, aux, lo, mid, hi);
            }
        }
    }

    // print array to standard output
    template<typename T>
    static void show(vector<T> &a) {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << endl;
        }
    }

private:
    // stably merge a[lo..mid] with a[mid+1..hi] using aux[lo..hi]
    template<typename T>
    static void merge(vector<T> &a, vector<T> &aux, int lo, int mid, int hi) {
        // copy to aux[]
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }

        // merge back to a[]
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) a[k] = aux[j++];  // this copying is unneccessary
            else if (j > hi) a[k] = aux[i++];
            else if (aux[j] < aux[i]) a[k] = aux[j++];
            else a[k] = aux[i++];
        }
    }

};

#endif //CH2_MERGEBU_H
