#ifndef CH1_KNUTH_H
#define CH1_KNUTH_H

#include <vector>
#include <random>

using std::vector;
using std::uniform_int_distribution;
using std::swap;

std::random_device rd;
std::mt19937 gen(rd());

/**
 *  The {@code Knuth} class provides a client for reading in a
 *  sequence of strings and <em>shuffling</em> them using the Knuth (or Fisher-Yates)
 *  shuffling algorithm. This algorithm guarantees to rearrange the
 *  elements in uniformly random order, under
 *  the assumption that Math.random() generates independent and
 *  uniformly distributed numbers between 0 and 1.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/11model">Section 1.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  See {@link StdRandom} for versions that shuffle arrays and
 *  subarrays of objects, doubles, and ints.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Knuth {
public:
    Knuth() = delete;

    /**
     * Rearranges an array of objects in uniformly random order
     * (under the assumption that {@code Math.random()} generates independent
     * and uniformly distributed numbers between 0 and 1).
     * @param a the array to be shuffled
     */
    template<typename T>
    static void shuffle(vector<T> &a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            // choose index uniformly in [0, i]
            uniform_int_distribution<> dis(0, i);
            int r = dis(gen);
            swap(a[r], a[i]);
        }
    }

    /**
     * Rearranges an array of objects in uniformly random order
     * (under the assumption that {@code Math.random()} generates independent
     * and uniformly distributed numbers between 0 and 1).
     * @param a the array to be shuffled
     */
    template<typename T>
    static void shuffleAlternate(vector<T> &a) {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            // choose index uniformly in [i, n-1]
            uniform_int_distribution<> dis(0, n - i);
            int r = i + dis(gen);
            swap(a[r], a[i]);
        }
    }

};

#endif //CH1_KNUTH_H
