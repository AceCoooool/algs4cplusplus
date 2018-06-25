#ifndef CH2_QUICK3WAY_H
#define CH2_QUICK3WAY_H

#include <vector>
#include <iostream>
#include <random>
#include <algorithm>

using std::vector;
using std::random_device;
using std::mt19937;
using std::shuffle;
using std::swap;
using std::cout;
using std::endl;

random_device rd;
mt19937 g(rd());

/**
 *  The {@code Quick3way} class provides static methods for sorting an
 *  array using quicksort with 3-way partitioning.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/23quick">Section 2.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Quick3way {
public:
    // This class should not be instantiated.
    Quick3way() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        shuffle(a.begin(), a.end(), g);
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
    // quicksort the subarray a[lo .. hi] using 3-way partitioning
    template<typename T>
    static void sort(vector<T> &a, int lo, int hi) {
        static auto f = [](T a, T b) { return a > b ? 1 : (a < b ? -1 : 0); };
        if (hi <= lo) return;
        int lt = lo, gt = hi;
        T v = a[lo];
        int i = lo + 1;
        while (i <= gt) {
            int cmp = f(a[i], v);
            if (cmp < 0) swap(a[lt++], a[i++]);
            else if (cmp > 0) swap(a[i], a[gt--]);
            else i++;
        }

        // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
        sort(a, lo, lt - 1);
        sort(a, gt + 1, hi);
    }
};

#endif //CH2_QUICK3WAY_H
