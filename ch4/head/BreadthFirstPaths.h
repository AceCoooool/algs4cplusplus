#ifndef CH4_BREADTHFIRSTPATHS_H
#define CH4_BREADTHFIRSTPATHS_H

// TODO: Iterator type?
#include <queue>
#include <limits>
#include "../head/Graph.h"

using std::queue;
using std::numeric_limits;

/**
 *  The {@code BreadthFirstPaths} class represents a data type for finding
 *  shortest paths (number of edges) from a source vertex <em>s</em>
 *  (or a set of source vertices)
 *  to every other vertex in an undirected graph.
 *  <p>
 *  This implementation uses breadth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Each call to {@link #distTo(int)} and {@link #hasPathTo(int)} takes constant time;
 *  each call to {@link #pathTo(int)} takes time proportional to the length
 *  of the path.
 *  It uses extra space (not including the graph) proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class BreadthFirstPaths {
public:
    /**
     * Computes the shortest path between the source vertex {@code s}
     * and every other vertex in the graph {@code G}.
     * @param G the graph
     * @param s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    BreadthFirstPaths(Graph &G, int s) : marked(G.getV()), distTo(G.getV()), edgeTo(G.getV()) {
        validateVertex(s);
        bfs(G, s);
    }

    /**
     * Computes the shortest path between any one of the source vertices in {@code sources}
     * and every other vertex in graph {@code G}.
     * @param G the graph
     * @param sources the source vertices
     * @throws IllegalArgumentException unless {@code 0 <= s < V} for each vertex
     *         {@code s} in {@code sources}
     */
    BreadthFirstPaths(Graph &G, forward_list<int> &sources) : marked(G.getV()),
                                                              distTo(G.getV(), numeric_limits<int>::max()),
                                                              edgeTo(G.getV()) {
        validateVertices(sources);
        bfs(G, sources);
    }

    /**
     * Is there a path between the source vertex {@code s} (or sources) and vertex {@code v}?
     * @param v the vertex
     * @return {@code true} if there is a path, and {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool hasPathTo(int v) {
        validateVertex(v);
        return marked[v];
    }

    /**
     * Returns the number of edges in a shortest path between the source vertex {@code s}
     * (or sources) and vertex {@code v}?
     * @param v the vertex
     * @return the number of edges in a shortest path
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int distTo_op(int v) {
        validateVertex(v);
        return distTo[v];
    }

    /**
     * Returns a shortest path between the source vertex {@code s} (or sources)
     * and {@code v}, or {@code null} if no such path.
     * @param  v the vertex
     * @return the sequence of vertices on a shortest path, as an Iterable
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    forward_list<int> pathTo(int v) {
        validateVertex(v);
        if (!hasPathTo(v))throw runtime_error("this vertex is not in path");
        forward_list<int> path;
        int x;
        for (x = v; distTo[x] != 0; x = edgeTo[x])
            path.push_front(x);
        path.push_front(x);
        return path;
    }

private:
    // breadth-first search from a single source
    void bfs(Graph &G, int s) {
        queue<int> q;
        for (int v = 0; v < G.getV(); v++)
            distTo[v] = numeric_limits<int>::max();
        distTo[s] = 0;
        marked[s] = true;
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

    // breadth-first search from multiple sources
    void bfs(Graph &G, forward_list<int> &sources) {
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

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertices(forward_list<int> &vertices) {
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

private:
    vector<bool> marked;   // marked[v] = is there an s-v path
    vector<int> edgeTo;    // edgeTo[v] = previous edge on shortest s-v path
    vector<int> distTo;    // distTo[v] = number of edges shortest s-v path
};

#endif //CH4_BREADTHFIRSTPATHS_H
