#ifndef CH1_INTERVAL1D_H
#define CH1_INTERVAL1D_H

#include <stdexcept>
#include <cmath>
#include <ostream>

using std::runtime_error;
using std::ostream;
using std::isinf;
using std::isnan;

/**
 *  The {@code Interval1D} class represents a one-dimensional interval.
 *  The interval is <em>closed</em>—it contains both endpoints.
 *  Intervals are immutable: their values cannot be changed after they are created.
 *  The class {@code Interval1D} includes methods for checking whether
 *  an interval contains a point and determining whether two intervals intersect.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Interval1D {
public:
    /**
     * Initializes a closed interval [min, max].
     *
     * @param  min the smaller endpoint
     * @param  max the larger endpoint
     * @throws IllegalArgumentException if the min endpoint is greater than the max endpoint
     * @throws IllegalArgumentException if either {@code min} or {@code max}
     *         is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY} or
     *         {@code Double.NEGATIVE_INFINITY}
     */
    Interval1D(double min_, double max_) : minval(min_), maxval(max_) {
        if (isinf(minval) || isinf(maxval))
            throw runtime_error("Endpoints must be finite");
        if (isnan(minval) || isnan(maxval))
            throw runtime_error("Endpoints cannot be NaN");

        if (minval > maxval)
            throw runtime_error("Illegal interval");
    }

    /**
     * Returns the min endpoint of this interval.
     *
     * @return the min endpoint of this interval
     */
    double getmin() {
        return minval;
    }

    /**
     * Returns the max endpoint of this interval.
     *
     * @return the max endpoint of this interval
     */
    double getmax() {
        return maxval;
    }

    /**
     * Returns true if this interval intersects the specified interval.
     *
     * @param  that the other interval
     * @return {@code true} if this interval intersects the argument interval;
     *         {@code false} otherwise
     */
    bool intersects(Interval1D &that) {
        if (maxval < that.minval) return false;
        if (that.maxval < minval) return false;
        return true;
    }

    /**
     * Returns true if this interval contains the specified value.
     *
     * @param x the value
     * @return {@code true} if this interval contains the value {@code x};
     *         {@code false} otherwise
     */
    bool contains(double x) {
        return (minval <= x) && (x <= maxval);
    }

    /**
     * Returns the length of this interval.
     *
     * @return the length of this interval (max - min)
     */
    double length() {
        return maxval - minval;
    }

    friend ostream &operator<<(ostream &stream, const Interval1D &item);

    friend bool operator==(const Interval1D &a1, const Interval1D &a2);

    // ascending order of min endpoint, breaking ties by max endpoint
    static bool MinEndpointComparator(Interval1D a, Interval1D b);

    // ascending order of max endpoint, breaking ties by min endpoint
    static bool MaxEndpointComparator(Interval1D a, Interval1D b);

    // ascending order of length
    static bool LengthComparator(Interval1D a, Interval1D b);

private:
    double minval, maxval;
};

ostream &operator<<(ostream &stream, const Interval1D &item) {
    stream << "[" << item.minval << ", " << item.maxval << "]";
}

bool operator==(const Interval1D &a1, const Interval1D &a2) {
    return (a1.minval == a2.minval) && (a1.maxval == a2.maxval);
}

// ascending order of min endpoint, breaking ties by max endpoint
bool Interval1D::MinEndpointComparator(Interval1D a, Interval1D b) {
    if (a.minval < b.minval) return true;
    else if (a.minval > b.minval) return false;
    else if (a.maxval < b.maxval) return true;
    else if (a.maxval > b.maxval) return false;
    else return false;
};

// ascending order of max endpoint, breaking ties by min endpoint
bool Interval1D::MaxEndpointComparator(Interval1D a, Interval1D b) {
    if (a.maxval < b.maxval) return true;
    else if (a.maxval > b.maxval) return false;
    else if (a.minval < b.minval) return true;
    else if (a.minval > b.minval) return false;
    else return false;
}

// ascending order of length
bool Interval1D::LengthComparator(Interval1D a, Interval1D b) {
    double al = a.length(), bl = b.length();
    if (al < bl) return true;
    else return false;
}

#endif //CH1_INTERVAL1D_H
