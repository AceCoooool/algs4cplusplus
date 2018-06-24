#ifndef CH2_MERGEX_H
#define CH2_MERGEX_H

#include <vector>
#include <iostream>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code MergeX} class provides static methods for sorting an
 *  array using an optimized version of mergesort.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/22mergesort">Section 2.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class MergeX {
public:
    // This class should not be instantiated.
    MergeX() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        vector<T> aux(a);
        sort(aux, a, 0, a.size() - 1);
    }

    /*******************************************************************
     *  Version that takes Comparator as argument.
     *******************************************************************/
    /**
     * Rearranges the array in ascending order, using the provided order.
     *
     * @param a the array to be sorted
     * @param comparator the comparator that defines the total order
     */
    template<typename T, typename Comp>
    static void sort(vector<T> &a, Comp comp) {
        vector<T> aux(a);
        sort(aux, a, 0, a.size() - 1, comp);
    }

    // print array to standard output
    template<typename T>
    static void show(vector<T> &a) {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << endl;
        }
    }

private:
    template<typename T>
    static void merge(vector<T> &src, vector<T> &dst, int lo, int mid, int hi) {
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) dst[k] = src[j++];
            else if (j > hi) dst[k] = src[i++];
            else if (src[j] < src[i]) dst[k] = src[j++];   // to ensure stability
            else dst[k] = src[i++];
        }
    }

    template<typename T>
    static void sort(vector<T> &src, vector<T> &dst, int lo, int hi) {
        // if (hi <= lo) return;
        if (hi <= lo + CUTOFF) {
            insertionSort(dst, lo, hi);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid);
        sort(dst, src, mid + 1, hi);

        // first num of right>=last num of left
        if (!(src[mid + 1] < src[mid])) {
            for (int i = lo; i <= hi; i++) dst[i] = src[i];
            return;
        }

        merge(src, dst, lo, mid, hi);
    }

    // sort from a[lo] to a[hi] using insertion sort
    template<typename T>
    static void insertionSort(vector<T> &a, int lo, int hi) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && a[j] < a[j - 1]; j--)
                swap(a[j], a[j - 1]);
    }

    /*******************************************************************
     *  Version that takes Comparator as argument.
     *******************************************************************/
    template<typename T, typename Comp>
    static void merge(vector<T> &src, vector<T> &dst, int lo, int mid, int hi, Comp comp) {
        int i = lo, j = mid + 1;
        for (int k = lo; k <= hi; k++) {
            if (i > mid) dst[k] = src[j++];
            else if (j > hi) dst[k] = src[i++];
            else if (comp(src[j], src[i])) dst[k] = src[j++];
            else dst[k] = src[i++];
        }
    }

    template<typename T, typename Comp>
    static void sort(vector<T> &src, vector<T> &dst, int lo, int hi, Comp comp) {
        // if (hi <= lo) return;
        if (hi <= lo + CUTOFF) {
            insertionSort(dst, lo, hi, comp);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid, comp);
        sort(dst, src, mid + 1, hi, comp);

        // using System.arraycopy() is a bit faster than the above loop
        if (!comp(src[mid + 1], src[mid])) {
            for (int i = lo; i <= hi; i++) dst[i] = src[i];
            return;
        }

        merge(src, dst, lo, mid, hi, comp);
    }

    // sort from a[lo] to a[hi] using insertion sort
    template<typename T, typename Comp>
    static void insertionSort(vector<T> &a, int lo, int hi, Comp comp) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && comp(a[j], a[j - 1]); j--)
                swap(a[j], a[j - 1]);
    }

private:
    static const int CUTOFF = 7;

};


#endif //CH2_MERGEX_H
