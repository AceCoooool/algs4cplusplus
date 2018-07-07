#ifndef CH5_BOYERMOORE_H
#define CH5_BOYERMOORE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

/**
 *  The {@code BoyerMoore} class finds the first occurrence of a pattern string
 *  in a text string.
 *  <p>
 *  This implementation uses the Boyer-Moore algorithm (with the bad-character
 *  rule, but not the strong good suffix rule).
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/53substring">Section 5.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 */
class BoyerMoore {
public:
    /**
     * Preprocesses the pattern string.
     *
     * @param pat the pattern string
     */
    BoyerMoore(string pat) : R(256), pat(pat), right(R, -1) {
        // position of rightmost occurrence of c in the pattern
        for (int j = 0; j < pat.length(); j++)
            right[pat[j]] = j;
    }

    /**
     * Preprocesses the pattern string.
     *
     * @param pattern the pattern string
     * @param R the alphabet size
     */
    BoyerMoore(vector<char> pattern, int R) : R(R), pattern(pattern), right(R, -1) {
        for (int j = 0; j < pattern.size(); j++)
            right[pattern[j]] = j;
    }

    /**
     * Returns the index of the first occurrrence of the pattern string
     * in the text string.
     *
     * @param  txt the text string
     * @return the index of the first occurrence of the pattern string
     *         in the text string; n if no such match
     */
    int search(string txt) {
        int m = pat.length();
        int n = txt.length();
        int skip;
        for (int i = 0; i <= n - m; i += skip) {
            skip = 0;
            for (int j = m - 1; j >= 0; j--) {
                if (pat[j] != txt[i + j]) {
                    skip = std::max(1, j - right[txt[i + j]]);
                    break;
                }
            }
            if (skip == 0) return i;    // found
        }
        return n;                       // not found
    }

    /**
     * Returns the index of the first occurrrence of the pattern string
     * in the text string.
     *
     * @param  text the text string
     * @return the index of the first occurrence of the pattern string
     *         in the text string; n if no such match
     */
    int search(vector<char> &text) {
        int m = pattern.size();
        int n = text.size();
        int skip;
        for (int i = 0; i <= n - m; i += skip) {
            skip = 0;
            for (int j = m - 1; j >= 0; j--) {
                if (pattern[j] != text[i + j]) {
                    skip = std::max(1, j - right[text[i + j]]);
                    break;
                }
            }
            if (skip == 0) return i;    // found
        }
        return n;                       // not found
    }

private:
    int R;                  // the radix
    vector<int> right;      // the bad-character skip array
    vector<char> pattern;   // store the pattern as a character array
    string pat;             // or as a string
};

#endif //CH5_BOYERMOORE_H
