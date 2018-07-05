#ifndef CH4_DIJKSTRAUNDIRECTEDSP_H
#define CH4_DIJKSTRAUNDIRECTEDSP_H

#include "../head/EdgeWeightedGraph.h"
#include "IndexMinPQ.h"
#include <numeric>

using std::numeric_limits;

/**
 *  The {@code DijkstraUndirectedSP} class represents a data type for solving
 *  the single-source shortest paths problem in edge-weighted graphs
 *  where the edge weights are nonnegative.
 *  <p>
 *  This implementation uses Dijkstra's algorithm with a binary heap.
 *  The constructor takes time proportional to <em>E</em> log <em>V</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Each call to {@code distTo(int)} and {@code hasPathTo(int)} takes constant time;
 *  each call to {@code pathTo(int)} takes time proportional to the number of
 *  edges in the shortest path returned.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  See {@link DijkstraSP} for a version on edge-weighted digraphs.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *  @author Nate Liu
 */
class DijkstraUndirectedSP {
public:
    /**
     * Computes a shortest-paths tree from the source vertex {@code s} to every
     * other vertex in the edge-weighted graph {@code G}.
     *
     * @param  G the edge-weighted digraph
     * @param  s the source vertex
     * @throws IllegalArgumentException if an edge weight is negative
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    DijkstraUndirectedSP(EdgeWeightedGraph &G, int s) : distTo(G.V_(), numeric_limits<double>::max()), edgeTo(G.V_()),
                                                        pq(G.V_()) {
        for (Edge e : G.edges()) {
            if (e.weight_() < 0)
                throw runtime_error("edge has negative weight");
        }

        validateVertex(s);

        distTo[s] = 0.0;

        // relax vertices in order of distance from s
        pq.insert(s, distTo[s]);
        while (!pq.isEmpty()) {
            int v = pq.delMin();
            for (Edge e : G.adj_(v))
                relax(e, v);
        }
    }

    /**
     * Returns the length of a shortest path between the source vertex {@code s} and
     * vertex {@code v}.
     *
     * @param  v the destination vertex
     * @return the length of a shortest path between the source vertex {@code s} and
     *         the vertex {@code v}; {@code Double.POSITIVE_INFINITY} if no such path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    double distTo_(int v) {
        validateVertex(v);
        return distTo[v];
    }

    /**
     * Returns true if there is a path between the source vertex {@code s} and
     * vertex {@code v}.
     *
     * @param  v the destination vertex
     * @return {@code true} if there is a path between the source vertex
     *         {@code s} to vertex {@code v}; {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool hasPathTo(int v) {
        validateVertex(v);
        return distTo[v] < numeric_limits<double>::max();
    }

    /**
     * Returns a shortest path between the source vertex {@code s} and vertex {@code v}.
     *
     * @param  v the destination vertex
     * @return a shortest path between the source vertex {@code s} and vertex {@code v};
     *         {@code null} if no such path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<Edge> pathTo(int v) {
        validateVertex(v);
        if (!hasPathTo(v)) throw runtime_error("no path to this vertex");
        forward_list<Edge> path;
        int x = v;
        for (Edge e = edgeTo[v]; e.either() != -1; e = edgeTo[x]) {
            path.push_front(e);
            x = e.other(x);
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

    // relax edge e and update pq if changed
    void relax(Edge e, int v) {
        int w = e.other(v);
        if (distTo[w] > distTo[v] + e.weight_()) {
            distTo[w] = distTo[v] + e.weight_();
            edgeTo[w] = e;
            if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
            else pq.insert(w, distTo[w]);
        }
    }

private:
    vector<double> distTo;  // distTo[v] = distance  of shortest s->v path
    vector<Edge> edgeTo;    // edgeTo[v] = last edge on shortest s->v path
    IndexMinPQ<double> pq;  // priority queue of vertices

};

#endif //CH4_DIJKSTRAUNDIRECTEDSP_H
