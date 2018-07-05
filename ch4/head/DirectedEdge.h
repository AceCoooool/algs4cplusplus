#ifndef CH4_DIRECTEDEDGE_H
#define CH4_DIRECTEDEDGE_H

#include <stdexcept>
#include <ostream>
#include <iomanip>

using std::runtime_error;
using std::ostream;
using std::fixed;
using std::setprecision;

/**
 *  The {@code DirectedEdge} class represents a weighted edge in an
 *  {@link EdgeWeightedDigraph}. Each edge consists of two integers
 *  (naming the two vertices) and a real-value weight. The data type
 *  provides methods for accessing the two endpoints of the directed edge and
 *  the weight.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DirectedEdge {
public:
    /**
     * Initializes a directed edge from vertex {@code v} to vertex {@code w} with
     * the given {@code weight}.
     * @param v the tail vertex
     * @param w the head vertex
     * @param weight the weight of the directed edge
     * @throws IllegalArgumentException if either {@code v} or {@code w}
     *    is a negative integer
     * @throws IllegalArgumentException if {@code weight} is {@code NaN}
     */
    DirectedEdge(int v, int w, double weight) : v(v), w(w), weight(weight) {
        if (v < 0) throw runtime_error("Vertex names must be nonnegative integers");
        if (w < 0) throw runtime_error("Vertex names must be nonnegative integers");
    }

    // default init, as a "not exist" edge
    DirectedEdge() : v(-1), w(-1) {}

    /**
     * Returns the tail vertex of the directed edge.
     * @return the tail vertex of the directed edge
     */
    int from() const {
        return v;
    }

    /**
     * Returns the head vertex of the directed edge.
     * @return the head vertex of the directed edge
     */
    int to() const {
        return w;
    }

    /**
     * Returns the weight of the directed edge.
     * @return the weight of the directed edge
     */
    double weight_() const {
        return weight;
    }

    friend ostream &operator<<(ostream &stream, const DirectedEdge &e) {
        stream << e.v << "->" << e.w << " " << fixed << setprecision(2) << e.weight;
        return stream;
    }

private:
    int v, w;
    double weight;
};


#endif //CH4_DIRECTEDEDGE_H
