#ifndef CH4_GRAPH_H
#define CH4_GRAPH_H

#include <forward_list>
#include <vector>
#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <stack>

using std::vector;
using std::forward_list;
using std::runtime_error;
using std::to_string;
using std::ostream;
using std::stringstream;
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::stack;

/**
 *  The {@code Graph} class represents an undirected graph of vertices
 *  named 0 through <em>V</em> – 1.
 *  It supports the following two primary operations: add an edge to the graph,
 *  iterate over all of the vertices adjacent to a vertex. It also provides
 *  methods for returning the number of vertices <em>V</em> and the number
 *  of edges <em>E</em>. Parallel edges and self-loops are permitted.
 *  By convention, a self-loop <em>v</em>-<em>v</em> appears in the
 *  adjacency list of <em>v</em> twice and contributes two to the degree
 *  of <em>v</em>.
 *  <p>
 *  This implementation uses an adjacency-lists representation, which
 *  is a vertex-indexed array of {@link Bag} objects.
 *  All operations take constant time (in the worst case) except
 *  iterating over the vertices adjacent to a given vertex, which takes
 *  time proportional to the number of such vertices.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Graph {
public:
    /**
     * Initializes an empty graph with {@code V} vertices and 0 edges.
     * param V the number of vertices
     *
     * @param  V number of vertices
     * @throws IllegalArgumentException if {@code V < 0}
     */
    Graph(int v) : V(v), E(0), adj(v) {
        if (V < 0) throw runtime_error("Number of vertices must be nonnegative");
    }

    /**
     * Initializes a graph from the specified input stream.
     * The format is the number of vertices <em>V</em>,
     * followed by the number of edges <em>E</em>,
     * followed by <em>E</em> pairs of vertices, with each entry separated by whitespace.
     *
     * @param  in the input stream
     * @throws IllegalArgumentException if the endpoints of any edge are not in prescribed range
     * @throws IllegalArgumentException if the number of vertices or edges is negative
     * @throws IllegalArgumentException if the input stream is in the wrong format
     */
    // TODO: add try catch
    Graph(string filename) {
        fstream file(filename);
        file >> V;
        file >> E;
        adj.resize(V);
        int v, w;
        while (file >> v >> w) {
            validateVertex(v);
            validateVertex(w);
            addEdge(v, w);
        }
    }

    // TODO: fix copy constructor
    /**
     * Initializes a new graph that is a deep copy of {@code G}.
     *
     * @param  G the graph to copy
     */
    Graph(const Graph &G): Graph(G.getV()) {
        E = G.getE();
        for (int v = 0; v < G.V; v++) {
            // reverse so that adjacency list is in same order as original
            stack<int> reverse;
            for (int w : G.adj[v]) {
                reverse.push(w);
            }
            while (!reverse.empty()) {
                auto w = reverse.top();
                reverse.pop();
                adj[v].push_front(w);
            }
        }
    }

    /**
     * Returns the number of vertices in this graph.
     *
     * @return the number of vertices in this graph
     */
    int getV() const {
        return V;
    }

    /**
     * Returns the number of edges in this graph.
     *
     * @return the number of edges in this graph
     */
    int getE() const {
        return E;
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) const {
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    /**
     * Adds the undirected edge v-w to this graph.
     *
     * @param  v one vertex in the edge
     * @param  w the other vertex in the edge
     * @throws IllegalArgumentException unless both {@code 0 <= v < V} and {@code 0 <= w < V}
     */
    void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        E++;
        adj[v].push_front(w);
        adj[w].push_front(v);
    }

    /**
     * Returns the vertices adjacent to vertex {@code v}.
     *
     * @param  v the vertex
     * @return the vertices adjacent to vertex {@code v}, as an iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    decltype(auto) getadj(int v) const {
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
        return std::distance(adj[v].begin(), adj[v].end());
    }

    friend ostream &operator<<(ostream &stream, const Graph &g) {
        stringstream ss;
        ss << g.V << " vertices, " << g.E << " edges" << endl;
        for (int v = 0; v < g.V; ++v) {
            ss << v << ": ";
            for (auto w:g.getadj(v))
                ss << w << " ";
            ss << endl;
        }
        stream << ss.str();
        return stream;
    }

private:
    int V;
    int E;
    vector<forward_list<int>> adj;
};

#endif //CH4_GRAPH_H
