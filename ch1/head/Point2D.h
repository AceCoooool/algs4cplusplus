#ifndef CH1_POINT2D_H
#define CH1_POINT2D_H

// TODO: un-finish: don't know how to draw
#include <cmath>
#include <ostream>
#include <stdexcept>

using std::runtime_error;
using std::isnan;
using std::isinf;
using std::ostream;


/**
 *  The {@code Point} class is an immutable data type to encapsulate a
 *  two-dimensional point with real-value coordinates.
 *  <p>
 *  Note: in order to deal with the difference behavior of double and
 *  Double with respect to -0.0 and +0.0, the Point2D constructor converts
 *  any coordinates that are -0.0 to +0.0.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Point2D {
private:
    double x;   // x coordinate
    double y;   // y coordinate

public:
    /**
     * Initializes a new point (x, y).
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @throws IllegalArgumentException if either {@code x} or {@code y}
     *    is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY} or
     *    {@code Double.NEGATIVE_INFINITY}
     */
    Point2D(double x_, double y_) {
        if (isinf(x_) || isinf(y_))
            throw runtime_error("Coordinates must be finite");
        if (isnan(x_) || isnan(y_))
            throw runtime_error("Coordinates cannot be NaN");
        x = x_;
        y = y_;
    }

    /**
     * Returns the x-coordinate.
     * @return the x-coordinate
     */
    double x_() const {
        return x;
    }

    /**
     * Returns the y-coordinate.
     * @return the y-coordinate
     */
    double y_() const {
        return y;
    }

    /**
     * Returns the polar radius of this point.
     * @return the polar radius of this point in polar coordiantes: sqrt(x*x + y*y)
     */
    double r() const {
        return sqrt(x * x + y * y);
    }

    /**
     * Returns the angle of this point in polar coordinates.
     * @return the angle (in radians) of this point in polar coordiantes (between –&pi; and &pi;)
     */
    double theta() const {
        return atan2(y, x);
    }

    /**
     * Returns the angle between this point and that point.
     * @return the angle in radians (between –&pi; and &pi;) between this point and that point (0 if equal)
     */
    double angleTo(const Point2D &that) {
        double dx = that.x - x;
        double dy = that.y - y;
        return atan2(dy, dx);
    }

    /**
     * Returns the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the Euclidean distance between this point and that point
     */
    double distanceTo(const Point2D &that) {
        double dx = x - that.x;
        double dy = y - that.y;
        return sqrt(dx * dx + dy * dy);
    }

    /**
     * Returns the square of the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the square of the Euclidean distance between this point and that point
     */
    double distanceSquaredTo(const Point2D &that) {
        double dx = x - that.x;
        double dy = y - that.y;
        return dx * dx + dy * dy;
    }

    /**
     * Compares two points by y-coordinate, breaking ties by x-coordinate.
     * Formally, the invoking point (x0, y0) is less than the argument point (x1, y1)
     * if and only if either {@code y0 < y1} or if {@code y0 == y1} and {@code x0 < x1}.
     *
     * @param  that the other point
     * @return the value {@code 0} if this string is equal to the argument
     *         string (precisely when {@code equals()} returns {@code true});
     *         a negative integer if this point is less than the argument
     *         point; and a positive integer if this point is greater than the
     *         argument point
     */
    friend bool operator<(const Point2D &p1, const Point2D &p2);

    /**
     * Return a string representation of this point.
     * @return a string representation of this point in the format (x, y)
     */
    friend ostream &operator<<(ostream &stream, const Point2D &p);

    /**
     * Compares this point to the specified point.
     *
     * @param  other the other point
     * @return {@code true} if this point equals {@code other};
     *         {@code false} otherwise
     */
    friend bool operator==(const Point2D &p1, const Point2D &p2);

    /**
     * Returns true if a→b→c is a counterclockwise turn.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return { -1, 0, +1 } if a→b→c is a { clockwise, collinear; counterclocwise } turn.
     */
    static int ccw(const Point2D &a, const Point2D &b, const Point2D &c) {
        double area2 = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        if (area2 < 0) return -1;
        else if (area2 > 0) return +1;
        else return 0;
    }

    /**
     * Returns twice the signed area of the triangle a-b-c.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return twice the signed area of the triangle a-b-c
     */
    static double area2(const Point2D &a, const Point2D &b, const Point2D &c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    // compare points according to their x-coordinate
    static bool XOrder(const Point2D &p1, const Point2D &p2) {
        return p1.x < p2.x;
    }

    // compare points according to their y-coordinate
    static bool YOrder(const Point2D &p1, const Point2D &p2) {
        return p1.y < p2.y;
    }

    // compare points according to their polar radius
    static bool ROrder(const Point2D &p1, const Point2D &p2) {
        auto delta = (p1.x * p1.x + p1.y * p1.y) - (p2.x * p2.x + p2.y * p2.y);
        return delta < 0;
    }
};

bool operator<(const Point2D &p1, const Point2D &p2) {
    if (p1.y < p2.y) return true;
    if (p1.y > p2.y) return false;
    if (p1.x < p2.x) return true;
    if (p1.x > p2.x) return false;
    return false;
}

ostream &operator<<(ostream &stream, const Point2D &p) {
    stream << "(" << p.x << ", " << p.y << ")";
    return stream;
}

bool operator==(const Point2D &p1, const Point2D &p2) {
    return p1.x == p2.x && p1.y == p2.y;
}


#endif //CH1_POINT2D_H
