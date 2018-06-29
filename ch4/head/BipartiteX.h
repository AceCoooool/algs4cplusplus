#ifndef CH4_BIPARTITEX_H
#define CH4_BIPARTITEX_H

#include <queue>
#include "../head/Graph.h"

using std::queue;

/**
 *  The {@code BipartiteX} class represents a data type for
 *  determining whether an undirected graph is bipartite or whether
 *  it has an odd-length cycle.
 *  The <em>isBipartite</em> operation determines whether the graph is
 *  bipartite. If so, the <em>color</em> operation determines a
 *  bipartition; if not, the <em>oddCycle</em> operation determines a
 *  cycle with an odd number of edges.
 *  <p>
 *  This implementation uses breadth-first search and is nonrecursive.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>isBipartite</em> and <em>color</em> operations
 *  take constant time; the <em>oddCycle</em> operation takes time proportional
 *  to the length of the cycle.
 *  See {@link Bipartite} for a recursive version that uses depth-first search.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class BipartiteX {
public:
    /**
     * Determines whether an undirected graph is bipartite and finds either a
     * bipartition or an odd-length cycle.
     *
     * @param  G the graph
     */
    BipartiteX(Graph &G) : isBipartite(true), color(G.getV()), marked(G.getV()), edgeTo(G.getV()) {
        for (int v = 0; v < G.getV() && isBipartite; v++) {
            if (!marked[v]) {
                bfs(G, v);
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
            throw runtime_error("Graph is not bipartite");
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
    queue<int> oddCycle() {
        return cycle;
    }

private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

    void bfs(Graph &G, int s) {
        queue<int> q;
        color[s] = WHITE;
        marked[s] = true;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int w : G.getadj(v)) {
                if (!marked[w]) {
                    marked[w] = true;
                    edgeTo[w] = v;
                    color[w] = !color[v];
                    q.push(w);
                } else if (color[w] == color[v]) {
                    isBipartite = false;

                    // to form odd cycle, consider s-v path and s-w path
                    // and let x be closest node to v and w common to two paths
                    // then (w-x path) + (x-v path) + (edge v-w) is an odd-length cycle
                    // Note: distTo[v] == distTo[w];
                    stack<int> stack1;
                    int x = v, y = w;
                    while (x != y) {
                        stack1.push(x);
                        cycle.push(y);
                        x = edgeTo[x];
                        y = edgeTo[y];
                    }
                    stack1.push(x);
                    while (!stack1.empty()) {
                        auto tmp = stack1.top();
                        cycle.push(tmp);
                        stack1.pop();
                    }
                    cycle.push(w);
                    return;
                }
            }
        }
    }

private:
    bool isBipartite;    // is the graph bipartite?
    vector<bool> color;  // color[v] gives vertices on one side of bipartition
    vector<bool> marked; // marked[v] = true iff v has been visited in DFS
    vector<int> edgeTo;  // edgeTo[v] = last edge on path to v
    queue<int> cycle;    // odd-length cycle

    static bool WHITE;
    static bool BLACK;
};

bool BipartiteX::WHITE = false;
bool BipartiteX::BLACK = true;

#endif //CH4_BIPARTITEX_H
