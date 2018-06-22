#ifndef CH1_RECTHV_H
#define CH1_RECTHV_H

#include <ostream>
#include "../head/Point2D.h"

/**
 *  The {@code RectHV} class is an immutable data type to encapsulate a
 *  two-dimensional axis-aligned rectagle with real-value coordinates.
 *  The rectangle is <em>closed</em>—it includes the points on the boundary.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class RectHV {
public:
    /**
     * Initializes a new rectangle [<em>xmin</em>, <em>xmax</em>]
     * x [<em>ymin</em>, <em>ymax</em>].
     *
     * @param  xmin the <em>x</em>-coordinate of the lower-left endpoint
     * @param  xmax the <em>x</em>-coordinate of the upper-right endpoint
     * @param  ymin the <em>y</em>-coordinate of the lower-left endpoint
     * @param  ymax the <em>y</em>-coordinate of the upper-right endpoint
     * @throws IllegalArgumentException if any of {@code xmin},
     *         {@code xmax}, {@code ymin}, or {@code ymax}
     *         is {@code Double.NaN}.
     * @throws IllegalArgumentException if {@code xmax < xmin} or {@code ymax < ymin}.
     */
    RectHV(double xmin_, double ymin_, double xmax_, double ymax_) : xmin(xmin_), ymin(ymin_), xmax(xmax_),
                                                                     ymax(ymax_) {}

    /**
     * Returns the minimum <em>x</em>-coordinate of any point in this rectangle.
     *
     * @return the minimum <em>x</em>-coordinate of any point in this rectangle
     */
    double getxmin() {
        return xmin;
    }

    /**
     * Returns the maximum <em>x</em>-coordinate of any point in this rectangle.
     *
     * @return the maximum <em>x</em>-coordinate of any point in this rectangle
     */
    double getxmax() {
        return xmax;
    }

    /**
     * Returns the minimum <em>y</em>-coordinate of any point in this rectangle.
     *
     * @return the minimum <em>y</em>-coordinate of any point in this rectangle
     */
    double getymin() {
        return ymin;
    }

    /**
     * Returns the maximum <em>y</em>-coordinate of any point in this rectangle.
     *
     * @return the maximum <em>y</em>-coordinate of any point in this rectangle
     */
    double getymax() {
        return ymax;
    }

    /**
     * Returns the width of this rectangle.
     *
     * @return the width of this rectangle {@code xmax - xmin}
     */
    double width() {
        return xmax - xmin;
    }


    /**
     * Returns the height of this rectangle.
     *
     * @return the height of this rectangle {@code ymax - ymin}
     */
    double height() {
        return ymax - ymin;
    }

    /**
     * Returns true if the two rectangles intersect. This includes
     * <em>improper intersections</em> (at points on the boundary
     * of each rectangle) and <em>nested intersctions</em>
     * (when one rectangle is contained inside the other)
     *
     * @param  that the other rectangle
     * @return {@code true} if this rectangle intersect the argument
               rectangle at one or more points
     */
    bool intersects(RectHV &that) {
        return xmax >= that.xmin && ymax >= that.ymin
               && that.xmax >= xmin && that.ymax >= ymin;
    }

    /**
     * Returns true if this rectangle contain the point.
     * @param  p the point
     * @return {@code true} if this rectangle contain the point {@code p},
               possibly at the boundary; {@code false} otherwise
     */
    bool contains(Point2D &p) {
        return (p.getx() >= xmin) && (p.getx() <= xmax)
               && (p.gety() >= ymin) && (p.gety() <= ymax);
    }

    /**
     * Returns the square of the Euclidean distance between this rectangle and the point {@code p}.
     *
     * @param  p the point
     * @return the square of the Euclidean distance between the point {@code p} and
     *         the closest point on this rectangle; 0 if the point is contained
     *         in this rectangle
     */
    double distanceSquaredTo(Point2D &p) {
        double dx = 0.0, dy = 0.0;
        if (p.getx() < xmin) dx = p.getx() - xmin;
        else if (p.getx() > xmax) dx = p.getx() - xmax;
        if (p.gety() < ymin) dy = p.gety() - ymin;
        else if (p.gety() > ymax) dy = p.gety() - ymax;
        return dx * dx + dy * dy;
    }

    /**
     * Returns the Euclidean distance between this rectangle and the point {@code p}.
     *
     * @param  p the point
     * @return the Euclidean distance between the point {@code p} and the closest point
               on this rectangle; 0 if the point is contained in this rectangle
     */
    double distanceTo(Point2D &p) {
        return sqrt(distanceSquaredTo(p));
    }

    /**
     * Compares this rectangle to the specified rectangle.
     *
     * @param  other the other rectangle
     * @return {@code true} if this rectangle equals {@code other};
     *         {@code false} otherwise
     */
    friend bool operator==(const RectHV &r1, const RectHV &r2);

    /**
     * Returns a string representation of this rectangle.
     *
     * @return a string representation of this rectangle, using the format
     *         {@code [xmin, xmax] x [ymin, ymax]}
     */
    friend ostream &operator<<(ostream &stream, const RectHV &r);

private:
    double xmin, ymin;  // minimum x- and y-coordinates
    double xmax, ymax;  // maximum x- and y-coordinates
};

bool operator==(const RectHV &r1, const RectHV &r2) {
    return r1.xmin == r2.xmin && r1.ymin == r2.ymin && r1.xmax == r2.xmax && r1.ymax == r2.ymax;
}

ostream &operator<<(ostream &stream, const RectHV &r) {
    stream << "[" << r.xmin << ", " << r.xmax << "] x [" << r.ymin << ", " << r.ymax << "]";
    return stream;
}

#endif //CH1_RECTHV_H
