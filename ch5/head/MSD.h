#ifndef CH5_MSD_H
#define CH5_MSD_H

#include <vector>
#include <string>

using std::vector;
using std::string;
using std::swap;

/**
 *  The {@code MSD} class provides static methods for sorting an
 *  array of extended ASCII strings or integers using MSD radix sort.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/51radix">Section 5.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class MSD {
public:
    MSD() = delete;

    /**
     * Rearranges the array of extended ASCII strings in ascending order.
     *
     * @param a the array to be sorted
     */
    static void sort(vector<string> &a) {
        int n = a.size();
        vector<string> aux(n);
        sort(a, 0, n - 1, 0, aux);
    }

private:
    // sort from a[lo] to a[hi], starting at the dth character
    static void sort(vector<string> &a, int lo, int hi, int d, vector<string> &aux) {

        // cutoff to insertion sort for small subarrays
        if (hi <= lo + CUTOFF) {
            insertion(a, lo, hi, d);
            return;
        }

        // compute frequency counts
        vector<int> count(R + 2);
        for (int i = lo; i <= hi; i++) {
            int c = charAt(a[i], d);
            count[c + 2]++;
        }

        // transform counts to indicies
        for (int r = 0; r < R + 1; r++)
            count[r + 1] += count[r];

        // distribute
        for (int i = lo; i <= hi; i++) {
            int c = charAt(a[i], d);
            aux[count[c + 1]++] = a[i];
        }

        // copy back
        for (int i = lo; i <= hi; i++)
            a[i] = aux[i - lo];


        // recursively sort for each character (excludes sentinel -1)
        for (int r = 0; r < R; r++)
            sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
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

public:
    /**
     * Rearranges the array of 32-bit integers in ascending order.
     * Currently assumes that the integers are nonnegative.
     *
     * @param a the array to be sorted
     */
    static void sort(vector<int> &a) {
        int n = a.size();
        vector<int> aux(n);
        sort(a, 0, n - 1, 0, aux);
    }

private:
    // MSD sort from a[lo] to a[hi], starting at the dth byte
    static void sort(vector<int> &a, int lo, int hi, int d, vector<int> &aux) {
        // cutoff to insertion sort for small subarrays
        if (hi <= lo + CUTOFF) {
            insertion(a, lo, hi, d);
            return;
        }

        // compute frequency counts (need R = 256)
        vector<int> count(R + 1);
        int mask = R - 1;   // 0xFF;
        int shift = BITS_PER_INT - BITS_PER_BYTE * d - BITS_PER_BYTE;
        for (int i = lo; i <= hi; i++) {
            int c = (a[i] >> shift) & mask;
            count[c + 1]++;
        }

        // transform counts to indicies
        for (int r = 0; r < R; r++)
            count[r + 1] += count[r];

        // distribute
        for (int i = lo; i <= hi; i++) {
            int c = (a[i] >> shift) & mask;
            aux[count[c]++] = a[i];
        }

        // copy back
        for (int i = lo; i <= hi; i++)
            a[i] = aux[i - lo];

        // no more bits
        if (d == 4) return;

        // recursively sort for each character
        if (count[0] > 0)
            sort(a, lo, lo + count[0] - 1, d + 1, aux);
        for (int r = 0; r < R; r++)
            if (count[r + 1] > count[r])
                sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
    }

private:
    // TODO: insertion sort a[lo..hi], starting at dth character
    static void insertion(vector<int> &a, int lo, int hi, int d) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && a[j] < a[j - 1]; j--)
                swap(a[j], a[j - 1]);
    }

private:
    static int BITS_PER_BYTE;
    static int BITS_PER_INT;   // each Java int is 32 bits
    static int R;              // extended ASCII alphabet size
    static int CUTOFF;         // cutoff to insertion sort
};

int MSD::BITS_PER_BYTE = 8;
int MSD::BITS_PER_INT = 32;   // each Java int is 32 bits
int MSD::R = 256;             // extended ASCII alphabet size
int MSD::CUTOFF = 15;         // cutoff to insertion sort

#endif //CH5_MSD_H
