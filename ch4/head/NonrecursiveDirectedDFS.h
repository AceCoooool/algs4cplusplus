#ifndef CH4_NONRECURSIVEDIRECTEDDFS_H
#define CH4_NONRECURSIVEDIRECTEDDFS_H

#include "../head/Digraph.h"

/**
 *  The {@code NonrecursiveDirectedDFS} class represents a data type for finding
 *  the vertices reachable from a source vertex <em>s</em> in the digraph.
 *  <p>
 *  This implementation uses a nonrecursive version of depth-first search
 *  with an explicit stack.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  It uses extra space (not including the digraph) proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class NonrecursiveDirectedDFS {
public:
    /**
     * Computes the vertices reachable from the source vertex {@code s} in the digraph {@code G}.
     * @param  G the digraph
     * @param  s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    NonrecursiveDirectedDFS(Digraph &G, int s) : marked(G.getV(), false) {
        validateVertex(s);

        // to be able to iterate over each adjacency list, keeping track of which
        // vertex in each adjacency list needs to be explored next
        vector<forward_list<int>> adj(G.getV());
        for (int v = 0; v < G.getV(); v++)
            adj[v] = G.getadj(v);

        // depth-first search using an explicit stack
        stack<int> stack;
        marked[s] = true;
        stack.push(s);
        while (!stack.empty()) {
            int v = stack.top();
            if (!adj[v].empty()) {
                int w = adj[v].front();
                adj[v].pop_front();
                // StdOut.printf("check %d\n", w);
                if (!marked[w]) {
                    // discovered vertex w for the first time
                    marked[w] = true;
                    // edgeTo[w] = v;
                    stack.push(w);
                    // StdOut.printf("dfs(%d)\n", w);
                }
            } else {
                // StdOut.printf("%d done\n", v);
                stack.pop();
            }
        }
    }

    /**
     * Is vertex {@code v} reachable from the source vertex {@code s}?
     * @param  v the vertex
     * @return {@code true} if vertex {@code v} is reachable from the source vertex {@code s},
     *         and {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    bool getmarked(int v) {
        validateVertex(v);
        return marked[v];
    }


private:
    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    vector<bool> marked;   // marked[v] = is there an s->v path?
};

#endif //CH4_NONRECURSIVEDIRECTEDDFS_H
