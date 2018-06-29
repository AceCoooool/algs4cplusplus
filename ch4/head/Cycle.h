#ifndef CH4_CYCLE_H
#define CH4_CYCLE_H

#include "../head/Graph.h"

/**
 *  The {@code Cycle} class represents a data type for
 *  determining whether an undirected graph has a simple cycle.
 *  The <em>hasCycle</em> operation determines whether the graph has
 *  a cycle and, if so, the <em>cycle</em> operation returns one.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>hasCycle</em> operation takes constant time;
 *  the <em>cycle</em> operation takes time proportional
 *  to the length of the cycle.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Cycle {
public:
    /**
     * Determines whether the undirected graph {@code G} has a cycle and,
     * if so, finds such a cycle.
     *
     * @param G the undirected graph
     */
    Cycle(Graph &G) : marked(G.getV()), edgeTo(G.getV()) {
        if (hasSelfLoop(G)) return;
        if (hasParallelEdges(G)) return;
        for (int v = 0; v < G.getV(); v++)
            if (!marked[v])
                dfs(G, -1, v);
    }

    /**
     * Returns true if the graph {@code G} has a cycle.
     *
     * @return {@code true} if the graph has a cycle; {@code false} otherwise
     */
    bool hasCycle() {
        return !cycle.empty();
    }

    /**
    * Returns a cycle in the graph {@code G}.
    * @return a cycle if the graph {@code G} has a cycle,
    *         and {@code null} otherwise
    */
    stack<int> getcycle() {
        return cycle;
    }

private:
    // does this graph have a self loop?
    // side effect: initialize cycle to be self loop
    bool hasSelfLoop(Graph &G) {
        for (int v = 0; v < G.getV(); v++) {
            for (int w : G.getadj(v)) {
                if (v == w) {
                    cycle.push(v);
                    cycle.push(v);
                    return true;
                }
            }
        }
        return false;
    }

    // does this graph have two parallel edges?
    // side effect: initialize cycle to be two parallel edges
    bool hasParallelEdges(Graph &G) {
        for (int v = 0; v < G.getV(); v++) {
            // check for parallel edges incident to v
            for (int w : G.getadj(v)) {
                if (marked[w]) {
                    cycle.push(v);
                    cycle.push(w);
                    cycle.push(v);
                    return true;
                }
                marked[w] = true;
            }

            // reset so marked[v] = false for all v
            for (int w : G.getadj(v)) {
                marked[w] = false;
            }
        }
        return false;
    }

    void dfs(Graph &G, int u, int v) {
        marked[v] = true;
        for (int w : G.getadj(v)) {
            // short circuit if cycle already found
            if (!cycle.empty()) return;

            if (!marked[w]) {
                edgeTo[w] = v;
                dfs(G, v, w);
            }// check for cycle (but disregard reverse of edge leading to v)
            else if (w != u) {
                for (int x = v; x != w; x = edgeTo[x]) {
                    cycle.push(x);
                }
                cycle.push(w);
                cycle.push(v);
            }
        }
    }

private:
    vector<bool> marked;
    vector<int> edgeTo;
    stack<int> cycle;
};

#endif //CH4_CYCLE_H
