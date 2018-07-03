#ifndef CH4_DIRECTEDCYCLEX_H
#define CH4_DIRECTEDCYCLEX_H

#include "../head/Digraph.h"
#include <queue>

using std::queue;

/**
 *  The {@code DirectedCycleX} class represents a data type for
 *  determining whether a digraph has a directed cycle.
 *  The <em>hasCycle</em> operation determines whether the digraph has
 *  a simple directed cycle and, if so, the <em>cycle</em> operation
 *  returns one.
 *  <p>
 *  This implementation uses a nonrecursive, queue-based algorithm.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>hasCycle</em> operation takes constant time;
 *  the <em>cycle</em> operation takes time proportional
 *  to the length of the cycle.
 *  <p>
 *  See {@link DirectedCycle} for a recursive version that uses depth-first search.
 *  See {@link Topological} or {@link TopologicalX} to compute a topological order
 *  when the digraph is acyclic.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DirectedCycleX {
public:
    DirectedCycleX(Digraph &G) {
        // indegrees of remaining vertices
        vector<int> indegree(G.getV());
        for (int v = 0; v < G.getV(); v++) {
            indegree[v] = G.getindegree(v);
        }

        // initialize queue to contain all vertices with indegree = 0
        queue<int> queue1;
        for (int v = 0; v < G.getV(); v++)
            if (indegree[v] == 0) queue1.push(v);

        while (!queue1.empty()) {
            int v = queue1.front();
            queue1.pop();
            for (int w : G.getadj(v)) {
                indegree[w]--;
                if (indegree[w] == 0) queue1.push(w);
            }
        }

        // there is a directed cycle in subgraph of vertices with indegree >= 1.
        vector<int> edgeTo(G.getV());
        int root = -1;  // any vertex with indegree >= -1
        for (int v = 0; v < G.getV(); v++) {
            if (indegree[v] == 0) continue;
            else root = v;
            for (int w : G.getadj(v)) {
                if (indegree[w] > 0) {
                    edgeTo[w] = v;
                }
            }
        }

        if (root != -1) {
            // find any vertex on cycle
            vector<bool> visited(G.getV(), false);
            while (!visited[root]) {
                visited[root] = true;
                root = edgeTo[root];
            }

            // extract cycle
            int v = root;
            do {
                cycle.push_front(v);
                v = edgeTo[v];
            } while (v != root);
            cycle.push_front(root);
        }
    }

    /**
     * Returns a directed cycle if the digraph has a directed cycle, and {@code null} otherwise.
     * @return a directed cycle (as an iterable) if the digraph has a directed cycle,
     *    and {@code null} otherwise
     */
    forward_list<int> getcycle() {
        return cycle;
    }

    /**
     * Does the digraph have a directed cycle?
     * @return {@code true} if the digraph has a directed cycle, {@code false} otherwise
     */
    bool hasCycle() {
        return !cycle.empty();
    }

private:
    forward_list<int> cycle;   // the directed cycle; null if digraph is acyclic
};


#endif //CH4_DIRECTEDCYCLEX_H
