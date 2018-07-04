#ifndef CH4_TOPOLOGICALX_H
#define CH4_TOPOLOGICALX_H

#include "../head/Digraph.h"
#include <queue>

using std::queue;

/**
 *  The {@code TopologicalX} class represents a data type for
 *  determining a topological order of a directed acyclic graph (DAG).
 *  Recall, a digraph has a topological order if and only if it is a DAG.
 *  The <em>hasOrder</em> operation determines whether the digraph has
 *  a topological order, and if so, the <em>order</em> operation
 *  returns one.
 *  <p>
 *  This implementation uses a nonrecursive, queue-based algorithm.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>hasOrder</em> and <em>rank</em> operations takes constant time;
 *  the <em>order</em> operation takes time proportional to <em>V</em>.
 *  <p>
 *  See {@link DirectedCycle}, {@link DirectedCycleX}, and
 *  {@link EdgeWeightedDirectedCycle} to compute a
 *  directed cycle if the digraph is not a DAG.
 *  See {@link Topological} for a recursive version that uses depth-first search.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class TopologicalX {
public:
    /**
     * Determines whether the digraph {@code G} has a topological order and, if so,
     * finds such a topological order.
     * @param G the digraph
     */
    TopologicalX(Digraph &G) : ranks(G.getV()) {

        // indegrees of remaining vertices
        vector<int> indegree(G.getV());
        for (int v = 0; v < G.getV(); v++) {
            indegree[v] = G.getindegree(v);
        }

        // initialize
        int count = 0;

        // initialize queue to contain all vertices with indegree = 0
        queue<int> queue1;
        for (int v = 0; v < G.getV(); v++)
            if (indegree[v] == 0) queue1.push(v);

        while (!queue1.empty()) {
            int v = queue1.front();
            queue1.pop();
            order.push(v);
            ranks[v] = count++;
            for (int w : G.getadj(v)) {
                indegree[w]--;
                if (indegree[w] == 0) {
                    queue1.push(w);
                }
            }
        }

        // there is a directed cycle in subgraph of vertices with indegree >= 1.
        if (count != G.getV()) {
            while (!order.empty())
                order.pop();
        }

    }

    /**
     * Returns a topological order if the digraph has a topologial order,
     * and {@code null} otherwise.
     * @return a topological order of the vertices (as an interable) if the
     *    digraph has a topological order (or equivalently, if the digraph is a DAG),
     *    and {@code null} otherwise
     */
    queue<int> getorder() {
        return order;
    }

    /**
     * Does the digraph have a topological order?
     * @return {@code true} if the digraph has a topological order (or equivalently,
     *    if the digraph is a DAG), and {@code false} otherwise
     */
    bool hasOrder() {
        return !order.empty();
    }

    /**
     * The the rank of vertex {@code v} in the topological order;
     * -1 if the digraph is not a DAG
     *
     * @param v vertex
     * @return the position of vertex {@code v} in a topological order
     *    of the digraph; -1 if the digraph is not a DAG
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int rank(int v) {
        validateVertex(v);
        if (hasOrder()) return ranks[v];
        else return -1;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = ranks.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    queue<int> order;    // vertices in topological order
    vector<int> ranks;   // ranks[v] = order where vertex v appers in order

};

#endif //CH4_TOPOLOGICALX_H
