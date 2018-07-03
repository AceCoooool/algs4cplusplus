#ifndef CH4_DIRECTEDCYCLE_H
#define CH4_DIRECTEDCYCLE_H

#include "../head/Digraph.h"

/**
 *  The {@code DirectedCycle} class represents a data type for
 *  determining whether a digraph has a directed cycle.
 *  The <em>hasCycle</em> operation determines whether the digraph has
 *  a simple directed cycle and, if so, the <em>cycle</em> operation
 *  returns one.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>hasCycle</em> operation takes constant time;
 *  the <em>cycle</em> operation takes time proportional
 *  to the length of the cycle.
 *  <p>
 *  See {@link Topological} to compute a topological order if the
 *  digraph is acyclic.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DirectedCycle {
public:
    /**
     * Determines whether the digraph {@code G} has a directed cycle and, if so,
     * finds such a cycle.
     * @param G the digraph
     */
    DirectedCycle(Digraph &G) : marked(G.getV(), false), onStack(G.getV(), false), edgeTo(G.getV()) {
        for (int v = 0; v < G.getV(); v++) {
            if (!marked[v] && cycle.empty()) dfs(G, v);
        }
    }

    /**
     * Does the digraph have a directed cycle?
     * @return {@code true} if the digraph has a directed cycle, {@code false} otherwise
     */
    bool hasCycle() {
        return !cycle.empty();
    }

    /**
     * Returns a directed cycle if the digraph has a directed cycle, and {@code null} otherwise.
     * @return a directed cycle (as an iterable) if the digraph has a directed cycle,
     *    and {@code null} otherwise
     */
    forward_list<int> getcycle() {
        return cycle;
    }


private:
    // check that algorithm computes either the topological order or finds a directed cycle
    void dfs(Digraph &G, int v) {
        onStack[v] = true;
        marked[v] = true;
        for (int w : G.getadj(v)) {

            // short circuit if directed cycle found
            if (!cycle.empty()) return;
            else if (!marked[w]) {  // found new vertex, so recur
                edgeTo[w] = v;
                dfs(G, w);
            }// trace back directed cycle
            else if (onStack[w]) {
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push_front(x);
                }
                cycle.push_front(w);
                cycle.push_front(v);
            }
        }
        onStack[v] = false;
    }

private:
    vector<bool> marked;       // marked[v] = has vertex v been marked?
    vector<int> edgeTo;        // edgeTo[v] = previous vertex on path to v
    vector<bool> onStack;      // onStack[v] = is vertex on the stack?
    forward_list<int> cycle;   // directed cycle (or null if no such cycle)

};


#endif //CH4_DIRECTEDCYCLE_H
