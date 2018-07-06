#ifndef CH5_AMERICANFLAG_H
#define CH5_AMERICANFLAG_H

#include <vector>
#include <string>
#include <stack>
#include <cassert>

using std::swap;
using std::vector;
using std::string;
using std::stack;

/**
 *  The {@code AmericanFlag} class provides static methods for sorting an
 *  array of extended ASCII strings or integers in-place using
 *  American flag sort. This is a non-recursive implementation.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/51radix">Section 5.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne
 *  and <a href = "http://static.usenix.org/publications/compsystems/1993/win_mcilroy.pdf">
 *  Engineering Radix Sort</a> by McIlroy and Bostic.
 *  For a version that uses only one auxilary array, see {@link AmericanFlagX}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *  @author Ivan Pesin
 */
class AmericanFlag {
public:
    AmericanFlag() = delete;

    /**
     * Rearranges the array of extended ASCII strings in ascending order.
     * This is an unstable sorting algorithm.
     *
     * @param a the array to be sorted
     */
    static void sort(vector<string> &a) {
        sort(a, 0, a.size() - 1);
    }

    // sort from a[lo] to a[hi], starting at the dth character
    static void sort(vector<string> &a, int lo, int hi) {
        // one-time allocation of data structures
        stack<int> st;
        vector<int> first(R + 2);
        vector<int> next(R + 2);
        int d = 0; // character index to sort by

        st.push(lo);
        st.push(hi);
        st.push(d);

        while (!st.empty()) {
            d = st.top();
            st.pop();
            hi = st.top();
            st.pop();
            lo = st.top();
            st.pop();

            if (hi <= lo + CUTOFF) {
                insertion(a, lo, hi, d);
                continue;
            }

            // compute frequency counts
            for (int i = lo; i <= hi; i++) {
                int c = charAt(a[i], d) + 1; // account for -1 representing end-of-string
                first[c + 1]++;
            }

            // first[c] = location of first string whose dth character = c
            first[0] = lo;
            for (int c = 0; c <= R; c++) {
                first[c + 1] += first[c];

                if (c > 0 && first[c + 1] - 1 > first[c]) {
                    // add subproblem for character c (excludes sentinel c == 0)
                    st.push(first[c]);
                    st.push(first[c + 1] - 1);
                    st.push(d + 1);
                }
            }

            // next[c] = location to place next string whose dth character = c
            for (int c = 0; c < R + 2; c++)
                next[c] = first[c];

            // permute data in place
            for (int k = lo; k <= hi; k++) {
                int c = charAt(a[k], d) + 1;
                while (first[c] > k) {
                    swap(a[k], a[next[c]++]);
                    c = charAt(a[k], d) + 1;
                }
                next[c]++;
            }

            // clear first[] and next[] arrays
            for (int c = 0; c < R + 2; c++) {
                first[c] = 0;
                next[c] = 0;
            }
        }
    }

    // return dth character of s, -1 if d = length of string
private:
    static int charAt(string s, int d) {
        assert(d >= 0 && d <= s.length());
        if (d == s.length()) return -1;
        return s[d];
    }

    // insertion sort a[lo..hi], starting at dth character
    static void insertion(vector<string> &a, int lo, int hi, int d) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j - 1], d); j--)
                swap(a[j], a[j - 1]);
    }

    // is v less than w, starting at character d
    static bool less(string v, string w, int d) {
        // assert v.substring(0, d).equals(w.substring(0, d));
        for (int i = d; i < std::min(v.length(), w.length()); i++) {
            if (v[i] < w[i]) return true;
            if (v[i] > w[i]) return false;
        }
        return v.length() < w.length();
    }

private:
    static const int BITS_PER_BYTE;
    static const int BITS_PER_INT;   // each Java int is 32 bits
    static const int R;              // extend ASCII alphabet size
    static const int CUTOFF;         // cutoff to insertion sort

};

const int AmericanFlag::BITS_PER_BYTE = 8;
const int AmericanFlag::BITS_PER_INT = 32;   // each Java int is 32 bits
const int AmericanFlag::R = 256;             // extend ASCII alphabet size
const int AmericanFlag::CUTOFF = 15;         // cutoff to insertion sort

#endif //CH5_AMERICANFLAG_H
