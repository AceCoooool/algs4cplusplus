#ifndef CH1_STATICSETOFINTS_H
#define CH1_STATICSETOFINTS_H

#include <vector>
#include <algorithm>
#include <stdexcept>

using std::vector;
using std::runtime_error;


/**
 *  The {@code StaticSETofInts} class represents a set of integers.
 *  It supports searching for a given integer is in the set. It accomplishes
 *  this by keeping the set of integers in a sorted array and using
 *  binary search to find the given integer.
 *  <p>
 *  The <em>rank</em> and <em>contains</em> operations take
 *  logarithmic time in the worst case.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

class StaticSETofInts {
public:
    /**
     * Initializes a set of integers specified by the integer array.
     * @param keys the array of integers
     * @throws IllegalArgumentException if the array contains duplicate integers
     */
    StaticSETofInts(vector<int> keys) : a(keys) {
        sort(a.begin(), a.end());
        for (int i = 1; i < a.size(); ++i) {
            if (a[i] == a[i - 1])
                throw runtime_error("Argument arrays contains duplicate keys.");
        }
    }

    /**
     * Returns either the index of the search key in the sorted array
     * (if the key is in the set) or -1 (if the key is not in the set).
     * @param key the search key
     * @return the number of keys in this set less than the key (if the key is in the set)
     * or -1 (if the key is not in the set).
     */
    int rank(int key) {
        int lo = 0, hi = a.size() - 1;
        while (lo <= hi) {
            auto mid = lo + (hi - lo) / 2;
            if (key < a[mid]) hi = mid - 1;
            else if (key > a[mid]) lo = mid + 1;
            else return mid;
        }
        return -1;
    }

    /**
     * Is the key in this set of integers?
     * @param key the search key
     * @return true if the set of integers contains the key; false otherwise
     */
    bool contains(int key) {
        return rank(key) != -1;
    }

private:
    vector<int> a;
};

#endif //CH1_STATICSETOFINTS_H
