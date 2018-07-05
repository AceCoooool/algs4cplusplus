#ifndef CH5_LSD_H
#define CH5_LSD_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 *  The {@code LSD} class provides static methods for sorting an
 *  array of <em>w</em>-character strings or 32-bit integers using LSD radix sort.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/51radix">Section 5.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class LSD {
public:
    // do not instantiate
    LSD() = delete;

    /**
     * Rearranges the array of W-character strings in ascending order.
     *
     * @param a the array to be sorted
     * @param w the number of characters per string
     */
    static void sort(vector<string> &a, int w) {
        int n = a.size();
        int R = 256;   // extend ASCII alphabet size
        vector<string> aux(n);

        for (int d = w - 1; d >= 0; d--) {
            // sort by key-indexed counting on dth character

            // compute frequency counts
            vector<int> count(R + 1);
            for (int i = 0; i < n; i++)
                count[a[i][d] + 1]++;

            // compute cumulates
            for (int r = 0; r < R; r++)
                count[r + 1] += count[r];

            // move data
            for (int i = 0; i < n; i++)
                aux[count[a[i][d]]++] = a[i];

            // copy back
            for (int i = 0; i < n; i++)
                a[i] = aux[i];
        }
    }

    /**
     * Rearranges the array of 32-bit integers in ascending order.
     * This is about 2-3x faster than Arrays.sort().
     *
     * @param a the array to be sorted
     */
    static void sort(vector<int> &a) {
        int BITS = 32;                 // each int is 32 bits
        int R = 1 << BITS_PER_BYTE;    // each bytes is between 0 and 255
        int MASK = R - 1;              // 0xFF
        int w = BITS / BITS_PER_BYTE;  // each int is 4 bytes

        int n = a.size();

        vector<int> aux(n);

        for (int d = 0; d < w; d++) {

            // compute frequency counts
            vector<int> count(R+1);
            for (int i = 0; i < n; i++) {
                int c = (a[i] >> BITS_PER_BYTE * d) & MASK;
                count[c + 1]++;
            }

            // compute cumulates
            for (int r = 0; r < R; r++)
                count[r + 1] += count[r];

            // for most significant byte, 0x80-0xFF comes before 0x00-0x7F
            if (d == w - 1) {
                int shift1 = count[R] - count[R / 2];
                int shift2 = count[R / 2];
                for (int r = 0; r < R / 2; r++)
                    count[r] += shift1;
                for (int r = R / 2; r < R; r++)
                    count[r] -= shift2;
            }

            // move data
            for (int i = 0; i < n; i++) {
                int c = (a[i] >> BITS_PER_BYTE * d) & MASK;
                aux[count[c]++] = a[i];
            }

            // copy back
            for (int i = 0; i < n; i++)
                a[i] = aux[i];
        }
    }

private:
    static int BITS_PER_BYTE;
};

int LSD::BITS_PER_BYTE = 8;

#endif //CH5_LSD_H
