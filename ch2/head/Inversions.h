#ifndef CH2_INVERSIONS_H
#define CH2_INVERSIONS_H

#include <vector>

using std::vector;

/**
 *  The {@code Inversions} class provides static methods to count the
 *  number of <em>inversions</em> in either an array of integers or comparables.
 *  An inversion in an array {@code a[]} is a pair of indicies {@code i} and
 *  {@code j} such that {@code i < j} and {@code a[i] > a[j]}.
 *  <p>
 *  This implementation uses a generalization of mergesort. The <em>count</em>
 *  operation takes time proportional to <em>n</em> log <em>n</em>,
 *  where <em>n</em> is the number of keys in the array.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/22mergesort">Section 2.2</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Inversions {
public:
    // do not instantiate
    Inversions() = delete;

    /**
     * Returns the number of inversions in the integer array.
     * The argument array is not modified.
     * @param  a the array
     * @return the number of inversions in the array. An inversion is a pair of
     *         indicies {@code i} and {@code j} such that {@code i < j}
     *         and {@code a[i] > a[j]}.
     */
    static long count(vector<int> &a) {
        vector<int> b(a);
        vector<int> aux(a.size(), 0);
        long inversions = count(a, b, aux, 0, a.size() - 1);
        return inversions;
    }

    /**
     * Returns the number of inversions in the comparable array.
     * The argument array is not modified.
     * @param  a the array
     * @param <Key> the inferred type of the elements in the array
     * @return the number of inversions in the array. An inversion is a pair of
     *         indicies {@code i} and {@code j} such that {@code i < j}
     *         and {@code a[i].compareTo(a[j]) > 0}.
     */
    template<typename T>
    static long count_T(vector<T> &a) {
        vector<T> b(a);
        vector<T> aux(a);
        long inversions = count_T(a, b, aux, 0, a.size() - 1);
        return inversions;
    }

private:
    // merge and count
    template<typename T>
    static long merge(vector<T> &a, vector<T> &aux, int lo, int mid, int hi) {
        long inversions = 0;

        // copy to aux[]
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }

        // merge back to a[]
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) a[k] = aux[j++];
            else if (j > hi) a[k] = aux[i++];
            else if (aux[j] < aux[i]) {
                a[k] = aux[j++];
                inversions += (mid - i + 1);
            } else a[k] = aux[i++];
        }
        return inversions;
    }

    // return the number of inversions in the subarray b[lo..hi]
    // side effect b[lo..hi] is rearranged in ascending order
    static long count(vector<int> &a, vector<int> &b, vector<int> &aux, int lo, int hi) {
        long inversions = 0;
        if (hi <= lo) return 0;
        int mid = lo + (hi - lo) / 2;
        inversions += count(a, b, aux, lo, mid);
        inversions += count(a, b, aux, mid + 1, hi);
        inversions += merge(b, aux, lo, mid, hi);
        return inversions;
    }

    // merge and count (Comparable version)
    template<typename T>
    static long merge_T(vector<T> &a, vector<T> &aux, int lo, int mid, int hi) {
        long inversions = 0;

        // copy to aux[]
        for (int k = lo; k <= hi; k++) {
            aux[k] = a[k];
        }

        // merge back to a[]
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) a[k] = aux[j++];
            else if (j > hi) a[k] = aux[i++];
            else if (aux[j] < aux[i]) {
                a[k] = aux[j++];
                inversions += (mid - i + 1);
            } else a[k] = aux[i++];
        }
        return inversions;
    }

    // return the number of inversions in the subarray b[lo..hi]
    // side effect b[lo..hi] is rearranged in ascending order
    template<typename T>
    static long count_T(vector<T> &a, vector<T> &b, vector<T> &aux, int lo, int hi) {
        long inversions = 0;
        if (hi <= lo) return 0;
        int mid = lo + (hi - lo) / 2;
        inversions += count_T(a, b, aux, lo, mid);
        inversions += count_T(a, b, aux, mid + 1, hi);
        inversions += merge_T(b, aux, lo, mid, hi);
        return inversions;
    }

};

#endif //CH2_INVERSIONS_H
