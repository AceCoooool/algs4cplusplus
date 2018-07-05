#ifndef CH4_EDGEWEIGHTEDDIRECTEDCYCLE_H
#define CH4_EDGEWEIGHTEDDIRECTEDCYCLE_H

#include "../head/EdgeWeightedDigraph.h"

/**
 *  The {@code EdgeWeightedDirectedCycle} class represents a data type for
 *  determining whether an edge-weighted digraph has a directed cycle.
 *  The <em>hasCycle</em> operation determines whether the edge-weighted
 *  digraph has a directed cycle and, if so, the <em>cycle</em> operation
 *  returns one.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>hasCycle</em> operation takes constant time;
 *  the <em>cycle</em> operation takes time proportional
 *  to the length of the cycle.
 *  <p>
 *  See {@link Topological} to compute a topological order if the edge-weighted
 *  digraph is acyclic.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class EdgeWeightedDirectedCycle {
public:
    /**
     * Determines whether the edge-weighted digraph {@code G} has a directed cycle and,
     * if so, finds such a cycle.
     * @param G the edge-weighted digraph
     */
    EdgeWeightedDirectedCycle(EdgeWeightedDigraph &G) : marked(G.V_(), false),
                                                        onStack(G.V_(), false), edgeTo(G.V_()) {
        for (int v = 0; v < G.V_(); v++)
            if (!marked[v]) dfs(G, v);
    }

    /**
     * Does the edge-weighted digraph have a directed cycle?
     * @return {@code true} if the edge-weighted digraph has a directed cycle,
     * {@code false} otherwise
     */
    bool hasCycle() {
        return !cycle.empty();
    }

    /**
     * Returns a directed cycle if the edge-weighted digraph has a directed cycle,
     * and {@code null} otherwise.
     * @return a directed cycle (as an iterable) if the edge-weighted digraph
     *    has a directed cycle, and {@code null} otherwise
     */
    forward_list<DirectedEdge> cycle_() {
        return cycle;
    }

private:
    // check that algorithm computes either the topological order or finds a directed cycle
    void dfs(EdgeWeightedDigraph G, int v) {
        onStack[v] = true;
        marked[v] = true;
        for (DirectedEdge e : G.adj_(v)) {
            int w = e.to();

            // short circuit if directed cycle found
            if (!cycle.empty()) return;
            else if (!marked[w]) {  // found new vertex, so recur
                edgeTo[w] = e;
                dfs(G, w);
            } else if (onStack[w]) {    // trace back directed cycle
                DirectedEdge f = e;
                while (f.from() != w) {
                    cycle.push_front(f);
                    f = edgeTo[f.from()];
                }
                cycle.push_front(f);

                return;
            }
        }

        onStack[v] = false;
    }

private:
    vector<bool> marked;           // marked[v] = has vertex v been marked?
    vector<DirectedEdge> edgeTo;   // edgeTo[v] = previous edge on path to v
    vector<bool> onStack;          // onStack[v] = is vertex on the stack?
    forward_list<DirectedEdge> cycle;  // directed cycle (or null if no such cycle)
};

#endif //CH4_EDGEWEIGHTEDDIRECTEDCYCLE_H
