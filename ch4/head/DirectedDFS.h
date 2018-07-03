#ifndef CH4_DIRECTEDDFS_H
#define CH4_DIRECTEDDFS_H

#include "../head/Digraph.h"

/**
 *  The {@code DirectedDFS} class represents a data type for
 *  determining the vertices reachable from a given source vertex <em>s</em>
 *  (or set of source vertices) in a digraph. For versions that find the paths,
 *  see {@link DepthFirstDirectedPaths} and {@link BreadthFirstDirectedPaths}.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DirectedDFS {
public:
    /**
     * Computes the vertices in digraph {@code G} that are
     * reachable from the source vertex {@code s}.
     * @param G the digraph
     * @param s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    DirectedDFS(Digraph G, int s) : marked(G.getV(), false), count(0) {
        validateVertex(s);
        dfs(G, s);
    }

    /**
     * Computes the vertices in digraph {@code G} that are
     * connected to any of the source vertices {@code sources}.
     * @param G the graph
     * @param sources the source vertices
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     *         for each vertex {@code s} in {@code sources}
     */
    DirectedDFS(Digraph &G, vector<int> &sources) : marked(G.getV()), count(0) {
        validateVertices(sources);
        for (int v : sources) {
            if (!marked[v]) dfs(G, v);
        }
    }

    /**
     * Is there a directed path from the source vertex (or any
     * of the source vertices) and vertex {@code v}?
     * @param  v the vertex
     * @return {@code true} if there is a directed path, {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool getmarked(int v) {
        validateVertex(v);
        return marked[v];
    }

    /**
     * Returns the number of vertices reachable from the source vertex
     * (or source vertices).
     * @return the number of vertices reachable from the source vertex
     *   (or source vertices)
     */
    int getcount() {
        return count;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) const {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertices(vector<int> &vertices) const {
        if (vertices.empty()) {
            throw runtime_error("argument is null");
        }
        int V = marked.size();
        for (int v : vertices) {
            if (v < 0 || v >= V) {
                throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
            }
        }
    }

    void dfs(Digraph &G, int v) {
        count++;
        marked[v] = true;
        for (int w : G.getadj(v)) {
            if (!marked[w]) dfs(G, w);
        }
    }

private:
    vector<bool> marked; // marked[v] = true iff v is reachable from source(s)
    int count;           // number of vertices reachable from source(s)
};

#endif //CH4_DIRECTEDDFS_H
