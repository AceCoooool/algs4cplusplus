#ifndef CH4_EDGEWEIGHTEDGRAPH_H
#define CH4_EDGEWEIGHTEDGRAPH_H

#include "../head/Edge.h"
#include <forward_list>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

std::random_device rd;
std::mt19937 g(rd());

using std::endl;
using std::forward_list;
using std::vector;
using std::string;
using std::fstream;
using std::to_string;
using std::distance;
using std::stringstream;
using std::uniform_int_distribution;
using std::uniform_real_distribution;

/**
 *  The {@code EdgeWeightedGraph} class represents an edge-weighted
 *  graph of vertices named 0 through <em>V</em> – 1, where each
 *  undirected edge is of type {@link Edge} and has a real-valued weight.
 *  It supports the following two primary operations: add an edge to the graph,
 *  iterate over all of the edges incident to a vertex. It also provides
 *  methods for returning the number of vertices <em>V</em> and the number
 *  of edges <em>E</em>. Parallel edges and self-loops are permitted.
 *  By convention, a self-loop <em>v</em>-<em>v</em> appears in the
 *  adjacency list of <em>v</em> twice and contributes two to the degree
 *  of <em>v</em>.
 *  <p>
 *  This implementation uses an adjacency-lists representation, which
 *  is a vertex-indexed array of {@link Bag} objects.
 *  All operations take constant time (in the worst case) except
 *  iterating over the edges incident to a given vertex, which takes
 *  time proportional to the number of such edges.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class EdgeWeightedGraph {
public:
    /**
     * Initializes an empty edge-weighted graph with {@code V} vertices and 0 edges.
     *
     * @param  V the number of vertices
     * @throws IllegalArgumentException if {@code V < 0}
     */
    EdgeWeightedGraph(int V) : V(V), E(0), adj(V) {
        if (V < 0) throw runtime_error("Number of vertices must be nonnegative");
    }

    /**
     * Initializes a random edge-weighted graph with {@code V} vertices and <em>E</em> edges.
     *
     * @param  V the number of vertices
     * @param  E the number of edges
     * @throws IllegalArgumentException if {@code V < 0}
     * @throws IllegalArgumentException if {@code E < 0}
     */
    EdgeWeightedGraph(int V, int E) : EdgeWeightedGraph(V) {
        if (E < 0) throw runtime_error("Number of edges must be nonnegative");

        uniform_int_distribution<> dis(0, V - 1);
        uniform_real_distribution<double> dis2(0, 1);
        for (int i = 0; i < E; i++) {
            int v = dis(g);
            int w = dis(g);
            double weight = std::round(100 * dis2(g)) / 100.0;
            Edge e(v, w, weight);
            addEdge(e);
        }
    }

    /**
     * Initializes an edge-weighted graph from an input stream.
     * The format is the number of vertices <em>V</em>,
     * followed by the number of edges <em>E</em>,
     * followed by <em>E</em> pairs of vertices and edge weights,
     * with each entry separated by whitespace.
     *
     * @param  in the input stream
     * @throws IllegalArgumentException if the endpoints of any edge are not in prescribed range
     * @throws IllegalArgumentException if the number of vertices or edges is negative
     */
    EdgeWeightedGraph(string filename) {
        fstream in(filename);
        in >> V;
        E = 0;
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
            Edge e(v, w, weight);
            addEdge(e);
        }
    }

    /**
     * Initializes a new edge-weighted graph that is a deep copy of {@code G}.
     *
     * @param  G the edge-weighted graph to copy
     */
    EdgeWeightedGraph(const EdgeWeightedGraph &G) : EdgeWeightedGraph(G.V_()) {
        E = G.E_();
        for (int v = 0; v < G.V_(); v++) {
            // reverse so that adjacency list is in same order as original
            forward_list<Edge> reverse;
            for (Edge e : G.adj[v]) {
                reverse.push_front(e);
            }
            for (Edge e : reverse) {
                adj[v].push_front(e);
            }
        }
    }

    /**
     * Returns the number of vertices in this edge-weighted graph.
     *
     * @return the number of vertices in this edge-weighted graph
     */
    int V_() const {
        return V;
    }

    /**
     * Returns the number of edges in this edge-weighted graph.
     *
     * @return the number of edges in this edge-weighted graph
     */
    int E_() const {
        return E;
    }

    /**
     * Adds the undirected edge {@code e} to this edge-weighted graph.
     *
     * @param  e the edge
     * @throws IllegalArgumentException unless both endpoints are between {@code 0} and {@code V-1}
     */
    void addEdge(Edge e) {
        int v = e.either();
        int w = e.other(v);
        validateVertex(v);
        validateVertex(w);
        adj[v].push_front(e);
        adj[w].push_front(e);
        E++;
    }

    /**
     * Returns the edges incident on vertex {@code v}.
     *
     * @param  v the vertex
     * @return the edges incident on vertex {@code v} as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<Edge> adj_(int v) {
        validateVertex(v);
        return adj[v];
    }

    /**
     * Returns the degree of vertex {@code v}.
     *
     * @param  v the vertex
     * @return the degree of vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int degree(int v) {
        validateVertex(v);
        return distance(adj[v].begin(), adj[v].end());
    }

    /**
     * Returns all edges in this edge-weighted graph.
     * To iterate over the edges in this edge-weighted graph, use foreach notation:
     * {@code for (Edge e : G.edges())}.
     *
     * @return all edges in this edge-weighted graph, as an iterable
     */
    forward_list<Edge> edges() {
        forward_list<Edge> list;
        for (int v = 0; v < V; v++) {
            int selfLoops = 0;
            for (Edge e : adj_(v)) {
                if (e.other(v) > v) {
                    list.push_front(e);
                }
                    // add only one copy of each self loop (self loops will be consecutive)
                else if (e.other(v) == v) {
                    if (selfLoops % 2 == 0) list.push_front(e);
                    selfLoops++;
                }
            }
        }
        return list;
    }

    /**
     * Returns a string representation of the edge-weighted graph.
     * This method takes time proportional to <em>E</em> + <em>V</em>.
     *
     * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
     *         followed by the <em>V</em> adjacency lists of edges
     */
    friend ostream &operator<<(ostream &stream, const EdgeWeightedGraph &eg) {
        stringstream ss;
        ss << eg.V << " " << eg.E << endl;
        for (int v = 0; v < eg.V; ++v) {
            ss << v << ": ";
            for (auto e: eg.adj[v])
                ss << e << " ";
            ss << endl;
        }
        stream << ss.str();
        return stream;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }


private:
    int V, E;
    vector<forward_list<Edge>> adj;
};

#endif //CH4_EDGEWEIGHTEDGRAPH_H
