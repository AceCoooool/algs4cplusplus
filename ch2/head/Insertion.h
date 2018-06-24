#ifndef CH2_INSERTION_H
#define CH2_INSERTION_H

#include <vector>
#include <iostream>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code Insertion} class provides static methods for sorting an
 *  array using insertion sort.
 *  <p>
 *  This implementation makes ~ 1/2 n^2 compares and exchanges in
 *  the worst case, so it is not suitable for sorting large arbitrary arrays.
 *  More precisely, the number of exchanges is exactly equal to the number
 *  of inversions. So, for example, it sorts a partially-sorted array
 *  in linear time.
 *  <p>
 *  The sorting algorithm is stable and uses O(1) extra memory.
 *  <p>
 *  See <a href="https://algs4.cs.princeton.edu/21elementary/InsertionPedantic.java.html">InsertionPedantic.java</a>
 *  for a version that eliminates the compiler warning.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Insertion {
public:
    // This class should not be instantiated.
    Insertion() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        int n = a.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i; j > 0 && a[j] < a[j - 1]; --j) {
                swap(a[j], a[j - 1]);
            }
        }
    }

    /**
     * Rearranges the subarray a[lo..hi) in ascending order, using the natural order.
     * @param a the array to be sorted
     * @param lo left endpoint (inclusive)
     * @param hi right endpoint (exclusive)
     */
    template<typename T>
    static void sort(vector<T> &a, int lo, int hi) {
        for (int i = lo; i < hi; i++) {
            for (int j = i; j > lo && a[j] < a[j - 1]; j--) {
                swap(a[j], a[j - 1]);
            }
        }
    }

    /**
     * Rearranges the array in ascending order, using a comparator.
     * @param a the array
     * @param comparator the comparator specifying the order
     */
    template<typename T, typename Comp>
    static void sort(vector<T> &a, Comp cmp) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j > 0 && cmp(a[j], a[j - 1]); j--) {
                swap(a[j], a[j - 1]);
            }
        }
    }

    /**
     * Rearranges the subarray a[lo..hi) in ascending order, using a comparator.
     * @param a the array
     * @param lo left endpoint (inclusive)
     * @param hi right endpoint (exclusive)
     * @param comparator the comparator specifying the order
     */
    template<typename T, typename Comp>
    static void sort(vector<T> &a, int lo, int hi, Comp cmp) {
        for (int i = lo; i < hi; i++) {
            for (int j = i; j > lo && cmp(a[j], a[j - 1]); j--) {
                swap(a[j], a[j - 1]);
            }
        }
    }

    // return a permutation that gives the elements in a[] in ascending order
    // do not change the original array a[]
    /**
     * Returns a permutation that gives the elements in the array in ascending order.
     * @param a the array
     * @return a permutation {@code p[]} such that {@code a[p[0]]}, {@code a[p[1]]},
     *    ..., {@code a[p[n-1]]} are in ascending order
     */
    template<typename T>
    static vector<int> indexSort(vector<T> &a) {
        int n = a.size();
        vector<int> index(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        for (int i = 0; i < n; i++)
            for (int j = i; j > 0 && a[index[j]] < a[index[j - 1]]; j--)
                swap(index[j], index[j - 1]);

        return index;
    }

    // print array to standard output
    template<typename T>
    static void show(vector<T> &a) {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << endl;
        }
    }

};

#endif //CH2_INSERTION_H
