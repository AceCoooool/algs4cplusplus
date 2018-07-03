#ifndef CH4_DIRECTEDEULERIANCYCLE_H
#define CH4_DIRECTEDEULERIANCYCLE_H

#include "../head/Digraph.h"
#include <iostream>

using std::cout;
using std::endl;

/**
 *  The {@code DirectedEulerianCycle} class represents a data type
 *  for finding an Eulerian cycle or path in a digraph.
 *  An <em>Eulerian cycle</em> is a cycle (not necessarily simple) that
 *  uses every edge in the digraph exactly once.
 *  <p>
 *  This implementation uses a nonrecursive depth-first search.
 *  The constructor runs in O(<Em>E</em> + <em>V</em>) time,
 *  and uses O(<em>V</em>) extra space, where <em>E</em> is the
 *  number of edges and <em>V</em> the number of vertices
 *  All other methods take O(1) time.
 *  <p>
 *  To compute Eulerian paths in digraphs, see {@link DirectedEulerianPath}.
 *  To compute Eulerian cycles and paths in undirected graphs, see
 *  {@link EulerianCycle} and {@link EulerianPath}.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *  @author Nate Liu
 */
class DirectedEulerianCycle {
public:
    /**
     * Computes an Eulerian cycle in the specified digraph, if one exists.
     *
     * @param G the digraph
     */
    DirectedEulerianCycle(Digraph &G) {

        // must have at least one edge
        if (G.getE() == 0) return;

        // necessary condition: indegree(v) = outdegree(v) for each vertex v
        // (without this check, DFS might return a path instead of a cycle)
        for (int v = 0; v < G.getV(); v++)
            if (G.outdegree(v) != G.getindegree(v))
                return;

        // create local view of adjacency lists, to iterate one vertex at a time
        vector<forward_list<int>> adj(G.getV());
        for (int v = 0; v < G.getV(); v++)
            adj[v] = G.getadj(v);

        // initialize stack with any non-isolated vertex
        int s = nonIsolatedVertex(G);
        stack<int> stack1;
        stack1.push(s);

        // greedily add to putative cycle, depth-first search style
        while (!stack1.empty()) {
            int v = stack1.top();
            stack1.pop();
            while (!adj[v].empty()) {
                stack1.push(v);
                auto tmp = v;
                v = adj[v].front();
                adj[tmp].pop_front();
            }
            // add vertex with no more leaving edges to cycle
            cycle.push_front(v);
        }

        // check if all edges have been used
        // (in case there are two or more vertex-disjoint Eulerian cycles)
        if (distance(cycle.begin(), cycle.end()) != G.getE() + 1)
            cycle.clear();
    }

    /**
     * Returns the sequence of vertices on an Eulerian cycle.
     *
     * @return the sequence of vertices on an Eulerian cycle;
     *         {@code null} if no such cycle
     */
    forward_list<int> getcycle() {
        return cycle;
    }

    /**
     * Returns true if the digraph has an Eulerian cycle.
     *
     * @return {@code true} if the digraph has an Eulerian cycle;
     *         {@code false} otherwise
     */
    bool hasEulerianCycle() {
        return !cycle.empty();
    }

    static void unitTest(Digraph &G, string description) {
        cout << description << endl;
        cout << "-------------------------------------" << endl;
        cout << G;

        DirectedEulerianCycle *euler = new DirectedEulerianCycle(G);

        cout << "Eulerian cycle: ";
        if (euler->hasEulerianCycle()) {
            for (int v : euler->getcycle()) {
                cout << v << " ";
            }
            cout << endl;
        } else {
            cout << "none" << endl;
        }
        cout << endl;
    }

private:
    // returns any non-isolated vertex; -1 if no such vertex
    static int nonIsolatedVertex(Digraph &G) {
        for (int v = 0; v < G.getV(); v++)
            if (G.outdegree(v) > 0)
                return v;
        return -1;
    }

private:
    forward_list<int> cycle;  // Eulerian cycle; null if no such cylce
};


#endif //CH4_DIRECTEDEULERIANCYCLE_H
