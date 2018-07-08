#ifndef CH1_VECTOR_H
#define CH1_VECTOR_H

#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <cmath>
#include <stdexcept>

using std::vector;
using std::runtime_error;
using std::ostream;
using std::ostringstream;

/**
 *  The {@code Vector} class represents a <em>d</em>-dimensional Euclidean vector.
 *  Vectors are immutable: their values cannot be changed after they are created.
 *  It includes methods for addition, subtraction,
 *  dot product, scalar product, unit vector, Euclidean norm, and the Euclidean
 *  distance between two vectors.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Vector {
public:
    /**
     * Initializes a d-dimensional zero vector.
     *
     * @param d the dimension of the vector
     */
    Vector(int d) : d(d), data(d, 0) {}

    /**
     * Initializes a vector from either an array or a vararg list.
     * The vararg syntax supports a constructor that takes a variable number of
     * arugments such as Vector x = new Vector(1.0, 2.0, 3.0, 4.0).
     *
     * (Note: this version use vector rather than vararg list)
     * @param a  the array or vararg list
     */
    Vector(vector<double> arr) : d(arr.size()), data(arr) {}

    /**
     * Returns the dimension of this vector.
     *
     * @return the dimension of this vector
     */
    int dimension() const { return d; }

    /**
     * Returns the do product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the dot product of this vector and that vector
     * @throws IllegalArgumentException if the dimensions of the two vectors are not equal
     */
    double dot(const Vector &that) {
        if (d != that.d) throw runtime_error("Dimension don't agree");
        double sum = 0.0;
        for (int i = 0; i < d; ++i)
            sum += (data[i] * that.data[i]);
        return sum;
    }

    /**
     * Returns the magnitude of this vector.
     * This is also known as the L2 norm or the Euclidean norm.
     *
     * @return the magnitude of this vector
     */
    double magnitude() {
        return sqrt(dot(*this));
    }

    /**
     * Returns the Euclidean distance between this vector and the specified vector.
     *
     * @param  that the other vector
     * @return the Euclidean distance between this vector and that vector
     * @throws IllegalArgumentException if the dimensions of the two vectors are not equal
     */
    double distanceTo(const Vector &that) {
        if (d != that.d) throw runtime_error("Dimensions don't agree");
        return minus(that).magnitude();
    }

    /**
     * Returns the sum of this vector and the specified vector.
     *
     * @param  that the vector to add to this vector
     * @return the vector whose value is {@code (this + that)}
     * @throws IllegalArgumentException if the dimensions of the two vectors are not equal
     */
    Vector plus(const Vector &that) {
        if (d != that.d) throw runtime_error("Dimensions don't agree");
        Vector c(d);
        for (int i = 0; i < d; i++)
            c.data[i] = data[i] + that.data[i];
        return c;
    }

    /**
     * Returns the difference between this vector and the specified vector.
     *
     * @param  that the vector to subtract from this vector
     * @return the vector whose value is {@code (this - that)}
     * @throws IllegalArgumentException if the dimensions of the two vectors are not equal
     */
    Vector minus(const Vector &that) {
        if (d != that.d) throw runtime_error("Dimensions don't agree");
        Vector c(d);
        for (int i = 0; i < d; i++)
            c.data[i] = data[i] - that.data[i];
        return c;
    }

    /**
     * Returns the ith cartesian coordinate.
     *
     * @param  i the coordinate index
     * @return the ith cartesian coordinate
     */
    double cartesian(int i) const {
        return data[i];
    }

    /**
     * Returns the scalar-vector product of this vector and the specified scalar
     *
     * @param  alpha the scalar
     * @return the vector whose value is {@code (alpha * this)}
     */
    Vector scale(double alpha) {
        Vector c(d);
        for (int i = 0; i < d; i++)
            c.data[i] = alpha * data[i];
        return c;
    }

    /**
     * Returns a unit vector in the direction of this vector.
     *
     * @return a unit vector in the direction of this vector
     * @throws ArithmeticException if this vector is the zero vector
     */
    Vector direction() {
        if (magnitude() == 0.0) throw runtime_error("Zero-vector has no direction");
        return scale(1.0 / magnitude());
    }

    /**
     * Returns a string representation of this vector.
     *
     * @return a string representation of this vector, which consists of the
     *         the vector entries, separates by single spaces
     */
    friend ostream &operator<<(ostream &stream, const Vector &v);

private:
    int d;                // dimension of the vector
    vector<double> data;  // array of vector's components
};

ostream &operator<<(ostream &stream, const Vector &v) {
    ostringstream out;
    for (int i = 0; i < v.d; ++i)
        out << v.data[i] << " ";
    stream << out.str();
    return stream;
}

#endif //CH1_VECTOR_H
