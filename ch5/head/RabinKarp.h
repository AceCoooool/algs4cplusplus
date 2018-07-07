#ifndef CH5_RABINKARP_H
#define CH5_RABINKARP_H

#include <string>
#include <vector>
#include <stdexcept>

using std::invalid_argument;
using std::vector;
using std::string;

/**
 *  The {@code RabinKarp} class finds the first occurrence of a pattern string
 *  in a text string.
 *  <p>
 *  This implementation uses the Rabin-Karp algorithm.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/53substring">Section 5.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 */
class RabinKarp {
public:
    /**
     * Preprocesses the pattern string.
     *
     * @param pattern the pattern string
     * @param R the alphabet size
     */
    RabinKarp(vector<char> pattern, int R) : pat(pattern.begin(), pattern.end()), R(R) {
        throw invalid_argument("Operation not supported yet");
    }

    /**
     * Preprocesses the pattern string.
     *
     * @param pat the pattern string
     */
    RabinKarp(string pat) : pat(pat), m(pat.length()), R(256), q(997), RM(1) {
        // precompute R^(m-1) % q for use in removing leading digit
        for (int i = 1; i <= m - 1; i++)
            RM = (R * RM) % q;
        patHash = hash(pat, m);
    }

    /**
     * Returns the index of the first occurrrence of the pattern string
     * in the text string.
     *
     * @param  txt the text string
     * @return the index of the first occurrence of the pattern string
     *         in the text string; n if no such match
     */
    int search(string &txt) {
        int n = txt.length();
        if (n < m) return n;
        long txtHash = hash(txt, m);

        // check for match at offset 0
        if ((patHash == txtHash) && check(txt, 0))
            return 0;

        // check for hash match; if hash match, check for exact match
        for (int i = m; i < n; i++) {
            // Remove leading digit, add trailing digit, check for match.
            txtHash = (txtHash + q - RM * txt[i - m] % q) % q;
            txtHash = (txtHash * R + txt[i]) % q;

            // match
            int offset = i - m + 1;
            if ((patHash == txtHash) && check(txt, offset))
                return offset;
        }

        // no match
        return n;
    }

private:
    // Compute hash for key[0..m-1].
    long hash(string key, int m) {
        long h = 0;
        for (int j = 0; j < m; j++)
            h = (R * h + key[j]) % q;
        return h;
    }

    // Las Vegas version: does pat[] match txt[i..i-m+1] ?
    bool check(string &txt, int i) {
        for (int j = 0; j < m; j++)
            if (pat[j] != txt[i + j])
                return false;
        return true;
    }

    // TODO: prime generator: here use 997
//    // a random 31-bit prime
//    static long longRandomPrime() {
//        BigInteger prime = BigInteger.probablePrime(31, new Random());
//        return prime.longValue();
//    }

private:
    string pat;    // the pattern  // needed only for Las Vegas
    long patHash;  // pattern hash value
    int m;         // pattern length
    long q;        // a large prime, small enough to avoid long overflow
    int R;         // radix
    long RM;       // R^(M-1) % Q
};

#endif //CH5_RABINKARP_H
