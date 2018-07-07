#ifndef CH5_KMP_H
#define CH5_KMP_H

#include <vector>
#include <string>

using std::string;
using std::vector;

/**
 *  The {@code KMP} class finds the first occurrence of a pattern string
 *  in a text string.
 *  <p>
 *  This implementation uses a version of the Knuth-Morris-Pratt substring search
 *  algorithm. The version takes time proportional to <em>n</em> + <em>m R</em>
 *  in the worst case, where <em>n</em> is the length of the text string,
 *  <em>m</em> is the length of the pattern, and <em>R</em> is the alphabet size.
 *  It uses extra space proportional to <em>m R</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/53substring">Section 5.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 */
class KMP {
public:
    /**
     * Preprocesses the pattern string.
     *
     * @param pat the pattern string
     */
    KMP(string pat) : R(256), pat(pat), dfa(R, vector<int>(pat.length(), 0)) {
        // build DFA from pattern
        int m = pat.length();
        dfa[pat[0]][0] = 1;
        for (int x = 0, j = 1; j < m; j++) {
            for (int c = 0; c < R; c++)
                dfa[c][j] = dfa[c][x];    // Copy mismatch cases.
            dfa[pat[j]][j] = j + 1;       // Set match case.
            x = dfa[pat[j]][x];           // Update restart state.
        }
    }

    /**
     * Preprocesses the pattern string.
     *
     * @param pattern the pattern string
     * @param R the alphabet size
     */
    KMP(vector<char> &pattern, int R) : R(R), pattern(pattern), dfa(R, vector<int>(pattern.size(), 0)) {
        int m = pattern.size();
        dfa[pattern[0]][0] = 1;
        for (int x = 0, j = 1; j < m; j++) {
            for (int c = 0; c < R; c++)
                dfa[c][j] = dfa[c][x];     // Copy mismatch cases.
            dfa[pattern[j]][j] = j + 1;      // Set match case.
            x = dfa[pattern[j]][x];        // Update restart state.
        }
    }

    /**
     * Returns the index of the first occurrrence of the pattern string
     * in the text string.
     *
     * @param  txt the text string
     * @return the index of the first occurrence of the pattern string
     *         in the text string; N if no such match
     */
    int search(string &txt) {
        // simulate operation of DFA on text
        int m = pat.length();
        int n = txt.length();
        int i, j;
        for (i = 0, j = 0; i < n && j < m; i++) {
            j = dfa[txt[i]][j];
        }
        if (j == m) return i - m;    // found
        return n;                    // not found
    }

    /**
     * Returns the index of the first occurrrence of the pattern string
     * in the text string.
     *
     * @param  text the text string
     * @return the index of the first occurrence of the pattern string
     *         in the text string; N if no such match
     */
    int search(vector<char> &text) {

        // simulate operation of DFA on text
        int m = pattern.size();
        int n = text.size();
        int i, j;
        for (i = 0, j = 0; i < n && j < m; i++) {
            j = dfa[text[i]][j];
        }
        if (j == m) return i - m;    // found
        return n;                    // not found
    }

private:
    const int R;              // the radix
    vector<vector<int>> dfa;  // the KMP automoton
    vector<char> pattern;     // either the character array for the pattern
    string pat;               // or the pattern string
};


#endif //CH5_KMP_H
