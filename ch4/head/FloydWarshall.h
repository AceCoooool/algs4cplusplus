#ifndef CH4_FLOYDWARSHALL_H
#define CH4_FLOYDWARSHALL_H

#include "../head/AdjMatrixEdgeWeightedDigraph.h"
#include "../head/EdgeWeightedDirectedCycle.h"
#include <numeric>

using std::numeric_limits;

/**
 *  The {@code FloydWarshall} class represents a data type for solving the
 *  all-pairs shortest paths problem in edge-weighted digraphs with
 *  no negative cycles.
 *  The edge weights can be positive, negative, or zero.
 *  This class finds either a shortest path between every pair of vertices
 *  or a negative cycle.
 *  <p>
 *  This implementation uses the Floyd-Warshall algorithm.
 *  The constructor takes time proportional to <em>V</em><sup>3</sup> in the
 *  worst case, where <em>V</em> is the number of vertices.
 *  Afterwards, the {@code dist()}, {@code hasPath()}, and {@code hasNegativeCycle()}
 *  methods take constant time; the {@code path()} and {@code negativeCycle()}
 *  method takes time proportional to the number of edges returned.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class FloydWarshall {
public:
    /**
     * Computes a shortest paths tree from each vertex to to every other vertex in
     * the edge-weighted digraph {@code G}. If no such shortest path exists for
     * some pair of vertices, it computes a negative cycle.
     * @param G the edge-weighted digraph
     */
    FloydWarshall(AdjMatrixEdgeWeightedDigraph &G) :
            distTo(G.V_(), vector<double>(G.V_(), numeric_limits<double>::max())),
            edgeTo(G.V_(), vector<DirectedEdge>(G.V_())) {
        int V = G.V_();

        // initialize distances using edge-weighted digraph's
        for (int v = 0; v < G.V_(); v++) {
            for (DirectedEdge e : G.adj_(v)) {
                distTo[e.from()][e.to()] = e.weight_();
                edgeTo[e.from()][e.to()] = e;
            }
            // in case of self-loops
            if (distTo[v][v] >= 0.0) {
                distTo[v][v] = 0.0;
                edgeTo[v][v] = DirectedEdge();
            }
        }

        // Floyd-Warshall updates
        for (int i = 0; i < V; i++) {
            // compute shortest paths using only 0, 1, ..., i as intermediate vertices
            for (int v = 0; v < V; v++) {
                if (edgeTo[v][i].to() == -1) continue;  // optimization
                for (int w = 0; w < V; w++) {
                    if (distTo[v][w] > distTo[v][i] + distTo[i][w]) {
                        distTo[v][w] = distTo[v][i] + distTo[i][w];
                        edgeTo[v][w] = edgeTo[i][w];
                    }
                }
                // check for negative cycle
                if (distTo[v][v] < 0.0) {
                    hasNegativeCycle = true;
                    return;
                }
            }
        }
    }

    /**
     * Is there a negative cycle?
     * @return {@code true} if there is a negative cycle, and {@code false} otherwise
     */
    bool hasNegativeCycle_() {
        return hasNegativeCycle;
    }

    /**
     * Returns a negative cycle, or {@code null} if there is no such cycle.
     * @return a negative cycle as an iterable of edges,
     * or {@code null} if there is no such cycle
     */
    forward_list<DirectedEdge> negativeCycle() {
        for (int v = 0; v < distTo.size(); v++) {
            // negative cycle in v's predecessor graph
            if (distTo[v][v] < 0.0) {
                int V = edgeTo.size();
                EdgeWeightedDigraph spt(V);
                for (int w = 0; w < V; w++)
                    if (edgeTo[v][w].to() != -1)
                        spt.addEdge(edgeTo[v][w]);
                EdgeWeightedDirectedCycle finder(spt);
                return finder.cycle_();
            }
        }
        return forward_list<DirectedEdge>(0);
    }

    /**
     * Is there a path from the vertex {@code s} to vertex {@code t}?
     * @param  s the source vertex
     * @param  t the destination vertex
     * @return {@code true} if there is a path from vertex {@code s}
     *         to vertex {@code t}, and {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     * @throws IllegalArgumentException unless {@code 0 <= t < V}
     */
    bool hasPath(int s, int t) {
        validateVertex(s);
        validateVertex(t);
        return distTo[s][t] < numeric_limits<double >::max();
    }

    /**
     * Returns the length of a shortest path from vertex {@code s} to vertex {@code t}.
     * @param  s the source vertex
     * @param  t the destination vertex
     * @return the length of a shortest path from vertex {@code s} to vertex {@code t};
     *         {@code Double.POSITIVE_INFINITY} if no such path
     * @throws UnsupportedOperationException if there is a negative cost cycle
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    double dist(int s, int t) {
        validateVertex(s);
        validateVertex(t);
        if (hasNegativeCycle_())
            throw runtime_error("Negative cost cycle exists");
        return distTo[s][t];
    }

    /**
     * Returns a shortest path from vertex {@code s} to vertex {@code t}.
     * @param  s the source vertex
     * @param  t the destination vertex
     * @return a shortest path from vertex {@code s} to vertex {@code t}
     *         as an iterable of edges, and {@code null} if no such path
     * @throws UnsupportedOperationException if there is a negative cost cycle
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<DirectedEdge> path(int s, int t) {
        validateVertex(s);
        validateVertex(t);
        if (hasNegativeCycle_())
            throw runtime_error("Negative cost cycle exists");
        if (!hasPath(s, t)) return forward_list<DirectedEdge>(0);
        forward_list<DirectedEdge> path;
        for (DirectedEdge e = edgeTo[s][t]; e.to() != -1; e = edgeTo[s][e.from()]) {
            path.push_front(e);
        }
        return path;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = distTo.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V-1));
    }


private:
    bool hasNegativeCycle;          // is there a negative cycle?
    vector<vector<double>> distTo;  // distTo[v][w] = length of shortest v->w path
    vector<vector<DirectedEdge>> edgeTo;  // edgeTo[v][w] = last edge on shortest v->w path
};

#endif //CH4_FLOYDWARSHALL_H
