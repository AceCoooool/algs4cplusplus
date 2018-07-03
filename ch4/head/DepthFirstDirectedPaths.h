#ifndef CH4_DEPTHFIRSTDIRECTEDPATHS_H
#define CH4_DEPTHFIRSTDIRECTEDPATHS_H

#include "../head/Digraph.h"

/**
 *  The {@code DepthFirstDirectedPaths} class represents a data type for finding
 *  directed paths from a source vertex <em>s</em> to every
 *  other vertex in the digraph.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Each call to {@link #hasPathTo(int)} takes constant time;
 *  each call to {@link #pathTo(int)} takes time proportional to the length
 *  of the path returned.
 *  It uses extra space (not including the graph) proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DepthFirstDirectedPaths {
public:
    /**
     * Computes a directed path from {@code s} to every other vertex in digraph {@code G}.
     * @param  G the digraph
     * @param  s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    DepthFirstDirectedPaths(Digraph &G, int s) : marked(G.getV(), false), edgeTo(G.getV()), s(s) {
        validateVertex(s);
        dfs(G, s);
    }

    /**
     * Is there a directed path from the source vertex {@code s} to vertex {@code v}?
     * @param  v the vertex
     * @return {@code true} if there is a directed path from the source
     *         vertex {@code s} to vertex {@code v}, {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool hasPathTo(int v) {
        validateVertex(v);
        return marked[v];
    }

    /**
     * Returns a directed path from the source vertex {@code s} to vertex {@code v}, or
     * {@code null} if no such path.
     * @param  v the vertex
     * @return the sequence of vertices on a directed path from the source vertex
     *         {@code s} to vertex {@code v}, as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<int> pathTo(int v) {
        validateVertex(v);
        if (!hasPathTo(v)) throw runtime_error("No path to this source");
        forward_list<int> path;
        for (int x = v; x != s; x = edgeTo[x])
            path.push_front(x);
        path.push_front(s);
        return path;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    void dfs(Digraph &G, int v) {
        marked[v] = true;
        for (int w : G.getadj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, w);
            }
        }
    }

private:
    vector<bool> marked;   // marked[v] = true iff v is reachable from s
    vector<int> edgeTo;    // edgeTo[v] = last edge on path from s to v
    int s;                 // source vertex
};

#endif //CH4_DEPTHFIRSTDIRECTEDPATHS_H
