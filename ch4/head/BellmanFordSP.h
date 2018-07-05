#ifndef CH4_BELLMANFORDSP_H
#define CH4_BELLMANFORDSP_H

#include "../head/EdgeWeightedDigraph.h"
#include "../head/EdgeWeightedDirectedCycle.h"
#include <queue>
#include <numeric>

using std::queue;
using std::numeric_limits;

/**
 *  The {@code BellmanFordSP} class represents a data type for solving the
 *  single-source shortest paths problem in edge-weighted digraphs with
 *  no negative cycles.
 *  The edge weights can be positive, negative, or zero.
 *  This class finds either a shortest path from the source vertex <em>s</em>
 *  to every other vertex or a negative cycle reachable from the source vertex.
 *  <p>
 *  This implementation uses the Bellman-Ford-Moore algorithm.
 *  The constructor takes time proportional to <em>V</em> (<em>V</em> + <em>E</em>)
 *  in the worst case, where <em>V</em> is the number of vertices and <em>E</em>
 *  is the number of edges.
 *  Each call to {@code distTo(int)} and {@code hasPathTo(int)},
 *  {@code hasNegativeCycle} takes constant time;
 *  each call to {@code pathTo(int)} and {@code negativeCycle()}
 *  takes time proportional to length of the path returned.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class BellmanFordSP {
public:
    /**
     * Computes a shortest paths tree from {@code s} to every other vertex in
     * the edge-weighted digraph {@code G}.
     * @param G the acyclic digraph
     * @param s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    BellmanFordSP(EdgeWeightedDigraph &G, int s) : distTo(G.V_(), numeric_limits<double>::max()),
                                                   onQueue(G.V_(), false), edgeTo(G.V_()), cost(0) {
        distTo[s] = 0.0;

        // Bellman-Ford algorithm
        queue1.push(s);
        onQueue[s] = true;
        while (!queue1.empty() && !hasNegativeCycle()) {
            int v = queue1.front();
            queue1.pop();
            onQueue[v] = false;
            relax(G, v);
        }
    }

    /**
     * Is there a negative cycle reachable from the source vertex {@code s}?
     * @return {@code true} if there is a negative cycle reachable from the
     *    source vertex {@code s}, and {@code false} otherwise
     */
    bool hasNegativeCycle() {
        return !cycle.empty();
    }

    /**
     * Returns a negative cycle reachable from the source vertex {@code s}, or {@code null}
     * if there is no such cycle.
     * @return a negative cycle reachable from the soruce vertex {@code s}
     *    as an iterable of edges, and {@code null} if there is no such cycle
     */
    forward_list<DirectedEdge> negativeCycle() {
        return cycle;
    }

    /**
     * Returns the length of a shortest path from the source vertex {@code s} to vertex {@code v}.
     * @param  v the destination vertex
     * @return the length of a shortest path from the source vertex {@code s} to vertex {@code v};
     *         {@code Double.POSITIVE_INFINITY} if no such path
     * @throws UnsupportedOperationException if there is a negative cost cycle reachable
     *         from the source vertex {@code s}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    double distTo_(int v) {
        validateVertex(v);
        if (hasNegativeCycle())
            throw runtime_error("Negative cost cycle exists");
        return distTo[v];
    }

    /**
     * Is there a path from the source {@code s} to vertex {@code v}?
     * @param  v the destination vertex
     * @return {@code true} if there is a path from the source vertex
     *         {@code s} to vertex {@code v}, and {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool hasPathTo(int v) {
        validateVertex(v);
        return distTo[v] < numeric_limits<double>::max();
    }

    /**
     * Returns a shortest path from the source {@code s} to vertex {@code v}.
     * @param  v the destination vertex
     * @return a shortest path from the source {@code s} to vertex {@code v}
     *         as an iterable of edges, and {@code null} if no such path
     * @throws UnsupportedOperationException if there is a negative cost cycle reachable
     *         from the source vertex {@code s}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<DirectedEdge> pathTo(int v) {
        validateVertex(v);
        if (hasNegativeCycle())
            throw runtime_error("Negative cost cycle exists");
        if (!hasPathTo(v)) throw runtime_error("no path to this vertex");
        forward_list<DirectedEdge> path;
        for (DirectedEdge e = edgeTo[v]; e.to() != -1; e = edgeTo[e.from()]) {
            path.push_front(e);
        }
        return path;
    }

private:
    // relax vertex v and put other endpoints on queue if changed
    void relax(EdgeWeightedDigraph &G, int v) {
        for (DirectedEdge e : G.adj_(v)) {
            int w = e.to();
            if (distTo[w] > distTo[v] + e.weight_()) {
                distTo[w] = distTo[v] + e.weight_();
                edgeTo[w] = e;
                if (!onQueue[w]) {
                    queue1.push(w);
                    onQueue[w] = true;
                }
            }
            if (cost++ % G.V_() == 0) {
                findNegativeCycle();
                if (hasNegativeCycle()) return;  // found a negative cycle
            }
        }
    }

    // by finding a cycle in predecessor graph
    void findNegativeCycle() {
        int V = edgeTo.size();
        EdgeWeightedDigraph spt(V);
        for (int v = 0; v < V; v++)
            if (edgeTo[v].to() != -1)
                spt.addEdge(edgeTo[v]);

        EdgeWeightedDirectedCycle finder(spt);
        cycle = finder.cycle_();
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = distTo.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }


private:
    vector<double> distTo;            // distTo[v] = distance  of shortest s->v path
    vector<DirectedEdge> edgeTo;      // edgeTo[v] = last edge on shortest s->v path
    vector<bool> onQueue;             // onQueue[v] = is v currently on the queue?
    queue<int> queue1;                // queue of vertices to relax
    int cost;                         // number of calls to relax()
    forward_list<DirectedEdge> cycle; // negative cycle (or null if no such cycle)
};

#endif //CH4_BELLMANFORDSP_H
