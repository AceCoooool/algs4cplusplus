
#ifndef CH3_SPARSEVECTOR_H
#define CH3_SPARSEVECTOR_H

#include "../head/ST.h"
#include <vector>
#include <cmath>
#include <ostream>
#include <sstream>

using std::vector;
using std::ostream;
using std::stringstream;

/**
 *  The {@code SparseVector} class represents a <em>d</em>-dimensional mathematical vector.
 *  Vectors are mutable: their values can be changed after they are created.
 *  It includes methods for addition, subtraction,
 *  dot product, scalar product, unit vector, and Euclidean norm.
 *  <p>
 *  The implementation is a symbol table of indices and values for which the vector
 *  coordinates are nonzero. This makes it efficient when most of the vector coordindates
  * are zero.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/35applications">Section 3.5</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  See also {@link Vector} for an immutable (dense) vector data type.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class SparseVector {
public:
    /**
     * Initializes a d-dimensional zero vector.
     * @param d the dimension of the vector
     */
    SparseVector(int d) : d(d) {}

    /**
     * Sets the ith coordinate of this vector to the specified value.
     *
     * @param  i the index
     * @param  value the new value
     * @throws IllegalArgumentException unless i is between 0 and d-1
     */
    void put(int i, double value) {
        if (i < 0 || i >= d) throw runtime_error("Illegal index");
        if (value == 0.0) st.delete_op(i);
        else st.put(i, value);
    }

    /**
     * Returns the ith coordinate of this vector.
     *
     * @param  i the index
     * @return the value of the ith coordinate of this vector
     * @throws IllegalArgumentException unless i is between 0 and d-1
     */
    double get(int i) {
        if (i < 0 || i >= d) throw runtime_error("Illegal index");
        if (st.contains(i)) return st.get(i);  //TODO: maybe a bug
        else return 0.0;
    }

    /**
     * Returns the number of nonzero entries in this vector.
     *
     * @return the number of nonzero entries in this vector
     */
    int nnz() {
        return st.size();
    }

    /**
     * Returns the dimension of this vector.
     *
     * @return the dimension of this vector
     */
    int dimension() {
        return d;
    }

    /**
     * Returns the inner product of this vector with the specified vector.
     *
     * @param  that the other vector
     * @return the dot product between this vector and that vector
     * @throws IllegalArgumentException if the lengths of the two vectors are not equal
     */
    double dot(SparseVector &that) {
        if (d != that.d) throw runtime_error("Vector lengths disagree");
        double sum = 0.0;

        // iterate over the vector with the fewest nonzeros
        if (st.size() <= that.st.size()) {
            for (auto p : st) {
                auto i = p.first;
                if (that.st.contains(i)) sum += get(i) * that.get(i);
            }
        } else {
            for (auto p : that.st) {
                int i = p.first;
                if (st.contains(i)) sum += get(i) * that.get(i);
            }

        }
        return sum;
    }

    /**
     * Returns the inner product of this vector with the specified array.
     *
     * @param  that the array
     * @return the dot product between this vector and that array
     * @throws IllegalArgumentException if the dimensions of the vector and the array are not equal
     */
    double dot(vector<double> &that) {
        double sum = 0.0;
        for (auto p : st) {
            auto i = p.first;
            sum += that[i] * get(i);
        }
        return sum;
    }

    /**
     * Returns the magnitude of this vector.
     * This is also known as the L2 norm or the Euclidean norm.
     *
     * @return the magnitude of this vector
     */
    double magnitude() {
        return std::sqrt(this->dot(*this));
    }

    /**
     * Returns the scalar-vector product of this vector with the specified scalar.
     *
     * @param  alpha the scalar
     * @return the scalar-vector product of this vector with the specified scalar
     */
    SparseVector scale(double alpha) {
        SparseVector c(d);
        for (auto p : st) {
            auto i = p.first;
            c.put(i, alpha * get(i));
        }
        return c;
    }

    /**
     * Returns the sum of this vector and the specified vector.
     *
     * @param  that the vector to add to this vector
     * @return the sum of this vector and that vector
     * @throws IllegalArgumentException if the dimensions of the two vectors are not equal
     */
    SparseVector plus(SparseVector &that) {
        if (d != that.d) throw runtime_error("Vector lengths disagree");
        SparseVector c(d);
        for (auto p : st) {     // c = this
            auto i = p.first;
            c.put(i, get(i));
        }
        for (auto p : that.st) {  // c = c + that
            auto i = p.first;
            c.put(i, that.get(i) + c.get(i));
        }
        return c;
    }

    // TODO: change to const SparseVector---due to map issue
    friend ostream &operator<<(ostream &stream, SparseVector &sparse);

private:
    int d;               // dimension
    ST<int, double> st;  // the vector, represented by index-value pairs
};

ostream &operator<<(ostream &stream, SparseVector &sparse) {
    stringstream ss;
    for (auto p: sparse.st) {
        auto i = p.first;
        ss << "(" << i << ", " << sparse.st.get(i) << ")";
    }
    stream << ss.str();
    return stream;
}

#endif //CH3_SPARSEVECTOR_H
