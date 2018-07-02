#ifndef CH4_DIGRAPH_H
#define CH4_DIGRAPH_H

#include <forward_list>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <stack>
#include <ostream>
#include <sstream>

using std::forward_list;
using std::vector;
using std::runtime_error;
using std::string;
using std::fstream;
using std::to_string;
using std::stack;
using std::distance;
using std::ostream;
using std::stringstream;

/**
 *  The {@code Digraph} class represents a directed graph of vertices
 *  named 0 through <em>V</em> - 1.
 *  It supports the following two primary operations: add an edge to the digraph,
 *  iterate over all of the vertices adjacent from a given vertex.
 *  Parallel edges and self-loops are permitted.
 *  <p>
 *  This implementation uses an adjacency-lists representation, which
 *  is a vertex-indexed array of {@link Bag} objects.
 *  All operations take constant time (in the worst case) except
 *  iterating over the vertices adjacent from a given vertex, which takes
 *  time proportional to the number of such vertices.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Digraph {
public:
    /**
     * Initializes an empty digraph with <em>V</em> vertices.
     *
     * @param  V the number of vertices
     * @throws IllegalArgumentException if {@code V < 0}
     */
    Digraph(int V) : V(V), E(0), indegree(V), adj(V) {
        if (V < 0) throw runtime_error("Number of vertices in a Digraph must be nonnegative");
    }

    /**
     * Initializes a digraph from the specified input stream.
     * The format is the number of vertices <em>V</em>,
     * followed by the number of edges <em>E</em>,
     * followed by <em>E</em> pairs of vertices, with each entry separated by whitespace.
     *
     * @param  in the input stream
     * @throws IllegalArgumentException if the endpoints of any edge are not in prescribed range
     * @throws IllegalArgumentException if the number of vertices or edges is negative
     * @throws IllegalArgumentException if the input stream is in the wrong format
     */
    Digraph(string in): E(0) {
        fstream file(in);
        file >> V;
        if (V < 0) throw runtime_error("number of vertices in a Digraph must be nonnegative");
        indegree.resize(V);
        adj.resize(V);
        int tmpE;
        file >> tmpE;
        if (tmpE < 0) throw runtime_error("number of edges in a Digraph must be nonnegative");
        int v, w;
        for (int i = 0; i < tmpE; i++) {
            file >> v >> w;
            addEdge(v, w);
        }
    }

    /**
     * Initializes a new digraph that is a deep copy of the specified digraph.
     *
     * @param  G the digraph to copy
     */
    Digraph(const Digraph &G) : Digraph(G.getV()) {
        E = G.getE();
        for (int v = 0; v < V; v++)
            indegree[v] = G.getindegree(v);
        for (int v = 0; v < G.getV(); v++) {
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
     * Returns the number of vertices in this digraph.
     *
     * @return the number of vertices in this digraph
     */
    int getV() const {
        return V;
    }

    /**
     * Returns the number of edges in this digraph.
     *
     * @return the number of edges in this digraph
     */
    int getE() const {
        return E;
    }

    /**
    * Adds the directed edge v→w to this digraph.
    *
    * @param  v the tail vertex
    * @param  w the head vertex
    * @throws IllegalArgumentException unless both {@code 0 <= v < V} and {@code 0 <= w < V}
    */
    void addEdge(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        adj[v].push_front(w);
        indegree[w]++;
        E++;
    }

    /**
     * Returns the vertices adjacent from vertex {@code v} in this digraph.
     *
     * @param  v the vertex
     * @return the vertices adjacent from vertex {@code v} in this digraph, as an iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<int> getadj(int v) const {
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
    int getindegree(int v) const {
        validateVertex(v);
        return indegree[v];
    }

    /**
     * Returns the reverse of the digraph.
     *
     * @return the reverse of the digraph
     */
    Digraph *reverse() {
        Digraph *reverse = new Digraph(V);
        for (int v = 0; v < V; v++) {
            for (int w : getadj(v)) {
                reverse->addEdge(w, v);
            }
        }
        return reverse;
    }

    /**
     * Returns a string representation of the graph.
     *
     * @return the number of vertices <em>V</em>, followed by the number of edges <em>E</em>,
     *         followed by the <em>V</em> adjacency lists
     */
    friend ostream &operator<<(ostream &stream, const Digraph &dg) {
        stringstream ss;
        ss << dg.V << " vertices, " << dg.getE() << " edges" << std::endl;
        for (int v = 0; v < dg.V; ++v) {
            ss << v << ": ";
            for (auto w: dg.getadj(v))
                ss << w << " ";
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
    int V;                         // number of vertices in this digraph
    int E;                         // number of edges in this digraph
    vector<forward_list<int>> adj; // adj[v] = adjacency list for vertex v
    vector<int> indegree;          // indegree[v] = indegree of vertex v
};

#endif //CH4_DIGRAPH_H
