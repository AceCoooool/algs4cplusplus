
#ifndef CH4_DEPTHFIRSTSEARCH_H
#define CH4_DEPTHFIRSTSEARCH_H

#include <vector>
#include "../head/Graph.h"

using std::vector;

/**
 *  The {@code DepthFirstSearch} class represents a data type for
 *  determining the vertices connected to a given source vertex <em>s</em>
 *  in an undirected graph. For versions that find the paths, see
 *  {@link DepthFirstPaths} and {@link BreadthFirstPaths}.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  It uses extra space (not including the graph) proportional to <em>V</em>.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DepthFirstSearch {
public:
    /**
     * Computes the vertices in graph {@code G} that are
     * connected to the source vertex {@code s}.
     * @param G the graph
     * @param s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    DepthFirstSearch(Graph &G, int s) : count(0) {
        marked.resize(G.getV());
        validateVertex(s);
        dfs(G, s);
    }

    /**
     * Is there a path between the source vertex {@code s} and vertex {@code v}?
     * @param v the vertex
     * @return {@code true} if there is a path, {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool getmarked(int v) const {
        validateVertex(v);
        return marked[v];
    }

    /**
     * Returns the number of vertices connected to the source vertex {@code s}.
     * @return the number of vertices connected to the source vertex {@code s}
     */
    int getcount() {
        return count;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) const{
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    // depth first search from v
    void dfs(Graph &G, int v) {
        count++;
        marked[v] = true;
        for (int w : G.getadj(v)) {
            if (!marked[w]) {
                dfs(G, w);
            }
        }
    }

private:
    vector<bool> marked;  // marked[v] = is there an s-v path?
    int count;            // number of vertices connected to s
};

#endif //CH4_DEPTHFIRSTSEARCH_H
