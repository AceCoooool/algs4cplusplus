#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

class Vector {
public:
    /**
     * Initializes a d-dimensional zero vector.
     *
     * @param d the dimension of the vector
     */
    Vector(int d) : d(d) {
        data.resize(d);
    }

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
    int dimension() { return d; }

    /**
     * Returns the do product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the dot product of this vector and that vector
     * @throws IllegalArgumentException if the dimensions of the two vectors are not equal
     */

    double dot(Vector &that) {
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
    double distanceTo(Vector that) {
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
    Vector plus(Vector &that) {
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
    Vector minus(Vector &that) {
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
    double cartesian(int i) {
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
    string toString() {
        ostringstream out;
        for (int i = 0; i < d; ++i)
            out << data[i] << " ";
        return out.str();
    }

private:
    int d;                // dimension of the vector
    vector<double> data;  // array of vector's components
};


int main() {
    vector<double> xdata{1.0, 2.0, 3.0, 4.0};
    vector<double> ydata{5.0, 2.0, 4.0, 1.0};
    Vector x(xdata), y(ydata);
    cout << "x = " + x.toString() << endl;
    cout << "y = " + y.toString() << endl;

    Vector z = x.plus(y);
    cout << "z = " << z.toString() << endl;

    z = z.scale(10.0);
    cout << "10z = " << z.toString() << endl;

    cout << "|x| = " << x.magnitude() << endl;
    cout << "<x, y> = " << x.dot(y) << endl;
    cout << "dist(x,y) = " << x.distanceTo(y) << endl;
    cout << "dir(x) = " << x.direction().toString() << endl;
}