#ifndef CH4_ACYCLICSP_H
#define CH4_ACYCLICSP_H

#include "EdgeWeightedDigraph.h"
#include "Topological.h"
#include <numeric>

using std::numeric_limits;

/**
 *  The {@code AcyclicSP} class represents a data type for solving the
 *  single-source shortest paths problem in edge-weighted directed acyclic
 *  graphs (DAGs). The edge weights can be positive, negative, or zero.
 *  <p>
 *  This implementation uses a topological-sort based algorithm.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Each call to {@code distTo(int)} and {@code hasPathTo(int)} takes constant time;
 *  each call to {@code pathTo(int)} takes time proportional to the number of
 *  edges in the shortest path returned.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class AcyclicSP {
public:
    /**
     * Computes a shortest paths tree from {@code s} to every other vertex in
     * the directed acyclic graph {@code G}.
     * @param G the acyclic digraph
     * @param s the source vertex
     * @throws IllegalArgumentException if the digraph is not acyclic
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    AcyclicSP(EdgeWeightedDigraph &G, int s) : distTo(G.V_(), numeric_limits<double>::max()), edgeTo(G.V_()) {
        validateVertex(s);

        distTo[s] = 0.0;

        // visit vertices in topological order
        Topological topological(G);
        if (!topological.hasOrder())
            throw runtime_error("Digraph is not acyclic.");
        for (int v : topological.getorder()) {
            for (DirectedEdge e : G.adj_(v))
                relax(e);
        }
    }

    /**
     * Returns the length of a shortest path from the source vertex {@code s} to vertex {@code v}.
     * @param  v the destination vertex
     * @return the length of a shortest path from the source vertex {@code s} to vertex {@code v};
     *         {@code Double.POSITIVE_INFINITY} if no such path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    double distTo_(int v) {
        validateVertex(v);
        return distTo[v];
    }

    /**
     * Is there a path from the source vertex {@code s} to vertex {@code v}?
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
     * Returns a shortest path from the source vertex {@code s} to vertex {@code v}.
     * @param  v the destination vertex
     * @return a shortest path from the source vertex {@code s} to vertex {@code v}
     *         as an iterable of edges, and {@code null} if no such path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<DirectedEdge> pathTo(int v) {
        validateVertex(v);
        if (!hasPathTo(v)) throw runtime_error("no path to this vertex");
        forward_list<DirectedEdge> path;
        for (DirectedEdge e = edgeTo[v]; e.to()!=-1; e = edgeTo[e.from()]) {
            path.push_front(e);
        }
        return path;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = distTo.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    // relax edge e
    void relax(DirectedEdge &e) {
        int v = e.from(), w = e.to();
        if (distTo[w] > distTo[v] + e.weight_()) {
            distTo[w] = distTo[v] + e.weight_();
            edgeTo[w] = e;
        }
    }

private:
    vector<double> distTo;        // distTo[v] = distance  of shortest s->v path
    vector<DirectedEdge> edgeTo;  // edgeTo[v] = last edge on shortest s->v path
};

#endif //CH4_ACYCLICSP_H
