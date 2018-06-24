#ifndef CH2_BINARYINSERTION_H
#define CH2_BINARYINSERTION_H

#include <vector>
#include <iostream>

using std::vector;
using std::swap;
using std::cout;
using std::endl;

/**
 *  The {@code BinaryInsertion} class provides a static method for sorting an
 *  array using an optimized binary insertion sort with half exchanges.
 *  <p>
 *  This implementation makes ~ n lg n compares for any array of length n.
 *  However, in the worst case, the running time is quadratic because the
 *  number of array accesses can be proportional to n^2 (e.g, if the array
 *  is reverse sorted). As such, it is not suitable for sorting large
 *  arrays (unless the number of inversions is small).
 *  <p>
 *  The sorting algorithm is stable and uses O(1) extra memory.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Ivan Pesin
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class BinaryInsertion {
public:
    // This class should not be instantiated.
    BinaryInsertion() = delete;

    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template<typename T>
    static void sort(vector<T> &a) {
        int n = a.size();
        for (int i = 1; i < n; i++) {

            // binary search to determine index j at which to insert a[i]
            T v = a[i];
            int lo = 0, hi = i;
            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;
                if (v < a[mid]) hi = mid;
                else lo = mid + 1;
            }

            // insetion sort with "half exchanges"
            // (insert a[i] at index j and shift a[j], ..., a[i-1] to right)
            for (int j = i; j > lo; --j)
                a[j] = a[j - 1];
            a[lo] = v;
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

#endif //CH2_BINARYINSERTION_H
