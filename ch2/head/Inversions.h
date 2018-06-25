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
            }
            else a[k] = aux[i++];
        }
        return inversions;
    }

};

#endif //CH2_INVERSIONS_H
