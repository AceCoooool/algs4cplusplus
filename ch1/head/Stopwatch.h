#ifndef CH1_STOPWATCH_H
#define CH1_STOPWATCH_H

#include <chrono>

using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::microseconds;

/**
 *  The {@code Stopwatch} data type is for measuring
 *  the time that elapses between the start and end of a
 *  programming task (wall-clock time).
 *
 *  See {@link StopwatchCPU} for a version that measures CPU time.
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/14analysis">Section 1.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Stopwatch {
public:
    /**
     * Initializes a new stopwatch.
     */
    Stopwatch() : start(steady_clock::now()) {}

    /**
     * Returns the elapsed CPU time (in microseconds) since the stopwatch was created.
     *
     * @return elapsed CPU time (in microseconds) since the stopwatch was created
     */
    int elapsedTime() {
        auto now = steady_clock::now();
        return duration_cast<microseconds>(now - start).count();
    }


private:
    steady_clock::time_point start;
};

#endif //CH1_STOPWATCH_H
