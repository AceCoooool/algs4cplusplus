#ifndef CH4_TRANSITIVECLOSURE_H
#define CH4_TRANSITIVECLOSURE_H

#include "../head/Digraph.h"
#include "../head/DirectedDFS.h"

/**
 *  The {@code TransitiveClosure} class represents a data type for
 *  computing the transitive closure of a digraph.
 *  <p>
 *  This implementation runs depth-first search from each vertex.
 *  The constructor takes time proportional to <em>V</em>(<em>V</em> + <em>E</em>)
 *  (in the worst case) and uses space proportional to <em>V</em><sup>2</sup>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  <p>
 *  For large digraphs, you may want to consider a more sophisticated algorithm.
 *  <a href = "http://www.cs.hut.fi/~enu/thesis.html">Nuutila</a> proposes two
 *  algorithm for the problem (based on strong components and an interval representation)
 *  that runs in <em>E</em> + <em>V</em> time on typical digraphs.
 *
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class TransitiveClosure {
public:
    /**
     * Computes the transitive closure of the digraph {@code G}.
     * @param G the digraph
     */
    TransitiveClosure(Digraph &G) : tc(G.getV()) {
        for (int v = 0; v < G.getV(); v++)
            tc[v] = new DirectedDFS(G, v);
    }

    /**
     * Is there a directed path from vertex {@code v} to vertex {@code w} in the digraph?
     * @param  v the source vertex
     * @param  w the target vertex
     * @return {@code true} if there is a directed path from {@code v} to {@code w},
     *         {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     * @throws IllegalArgumentException unless {@code 0 <= w < V}
     */
    bool reachable(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return tc[v]->getmarked(w);
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = tc.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    vector<DirectedDFS *> tc;   // tc[v] = reachable from v
};

#endif //CH4_TRANSITIVECLOSURE_H
