#ifndef CH1_DOUBLINGTEST_H
#define CH1_DOUBLINGTEST_H

#include <vector>
#include <random>
#include "Stopwatch.h"
#include "ThreeSum.h"

const int MAXIMUM_INTEGER = 1000000;

using std::vector;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(-MAXIMUM_INTEGER, MAXIMUM_INTEGER);

/**
 *  The {@code DoublingTest} class provides a client for measuring
 *  the running time of a method using a doubling test.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/14analysis">Section 1.4</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DoublingTest {
public:
    DoublingTest() = delete;

    /**
     * Returns the amount of time to call {@code ThreeSum.count()} with <em>n</em>
     * random 6-digit integers.
     * @param n the number of integers
     * @return amount of time (in seconds) to call {@code ThreeSum.count()}
     *   with <em>n</em> random 6-digit integers
     */
    static double timeTrial(int n) {
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = dis(gen);
        }
        Stopwatch timer;
        ThreeSum::count(a);
        return timer.elapsedTime();
    }
};

#endif //CH1_DOUBLINGTEST_H
