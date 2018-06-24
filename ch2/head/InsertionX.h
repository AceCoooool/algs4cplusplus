#ifndef CH2_INSERTIONX_H
#define CH2_INSERTIONX_H

#include <vector>
#include <iostream>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code InsertionX} class provides static methods for sorting
 *  an array using an optimized version of insertion sort (with half exchanges
 *  and a sentinel).
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class InsertionX {
public:
    // This class should not be instantiated.
    InsertionX() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        int n = a.size();

        // put smallest element in position to serve as sentinel
        int exchanges = 0;
        for (int i = n - 1; i > 0; i--) {
            if (a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
                exchanges++;
            }
        }
        if (exchanges == 0) return;

        // insertion sort with half-exchanges
        for (int i = 2; i < n; i++) {
            T v = a[i];
            int j = i;
            while (v < a[j - 1]) {
                a[j] = a[j - 1];
                j--;
            }
            a[j] = v;
        }
    }

    // print array to standard output
    template<typename T>
    static void show(vector<T> &a) {
        for (int i = 0; i < a.size(); i++) {
            cout << a[i] << endl;
        }
    }
};

#endif //CH2_INSERTIONX_H
