#ifndef CH2_QUICKBENTLEYMCILROY_H
#define CH2_QUICKBENTLEYMCILROY_H

#include <vector>
#include <iostream>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code QuickBentleyMcIlroy} class provides static methods for sorting
 *  an array using an optimized version of quicksort (using Bentley-McIlroy
 *  3-way partitioning, Tukey's ninther, and cutoff to insertion sort).
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/23quick">Section 2.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class QuickBentleyMcIlroy {
public:
    QuickBentleyMcIlroy() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
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
    template<typename T>
    static void sort(vector<T> &a, int lo, int hi) {
        int n = hi - lo + 1;

        // cutoff to insertion sort
        if (n <= INSERTION_SORT_CUTOFF) {
            insertionSort(a, lo, hi);
            return;
        } else if (n <= MEDIAN_OF_3_CUTOFF) {   // use median-of-3 as partitioning element
            int m = median3(a, lo, lo + n / 2, hi);
            swap(a[m], a[lo]);
        } else {      // use Tukey ninther as partitioning element
            int eps = n / 8;
            int mid = lo + n / 2;
            int m1 = median3(a, lo, lo + eps, lo + eps + eps);
            int m2 = median3(a, mid - eps, mid, mid + eps);
            int m3 = median3(a, hi - eps - eps, hi - eps, hi);
            int ninther = median3(a, m1, m2, m3);
            swap(a[ninther], a[lo]);
        }

        // Bentley-McIlroy 3-way partitioning
        int i = lo, j = hi + 1;
        int p = lo, q = hi + 1;
        T v = a[lo];
        while (true) {
            while (a[++i] < v)
                if (i == hi) break;
            while (v < a[--j])
                if (j == lo) break;

            // pointers cross
            if (i == j && a[i] == v)
                swap(a[++p], a[i]);
            if (i >= j) break;

            swap(a[i], a[j]);
            if (a[i] == v) swap(a[++p], a[i]);
            if (a[j] == v) swap(a[--q], a[j]);
        }


        i = j + 1;
        for (int k = lo; k <= p; k++)
            swap(a[k], a[j--]);
        for (int k = hi; k >= q; k--)
            swap(a[k], a[i++]);

        sort(a, lo, j);
        sort(a, i, hi);
    }

    // sort from a[lo] to a[hi] using insertion sort
    template<typename T>
    static void insertionSort(vector<T> &a, int lo, int hi) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && (a[j] < a[j - 1]); j--)
                swap(a[j], a[j - 1]);
    }


    // return the index of the median element among a[i], a[j], and a[k]
    template<typename T>
    static int median3(vector<T> &a, int i, int j, int k) {
        return a[i] < a[j] ? (a[j] < a[k] ? j : (a[i] < a[k] ? k : i)) : (a[k] < a[j] ? j : (a[k] < a[i] ? k : i));
    }

private:
    // cutoff to insertion sort, must be >= 1
    static int INSERTION_SORT_CUTOFF;

    // cutoff to median-of-3 partitioning
    static int MEDIAN_OF_3_CUTOFF;
};

int QuickBentleyMcIlroy::INSERTION_SORT_CUTOFF = 8;
int QuickBentleyMcIlroy::MEDIAN_OF_3_CUTOFF = 40;

#endif //CH2_QUICKBENTLEYMCILROY_H
