#ifndef CH4_ADJMATRIXEDGEWEIGHTEDDIGRAPH_H
#define CH4_ADJMATRIXEDGEWEIGHTEDDIGRAPH_H

#include "../head/DirectedEdge.h"
#include <vector>
#include <random>
#include <sstream>
#include <iostream>

std::random_device rd;
std::mt19937 g(rd());

using std::cout;
using std::endl;
using std::vector;
using std::to_string;
using std::stringstream;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

/**
 *  The {@code AdjMatrixEdgeWeightedDigraph} class represents a edge-weighted
 *  digraph of vertices named 0 through <em>V</em> - 1, where each
 *  directed edge is of type {@link DirectedEdge} and has a real-valued weight.
 *  It supports the following two primary operations: add a directed edge
 *  to the digraph and iterate over all of edges incident from a given vertex.
 *  It also provides
 *  methods for returning the number of vertices <em>V</em> and the number
 *  of edges <em>E</em>. Parallel edges are disallowed; self-loops are permitted.
 *  <p>
 *  This implementation uses an adjacency-matrix representation.
 *  All operations take constant time (in the worst case) except
 *  iterating over the edges incident from a given vertex, which takes
 *  time proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class AdjMatrixEdgeWeightedDigraph {
public:
    /**
     * Initializes an empty edge-weighted digraph with {@code V} vertices and 0 edges.
     * @param V the number of vertices
     * @throws IllegalArgumentException if {@code V < 0}
     */
    AdjMatrixEdgeWeightedDigraph(int V) : V(V), E(0), adj(V, vector<DirectedEdge>(V)) {
        if (V < 0) throw runtime_error("number of vertices must be nonnegative");
    }

    /**
     * Initializes a random edge-weighted digraph with {@code V} vertices and <em>E</em> edges.
     * @param V the number of vertices
     * @param E the number of edges
     * @throws IllegalArgumentException if {@code V < 0}
     * @throws IllegalArgumentException if {@code E < 0}
     */
    AdjMatrixEdgeWeightedDigraph(int V, int E) : AdjMatrixEdgeWeightedDigraph(V) {
        if (E < 0) throw runtime_error("number of edges must be nonnegative");
        if (E > V * V) throw runtime_error("too many edges");

        uniform_int_distribution<> dis(0, V - 1);
        uniform_real_distribution<> dis2(0, 1);
        // can be inefficient
        while (this->E != E) {
            int v = dis(g);
            int w = dis(g);
            double weight = round(100 * dis2(g)) / 100.0;
            addEdge(DirectedEdge(v, w, weight));
        }
    }

    /**
     * Returns the number of vertices in the edge-weighted digraph.
     * @return the number of vertices in the edge-weighted digraph
     */
    int V_() {
        return V;
    }

    /**
     * Returns the number of edges in the edge-weighted digraph.
     * @return the number of edges in the edge-weighted digraph
     */
    int E_() {
        return E;
    }

    /**
     * Adds the directed edge {@code e} to the edge-weighted digraph (if there
     * is not already an edge with the same endpoints).
     * @param e the edge
     */
    void addEdge(DirectedEdge e) {
        int v = e.from();
        int w = e.to();
        validateVertex(v);
        validateVertex(w);
        if (adj[v][w].to() == -1) {
            E++;
            adj[v][w] = e;
        }
    }

    /**
     * Returns the directed edges incident from vertex {@code v}.
     * @param v the vertex
     * @return the directed edges incident from vertex {@code v} as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    vector<DirectedEdge> adj_(int v) const {
        validateVertex(v);
        vector<DirectedEdge> res;
        for (auto a: adj[v]) {
            if (a.to() != -1)
                res.push_back(a);
        }
        return res;
    }

    friend ostream &operator<<(ostream &stream, const AdjMatrixEdgeWeightedDigraph &mat) {
        stringstream ss;
        ss << mat.V << " " << mat.E << std::endl;
        for (int v = 0; v < mat.V; ++v) {
            ss << v << " ";
            for (auto e: mat.adj_(v))
                ss << e << " ";
            ss << endl;
        }
        ss << endl;
        stream << ss.str();
        return stream;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) const {
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    int V;
    int E;
    vector<vector<DirectedEdge>> adj;
};

#endif //CH4_ADJMATRIXEDGEWEIGHTEDDIGRAPH_H
