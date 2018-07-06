#ifndef CH5_AMERICANFLAGX_H
#define CH5_AMERICANFLAGX_H

#include <vector>
#include <string>
#include <stack>
#include <cassert>

using std::vector;
using std::string;
using std::stack;
using std::swap;

/**
 *  The {@code AmericanFlagX} class provides static methods for sorting an
 *  array of extended ASCII strings or integers in-place using
 *  American Flag sort. This implementation is non-recursive and uses only
 *  one auxiliary array.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/51radix">Section 5.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne
 *  and <a href = "http://static.usenix.org/publications/compsystems/1993/win_mcilroy.pdf">
 *  Engineering Radix Sort</a> by McIlroy and Bostic.
 *  For a version that uses two auxilary arrays, see {@link AmericanFlag}.
 *
 *  @author Ivan Pesin
 */
class AmericanFlagX {
public:
    AmericanFlagX() = delete;

    /**
     * Rearranges the array of extended ASCII strings in ascending order.
     * This is an unstable in-place sorting algorithm.
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
        vector<int> count(R + 1);
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
                count[c]++;
            }

            // accumulate counts relative to a[0], so that
            // count[c] is the number of keys <= c
            count[0] += lo;
            for (int c = 0; c < R; c++) {
                count[c + 1] += count[c];

                if (c > 0 && count[c + 1] - 1 > count[c]) {
                    // add subproblem for character c (excludes sentinel c == 0)
                    st.push(count[c]);
                    st.push(count[c + 1] - 1);
                    st.push(d + 1);
                }
            }

            // permute data in place
            // for details and proof see Knuth Theorem 5.1.2B and ch 5.2 excercise 13.
            for (int r = hi; r >= lo; r--) {

                // locate element that must be shifted right of r
                int c = charAt(a[r], d) + 1;
                while (r >= lo && count[c] - 1 <= r) {
                    if (count[c] - 1 == r) count[c]--;
                    r--;
                    if (r >= lo) c = charAt(a[r], d) + 1;
                }

                // if r < lo the subarray is sorted.
                if (r < lo) break;

                // permute a[r] until correct element is in place
                while (--count[c] != r) {
                    swap(a[r], a[count[c]]);
                    c = charAt(a[r], d) + 1;
                }
            }

            // clear count[] array
            for (int c = 0; c < R + 1; c++)
                count[c] = 0;
        }
    }

private:
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

    // return dth character of s, -1 if d = length of string
    static int charAt(string s, int d) {
        assert(d >= 0 && d <= s.length());
        if (d == s.length()) return -1;
        return s[d];
    }

private:
    static const int R;        // extend ASCII alphabet size
    static const int CUTOFF;   // cutoff to insertion sort

};

const int AmericanFlagX::R = 256;
const int AmericanFlagX::CUTOFF = 15;

#endif //CH5_AMERICANFLAGX_H
