#ifndef CH4_SYMBOLGRAPH_H
#define CH4_SYMBOLGRAPH_H

#include "../head/Graph.h"
#include <map>

using std::map;

/**
 *  The {@code SymbolGraph} class represents an undirected graph, where the
 *  vertex names are arbitrary strings.
 *  By providing mappings between string vertex names and integers,
 *  it serves as a wrapper around the
 *  {@link Graph} data type, which assumes the vertex names are integers
 *  between 0 and <em>V</em> - 1.
 *  It also supports initializing a symbol graph from a file.
 *  <p>
 *  This implementation uses an {@link ST} to map from strings to integers,
 *  an array to map from integers to strings, and a {@link Graph} to store
 *  the underlying graph.
 *  The <em>indexOf</em> and <em>contains</em> operations take time
 *  proportional to log <em>V</em>, where <em>V</em> is the number of vertices.
 *  The <em>nameOf</em> operation takes constant time.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
auto split = [](string s, char delim) {
    vector<string> tokens;
    stringstream ss(s);
    string tmp;
    while (getline(ss, tmp, delim)) {
        if (tmp != "")
            tokens.push_back(tmp);
    }
    return tokens;
};

class SymbolGraph {
public:
    /**
     * Initializes a graph from a file using the specified delimiter.
     * Each line in the file contains
     * the name of a vertex, followed by a list of the names
     * of the vertices adjacent to that vertex, separated by the delimiter.
     * @param filename the name of the file
     * @param delimiter the delimiter between fields
     */
    SymbolGraph(string filename, char delimiter) {
        // First pass builds the index by reading strings to associate
        // distinct strings with an index
        fstream in(filename);
        // while (in.hasNextLine()) {
        string tmp;
        while (getline(in, tmp)) {
            vector<string> a = split(tmp, delimiter);
            for (int i = 0; i < a.size(); i++) {
                if (st.find(a[i]) == st.end())
                    st[a[i]] = st.size()-1;
            }
        }

        // inverted index to get string keys in an array

        keys.resize(st.size());
        for (auto p: st) {
            keys[p.second] = p.first;
        }

        // second pass builds the graph by connecting first vertex on each
        // line to all others
        graph = new Graph(st.size());
        fstream in2(filename);
        while (getline(in2, tmp)) {
            vector<string> a = split(tmp, delimiter);
            int v = st[a[0]];
            for (int i = 1; i < a.size(); i++) {
                int w = st[a[i]];
                graph->addEdge(v, w);
            }
        }
    }

    /**
     * Does the graph contain the vertex named {@code s}?
     * @param s the name of a vertex
     * @return {@code true} if {@code s} is the name of a vertex, and {@code false} otherwise
     */
    bool contains(string s) {
        return st.find(s) != st.end();
    }

    /**
     * Returns the integer associated with the vertex named {@code s}.
     * @param s the name of a vertex
     * @return the integer (between 0 and <em>V</em> - 1) associated with the vertex named {@code s}
     */
    int indexOf(string s) {
        return st[s];
    }

    /**
     * Returns the name of the vertex associated with the integer {@code v}.
     * @param  v the integer corresponding to a vertex (between 0 and <em>V</em> - 1)
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     * @return the name of the vertex associated with the integer {@code v}
     */
    string nameOf(int v) {
        validateVertex(v);
        return keys[v];
    }

    /**
     * Returns the graph assoicated with the symbol graph. It is the client's responsibility
     * not to mutate the graph.
     * @return the graph associated with the symbol graph
     */
    Graph *getgraph() {
        return graph;
    }


private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = graph->getV();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    map<string, int> st;   // string -> index
    vector<string> keys;   // index  -> string
    Graph *graph;          // the underlying graph
};

#endif //CH4_SYMBOLGRAPH_H
