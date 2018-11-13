#ifndef CH1_INTERVAL2D_H
#define CH1_INTERVAL2D_H

#include "Interval1D.h"
#include "Point2D.h"

/**
 *  The {@code Interval2D} class represents a closed two-dimensional interval,
 *  which represents all points (x, y) with both {@code xmin <= x <= xmax} and
 *  {@code ymin <= y <= ymax}.
 *  Two-dimensional intervals are immutable: their values cannot be changed
 *  after they are created.
 *  The class {@code Interval2D} includes methods for checking whether
 *  a two-dimensional interval contains a point and determining whether
 *  two two-dimensional intervals intersect.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Interval2D {
private:
    Interval1D x;
    Interval1D y;

public:
    /**
     * Initializes a two-dimensional interval.
     * @param x the one-dimensional interval of x-coordinates
     * @param y the one-dimensional interval of y-coordinates
     */
    Interval2D(Interval1D x_, Interval1D y_) : x(x_), y(y_) {}

    /**
     * Does this two-dimensional interval intersect that two-dimensional interval?
     * @param that the other two-dimensional interval
     * @return true if this two-dimensional interval intersects
     *    that two-dimensional interval; false otherwise
     */
    bool intersects(const Interval2D &that) const {
        if (!x.intersects(that.x)) return false;
        if (!y.intersects(that.y)) return false;
        return true;
    }

    /**
     * Does this two-dimensional interval contain the point p?
     * @param p the two-dimensional point
     * @return true if this two-dimensional interval contains the point p; false otherwise
     */
    bool contains(const Point2D &p) const {
        return x.contains(p.x_()) && y.contains(p.y_());
    }

    /**
     * Returns the area of this two-dimensional interval.
     * @return the area of this two-dimensional interval
     */
    double area() const {
        return x.length() * y.length();
    }

    /**
     * Returns a string representation of this two-dimensional interval.
     * @return a string representation of this two-dimensional interval
     *    in the form [xmin, xmax] x [ymin, ymax]
     */
    friend ostream &operator<<(ostream &stream, const Interval2D &d2);

    /**
     * Does this interval equal the other interval?
     * @param other the other interval
     * @return true if this interval equals the other interval; false otherwise
     */
    friend bool operator==(const Interval2D &d1, const Interval2D &d2);

};

ostream &operator<<(ostream &stream, const Interval2D &d2) {
    stream << d2.x << " x " << d2.y;
    return stream;
}

bool operator==(const Interval2D &d1, const Interval2D &d2) {
    return d1.x == d2.x && d1.y == d2.y;
}

#endif //CH1_INTERVAL2D_H
