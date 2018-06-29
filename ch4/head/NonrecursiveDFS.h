#ifndef CH4_NONRECURSIVEDFS_H
#define CH4_NONRECURSIVEDFS_H

#include "../head/Graph.h"

/**
 *  The {@code NonrecursiveDFS} class represents a data type for finding
 *  the vertices connected to a source vertex <em>s</em> in the undirected
 *  graph.
 *  <p>
 *  This implementation uses a nonrecursive version of depth-first search
 *  with an explicit stack.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  It uses extra space (not including the graph) proportional to <em>V</em>.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class NonrecursiveDFS {
public:
    /**
     * Computes the vertices connected to the source vertex {@code s} in the graph {@code G}.
     * @param G the graph
     * @param s the source vertex
     * @throws IllegalArgumentException unless {@code 0 <= s < V}
     */
    NonrecursiveDFS(Graph &G, int s) : marked(G.getV()) {
        validateVertex(s);

        // to be able to iterate over each adjacency list, keeping track of which
        // vertex in each adjacency list needs to be explored next
        vector<forward_list<int>> adj(G.getV());
        for (int v = 0; v < G.getV(); v++)
            adj[v] = G.getadj(v);

        // depth-first search using an explicit stack
        stack<int> stack_;
        marked[s] = true;
        stack_.push(s);
        while (!stack_.empty()) {
            int v = stack_.top();
            if (!adj[v].empty()) {
                int w = adj[v].front();
                adj[v].pop_front();
                // StdOut.printf("check %d\n", w);
                if (!marked[w]) {
                    // discovered vertex w for the first time
                    marked[w] = true;
                    // edgeTo[w] = v;
                    stack_.push(w);
                    // StdOut.printf("dfs(%d)\n", w);
                }
            } else {
                // StdOut.printf("%d done\n", v);
                stack_.pop();
            }
        }
    }

    /**
     * Is vertex {@code v} connected to the source vertex {@code s}?
     * @param v the vertex
     * @return {@code true} if vertex {@code v} is connected to the source vertex {@code s},
     *    and {@code false} otherwise
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
    vector<bool> marked;   // marked[v] = is there an s-v path?
};

#endif //CH4_NONRECURSIVEDFS_H
