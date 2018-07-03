#ifndef CH4_BREADTHFIRSTDIRECTEDPATHS_H
#define CH4_BREADTHFIRSTDIRECTEDPATHS_H

#include "../head/Digraph.h"
#include <limits>
#include <queue>

using std::numeric_limits;
using std::queue;

/**
 *  The {@code BreadthDirectedFirstPaths} class represents a data type for finding
 *  shortest paths (number of edges) from a source vertex <em>s</em>
 *  (or set of source vertices) to every other vertex in the digraph.
 *  <p>
 *  This implementation uses breadth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Each call to {@link #distTo(int)} and {@link #hasPathTo(int)} takes constant time;
 *  each call to {@link #pathTo(int)} takes time proportional to the length
 *  of the path.
 *  It uses extra space (not including the digraph) proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class BreadthFirstDirectedPaths {
public:
    /**
     * Computes the shortest path from {@code s} and every other vertex in graph {@code G}.
     * @param G the digraph
     * @param s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    BreadthFirstDirectedPaths(Digraph &G, int s) : marked(G.getV(), false),
                                                   distTo(G.getV(), numeric_limits<int>::max()), edgeTo(G.getV()) {
        validateVertex(s);
        bfs(G, s);
    }

    /**
     * Computes the shortest path from any one of the source vertices in {@code sources}
     * to every other vertex in graph {@code G}.
     * @param G the digraph
     * @param sources the source vertices
     * @throws IllegalArgumentException unless each vertex {@code v} in
     *         {@code sources} satisfies {@code 0 <= v < V}
     */
    BreadthFirstDirectedPaths(Digraph &G, vector<int> &sources) : marked(G.getV(), false),
                                                                  distTo(G.getV(), numeric_limits<int>::max()),
                                                                  edgeTo(G.getV()) {
        validateVertices(sources);
        bfs(G, sources);
    }

    /**
     * Is there a directed path from the source {@code s} (or sources) to vertex {@code v}?
     * @param v the vertex
     * @return {@code true} if there is a directed path, {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool hasPathTo(int v) {
        validateVertex(v);
        return marked[v];
    }

    /**
     * Returns the number of edges in a shortest path from the source {@code s}
     * (or sources) to vertex {@code v}?
     * @param v the vertex
     * @return the number of edges in a shortest path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int getdistTo(int v) {
        validateVertex(v);
        return distTo[v];
    }

    /**
     * Returns a shortest path from {@code s} (or sources) to {@code v}, or
     * {@code null} if no such path.
     * @param v the vertex
     * @return the sequence of vertices on a shortest path, as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<int> pathTo(int v) {
        validateVertex(v);

        if (!hasPathTo(v)) throw runtime_error("no path to this vertex");
        forward_list<int> path;
        int x;
        for (x = v; distTo[x] != 0; x = edgeTo[x])
            path.push_front(x);
        path.push_front(x);
        return path;
    }


private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertices(vector<int> &vertices) {
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

    // BFS from single source
    void bfs(Digraph &G, int s) {
        queue<int> q;
        marked[s] = true;
        distTo[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G.getadj(v)) {
                if (!marked[w]) {
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }

    // BFS from multiple sources
    void bfs(Digraph &G, vector<int> &sources) {
        queue<int> q;
        for (int s : sources) {
            marked[s] = true;
            distTo[s] = 0;
            q.push(s);
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G.getadj(v)) {
                if (!marked[w]) {
                    edgeTo[w] = v;
                    distTo[w] = distTo[v] + 1;
                    marked[w] = true;
                    q.push(w);
                }
            }
        }
    }

private:
    vector<bool> marked;   // marked[v] = is there an s->v path?
    vector<int> edgeTo;    // edgeTo[v] = last edge on shortest s->v path
    vector<int> distTo;    // distTo[v] = length of shortest s->v path

};

#endif //CH4_BREADTHFIRSTDIRECTEDPATHS_H
