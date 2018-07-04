#ifndef CH4_EDGE_H
#define CH4_EDGE_H

#include <stdexcept>
#include <ostream>
#include <iomanip>

using std::runtime_error;
using std::ostream;
using std::setprecision;
using std::fixed;

/**
 *  The {@code Edge} class represents a weighted edge in an
 *  {@link EdgeWeightedGraph}. Each edge consists of two integers
 *  (naming the two vertices) and a real-value weight. The data type
 *  provides methods for accessing the two endpoints of the edge and
 *  the weight. The natural order for this data type is by
 *  ascending order of weight.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Edge {
public:
    /**
     * Initializes an edge between vertices {@code v} and {@code w} of
     * the given {@code weight}.
     *
     * @param  v one vertex
     * @param  w the other vertex
     * @param  weight the weight of this edge
     * @throws IllegalArgumentException if either {@code v} or {@code w}
     *         is a negative integer
     * @throws IllegalArgumentException if {@code weight} is {@code NaN}
     */
    Edge(int v, int w, double weight) : v(v), w(w), weight(weight) {
        if (v < 0) throw runtime_error("vertex index must be a nonnegative integer");
        if (w < 0) throw runtime_error("vertex index must be a nonnegative integer");
    }

    // default for judge
    Edge() : v(-1), w(-1) {}

    /**
     * Returns the weight of this edge.
     *
     * @return the weight of this edge
     */
    double weight_() {
        return weight;
    }

    /**
     * Returns either endpoint of this edge.
     *
     * @return either endpoint of this edge
     */
    int either() {
        return v;
    }

    /**
     * Returns the endpoint of this edge that is different from the given vertex.
     *
     * @param  vertex one endpoint of this edge
     * @return the other endpoint of this edge
     * @throws IllegalArgumentException if the vertex is not one of the
     *         endpoints of this edge
     */
    int other(int vertex) {
        if (vertex == v) return w;
        else if (vertex == w) return v;
        else throw runtime_error("Illegal endpoint");
    }

    friend bool operator<(const Edge &e1, const Edge &e2) {
        return e1.weight < e2.weight;
    }

    friend bool operator>(const Edge &e1, const Edge &e2) {
        return e1.weight > e2.weight;
    }

    friend ostream &operator<<(ostream &stream, const Edge &e) {
        stream << e.v << "-" << e.w << " " << fixed << setprecision(5) << e.weight;
        return stream;
    }

private:
    int v, w;
    double weight;
};

#endif //CH4_EDGE_H
