#ifndef CH4_EDGEWEIGHTEDDIGRAPH_H
#define CH4_EDGEWEIGHTEDDIGRAPH_H

#include "../head/DirectedEdge.h"
#include <vector>
#include <forward_list>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>

using std::vector;
using std::forward_list;
using std::uniform_int_distribution;
using std::to_string;
using std::string;
using std::fstream;
using std::distance;
using std::stringstream;

/**
 *  The {@code EdgeWeightedDigraph} class represents a edge-weighted
 *  digraph of vertices named 0 through <em>V</em> - 1, where each
 *  directed edge is of type {@link DirectedEdge} and has a real-valued weight.
 *  It supports the following two primary operations: add a directed edge
 *  to the digraph and iterate over all of edges incident from a given vertex.
 *  It also provides
 *  methods for returning the number of vertices <em>V</em> and the number
 *  of edges <em>E</em>. Parallel edges and self-loops are permitted.
 *  <p>
 *  This implementation uses an adjacency-lists representation, which
 *  is a vertex-indexed array of {@link Bag} objects.
 *  All operations take constant time (in the worst case) except
 *  iterating over the edges incident from a given vertex, which takes
 *  time proportional to the number of such edges.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/44sp">Section 4.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class EdgeWeightedDigraph {
public:
    /**
     * Initializes an empty edge-weighted digraph with {@code V} vertices and 0 edges.
     *
     * @param  V the number of vertices
     * @throws IllegalArgumentException if {@code V < 0}
     */
    EdgeWeightedDigraph(int V) : V(V), E(0), indegree(V, 0), adj(V) {
        if (V < 0) throw runtime_error("Number of vertices in a Digraph must be nonnegative");
    }

    /**
     * Initializes a random edge-weighted digraph with {@code V} vertices and <em>E</em> edges.
     *
     * @param  V the number of vertices
     * @param  E the number of edges
     * @throws IllegalArgumentException if {@code V < 0}
     * @throws IllegalArgumentException if {@code E < 0}
     */
    EdgeWeightedDigraph(int V, int E) : EdgeWeightedDigraph(V) {
        if (E < 0) throw runtime_error("Number of edges in a Digraph must be nonnegative");
        uniform_int_distribution<> dis(0, V - 1);
        uniform_int_distribution<> dis1(0, 100);
        for (int i = 0; i < E; i++) {
            int v = dis(g);
            int w = dis(g);
            double weight = 0.01 * dis1(g);
            DirectedEdge e(v, w, weight);
            addEdge(e);
        }
    }

    /**
     * Initializes an edge-weighted digraph from the specified input stream.
     * The format is the number of vertices <em>V</em>,
     * followed by the number of edges <em>E</em>,
     * followed by <em>E</em> pairs of vertices and edge weights,
     * with each entry separated by whitespace.
     *
     * @param  in the input stream
     * @throws IllegalArgumentException if the endpoints of any edge are not in prescribed range
     * @throws IllegalArgumentException if the number of vertices or edges is negative
     */
    EdgeWeightedDigraph(string filename) {
        fstream in(filename);
        in >> V;
        E = 0;
        indegree.resize(V, 0);
        adj.resize(V);
        int tmpE;
        in >> tmpE;
        if (tmpE < 0) throw runtime_error("Number of edges must be nonnegative");
        int v, w;
        double weight;
        for (int i = 0; i < tmpE; i++) {
            in >> v >> w;
            validateVertex(v);
            validateVertex(w);
            in >> weight;
            addEdge(DirectedEdge(v, w, weight));
        }
    }

    /**
     * Initializes a new edge-weighted digraph that is a deep copy of {@code G}.
     *
     * @param  G the edge-weighted digraph to copy
     */
    EdgeWeightedDigraph(const EdgeWeightedDigraph &G) : EdgeWeightedDigraph(G.V_()) {
        E = G.E_();
        for (int v = 0; v < G.V_(); v++)
            indegree[v] = G.indegree_(v);
        for (int v = 0; v < G.V_(); v++) {
            // reverse so that adjacency list is in same order as original
            forward_list<DirectedEdge> reverse;
            for (DirectedEdge e : G.adj[v]) {
                reverse.push_front(e);
            }
            for (DirectedEdge e : reverse) {
                adj[v].push_front(e);
            }
        }
    }

    /**
     * Returns the number of vertices in this edge-weighted digraph.
     *
     * @return the number of vertices in this edge-weighted digraph
     */
    int V_() const {
        return V;
    }

    /**
     * Returns the number of edges in this edge-weighted digraph.
     *
     * @return the number of edges in this edge-weighted digraph
     */
    int E_() const {
        return E;
    }

    /**
     * Adds the directed edge {@code e} to this edge-weighted digraph.
     *
     * @param  e the edge
     * @throws IllegalArgumentException unless endpoints of edge are between {@code 0}
     *         and {@code V-1}
     */
    void addEdge(DirectedEdge e) {
        int v = e.from();
        int w = e.to();
        validateVertex(v);
        validateVertex(w);
        adj[v].push_front(e);
        indegree[w]++;
        E++;
    }

    /**
     * Returns the directed edges incident from vertex {@code v}.
     *
     * @param  v the vertex
     * @return the directed edges incident from vertex {@code v} as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<DirectedEdge> adj_(int v) const {
        validateVertex(v);
        return adj[v];
    }

    /**
     * Returns the number of directed edges incident from vertex {@code v}.
     * This is known as the <em>outdegree</em> of vertex {@code v}.
     *
     * @param  v the vertex
     * @return the outdegree of vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int outdegree(int v) const {
        validateVertex(v);
        return distance(adj[v].begin(), adj[v].end());
    }

    /**
     * Returns the number of directed edges incident to vertex {@code v}.
     * This is known as the <em>indegree</em> of vertex {@code v}.
     *
     * @param  v the vertex
     * @return the indegree of vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int indegree_(int v) const {
        validateVertex(v);
        return indegree[v];
    }

    /**
     * Returns all directed edges in this edge-weighted digraph.
     * To iterate over the edges in this edge-weighted digraph, use foreach notation:
     * {@code for (DirectedEdge e : G.edges())}.
     *
     * @return all edges in this edge-weighted digraph, as an iterable
     */
    forward_list<DirectedEdge> edges() {
        forward_list<DirectedEdge> list;
        for (int v = 0; v < V; v++) {
            for (DirectedEdge e : adj_(v)) {
                list.push_front(e);
            }
        }
        return list;
    }

    /**
     * Returns a string representation of this edge-weighted digraph.
     *
     * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
     *         followed by the <em>V</em> adjacency lists of edges
     */
    friend ostream &operator<<(ostream &stream, const EdgeWeightedDigraph &e) {
        stringstream ss;
        ss << e.V << " " << e.E << std::endl;
        for (int v = 0; v < e.V; ++v) {
            ss << v << ": ";
            for (auto de: e.adj[v])
                ss << de << " ";
            ss << std::endl;
        }
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
    int V;    // number of vertices in this digraph
    int E;    // number of edges in this digraph
    vector<forward_list<DirectedEdge>> adj;   // adj[v] = adjacency list for vertex v
    vector<int> indegree;   // indegree[v] = indegree of vertex v
};

#endif //CH4_EDGEWEIGHTEDDIGRAPH_H
