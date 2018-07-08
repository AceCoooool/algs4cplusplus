#ifndef CH1_ACCUMULATOR_H
#define CH1_ACCUMULATOR_H

#include <cmath>
#include <limits>
#include <ostream>

using std::numeric_limits;
using std::ostream;

/**
 *  The {@code Accumulator} class is a data type for computing the running
 *  mean, sample standard deviation, and sample variance of a stream of real
 *  numbers. It provides an example of a mutable data type and a streaming
 *  algorithm.
 *  <p>
 *  This implementation uses a one-pass algorithm that is less susceptible
 *  to floating-point roundoff error than the more straightforward
 *  implementation based on saving the sum of the squares of the numbers.
 *  This technique is due to
 *  <a href = "https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm">B. P. Welford</a>.
 *  Each operation takes constant time in the worst case.
 *  The amount of memory is constant - the data values are not stored.
 *  <p>
 *  For additional documentation, 
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of 
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne. 
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Accumulator {
public:
    /**
     * Initializes an accumulator.
     */
    Accumulator() = default;

    /**
     * Adds the specified data value to the accumulator.
     * @param  x the data value
     */
    void addDataValue(double x) {
        n++;
        double delta = x - mu;
        mu += delta / n;
        sumval += (double) (n - 1) / n * delta * delta;
    }

    /**
     * Returns the mean of the data values.
     * @return the mean of the data values
     */
    double mean() const {
        return mu;
    }

    /**
     * Returns the sample variance of the data values.
     * @return the sample variance of the data values
     */
    double var() const {
        if (n <= 1) return numeric_limits<double>::quiet_NaN();
        return sumval / (n - 1);
    }

    /**
     * Returns the sample standard deviation of the data values.
     * @return the sample standard deviation of the data values
     */
    double stddev() const {
        return sqrt(var());
    }

    /**
     * Returns the number of data values.
     * @return the number of data values
     */
    int count() const {
        return n;
    }

    /**
     * Returns a string representation of this accumulator.
     * @return a string representation of this accumulator
     */
    friend ostream &operator<<(ostream &stream, Accumulator &acc);

private:
    int n = 0;            // number of data values
    double sumval = 0.0;  // sample variance * (n-1)
    double mu = 0.0;      // sample variance * (n-1)
};

ostream &operator<<(ostream &stream, Accumulator &acc) {
    stream << "n=" << acc.n << ", mean=" << acc.mean() << ", stddev=" << acc.stddev();
}

#endif //CH1_ACCUMULATOR_H
