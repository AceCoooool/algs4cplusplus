#ifndef CH5_INPLACEMSD_H
#define CH5_INPLACEMSD_H

#include <vector>
#include <string>

using std::vector;
using std::string;

/**
 *  The {@code InplaceMSD} class provides static methods for sorting an
 *  array of extended ASCII strings using in-place MSD radix sort.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/51radix">Section 5.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Ivan Pesin
 */
class InplaceMSD {
public:
    InplaceMSD() = delete;

    /**
     * Rearranges the array of extended ASCII strings in ascending order.
     * This is an unstable sorting algorithm.
     *
     * @param a the array to be sorted
     */
    static void sort(vector<string> &a) {
        int n = a.size();
        sort(a, 0, n - 1, 0);
    }

private:
    // sort from a[lo] to a[hi], starting at the dth character
    static void sort(vector<string> &a, int lo, int hi, int d) {

        // cutoff to insertion sort for small subarrays
        if (hi <= lo + CUTOFF) {
            insertion(a, lo, hi, d);
            return;
        }

        // compute frequency counts
        vector<int> heads(R + 2);
        vector<int> tails(R + 1);
        for (int i = lo; i <= hi; i++) {
            int c = charAt(a[i], d);
            heads[c + 2]++;
        }

        // transform counts to indices
        heads[0] = lo;
        for (int r = 0; r < R + 1; r++) {
            heads[r + 1] += heads[r];
            tails[r] = heads[r + 1];
        }

        // sort by d-th character in-place
        for (int r = 0; r < R + 1; r++) {
            while (heads[r] < tails[r]) {
                int c = charAt(a[heads[r]], d);
                while (c + 1 != r) {
                    swap(a[heads[r]], a[heads[c + 1]++]);
                    c = charAt(a[heads[r]], d);
                }
                heads[r]++;
            }
        }

        // recursively sort for each character (excludes sentinel -1)
        for (int r = 0; r < R; r++)
            sort(a, tails[r], tails[r + 1] - 1, d + 1);
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

    // return dth character of s, -1 if d = length of string
    static int charAt(string s, int d) {
        if (d == s.length()) return -1;
        return s[d];
    }

private:
    static int R;        // extended ASCII alphabet size
    static int CUTOFF;   // cutoff to insertion sort
};

int InplaceMSD::R = 256;
int InplaceMSD::CUTOFF = 15;

#endif //CH5_INPLACEMSD_H
