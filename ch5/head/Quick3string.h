#ifndef CH5_QUICK3STRING_H
#define CH5_QUICK3STRING_H

#include <string>
#include <vector>
#include <random>
#include <algorithm>

std::random_device rd;
std::mt19937 g(rd());
using std::swap;
using std::string;
using std::vector;
using std::shuffle;

/**
 *  The {@code Quick3string} class provides static methods for sorting an
 *  array of strings using 3-way radix quicksort.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/51radix">Section 5.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Quick3string {
public:
    Quick3string() = delete;


    /**
     * Rearranges the array of strings in ascending order.
     *
     * @param a the array to be sorted
     */
    static void sort(vector<string> &a) {
        shuffle(a.begin(), a.end(), g);
        sort(a, 0, a.size() - 1, 0);
    }

private:
    // 3-way string quicksort a[lo..hi] starting at dth character
    static void sort(vector<string> &a, int lo, int hi, int d) {
        // cutoff to insertion sort for small subarrays
        if (hi <= lo + CUTOFF) {
            insertion(a, lo, hi, d);
            return;
        }

        int lt = lo, gt = hi;
        int v = charAt(a[lo], d);
        int i = lo + 1;
        while (i <= gt) {
            int t = charAt(a[i], d);
            if (t < v) swap(a[lt++], a[i++]);
            else if (t > v) swap(a[i], a[gt--]);
            else i++;
        }

        // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
        sort(a, lo, lt - 1, d);
        if (v >= 0) sort(a, lt, gt, d + 1);
        sort(a, gt + 1, hi, d);
    }

    // sort from a[lo] to a[hi], starting at the dth character
    static void insertion(vector<string> &a, int lo, int hi, int d) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j - 1], d); j--)
                swap(a[j], a[j - 1]);
    }

    // is v less than w, starting at character d
    // DEPRECATED BECAUSE OF SLOW SUBSTRING EXTRACTION IN JAVA 7
    // private static boolean less(String v, String w, int d) {
    //    assert v.substring(0, d).equals(w.substring(0, d));
    //    return v.substring(d).compareTo(w.substring(d)) < 0;
    // }

    // is v less than w, starting at character d
    static bool less(string v, string w, int d) {
        for (int i = d; i < std::min(v.length(), w.length()); i++) {
            if (v[i] < w[i]) return true;
            if (v[i] > w[i]) return false;
        }
        return v.length() < w.length();
    }

    // return the dth character of s, -1 if d = length of s
    static int charAt(string s, int d) {
        if (d == s.length()) return -1;
        return s[d];
    }

private:
    static int CUTOFF;   // cutoff to insertion sort
};

int Quick3string::CUTOFF = 15;

#endif //CH5_QUICK3STRING_H
