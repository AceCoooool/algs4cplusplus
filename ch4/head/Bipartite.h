#ifndef CH4_BIPARTITE_H
#define CH4_BIPARTITE_H

#include "../head/Graph.h"


/**
 *  The {@code Bipartite} class represents a data type for
 *  determining whether an undirected graph is bipartite or whether
 *  it has an odd-length cycle.
 *  The <em>isBipartite</em> operation determines whether the graph is
 *  bipartite. If so, the <em>color</em> operation determines a
 *  bipartition; if not, the <em>oddCycle</em> operation determines a
 *  cycle with an odd number of edges.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>isBipartite</em> and <em>color</em> operations
 *  take constant time; the <em>oddCycle</em> operation takes time proportional
 *  to the length of the cycle.
 *  See {@link BipartiteX} for a nonrecursive version that uses breadth-first
 *  search.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Bipartite {
public:
    /**
     * Determines whether an undirected graph is bipartite and finds either a
     * bipartition or an odd-length cycle.
     *
     * @param  G the graph
     */
    Bipartite(Graph &G) : isBipartite(true), color(G.getV()), marked(G.getV()), edgeTo(G.getV()) {
        for (int v = 0; v < G.getV(); v++) {
            if (!marked[v]) {
                dfs(G, v);
            }
        }
    }

    /**
     * Returns true if the graph is bipartite.
     *
     * @return {@code true} if the graph is bipartite; {@code false} otherwise
     */
    bool getisBipartite() {
        return isBipartite;
    }

    /**
     * Returns the side of the bipartite that vertex {@code v} is on.
     *
     * @param  v the vertex
     * @return the side of the bipartition that vertex {@code v} is on; two vertices
     *         are in the same side of the bipartition if and only if they have the
     *         same color
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     * @throws UnsupportedOperationException if this method is called when the graph
     *         is not bipartite
     */
    bool getcolor(int v) {
        validateVertex(v);
        if (!isBipartite)
            throw runtime_error("graph is not bipartite");
        return color[v];
    }

    /**
     * Returns an odd-length cycle if the graph is not bipartite, and
     * {@code null} otherwise.
     *
     * @return an odd-length cycle if the graph is not bipartite
     *         (and hence has an odd-length cycle), and {@code null}
     *         otherwise
     */
    stack<int> oddCycle() {
        return cycle;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    void dfs(Graph G, int v) {
        marked[v] = true;
        for (int w : G.getadj(v)) {
            // short circuit if odd-length cycle found
            if (!cycle.empty()) return;

            // found uncolored vertex, so recur
            if (!marked[w]) {
                edgeTo[w] = v;
                color[w] = !color[v];
                dfs(G, w);
            } // if v-w create an odd-length cycle, find it
            else if (color[w] == color[v]) {
                isBipartite = false;
                cycle.push(w);  // don't need this unless you want to include start vertex twice
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(w);
            }
        }
    }


private:
    bool isBipartite;     // is the graph bipartite?
    vector<bool> color;   // color[v] gives vertices on one side of bipartition
    vector<bool> marked;  // marked[v] = true iff v has been visited in DFS
    vector<int> edgeTo;   // edgeTo[v] = last edge on path to v
    stack<int> cycle;     // odd-length cycle
};

#endif //CH4_BIPARTITE_H
