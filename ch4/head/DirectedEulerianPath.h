#ifndef CH4_DIRECTEDEULERIANPATH_H
#define CH4_DIRECTEDEULERIANPATH_H

#include "../head/Digraph.h"
#include <iostream>

using std::cout;
using std::endl;

/**
 *  The {@code DirectedEulerianPath} class represents a data type
 *  for finding an Eulerian path in a digraph.
 *  An <em>Eulerian path</em> is a path (not necessarily simple) that
 *  uses every edge in the digraph exactly once.
 *  <p>
 *  This implementation uses a nonrecursive depth-first search.
 *  The constructor runs in O(E + V) time, and uses O(V) extra space,
 *  where E is the number of edges and V the number of vertices
 *  All other methods take O(1) time.
 *  <p>
 *  To compute Eulerian cycles in digraphs, see {@link DirectedEulerianCycle}.
 *  To compute Eulerian cycles and paths in undirected graphs, see
 *  {@link EulerianCycle} and {@link EulerianPath}.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 * @author Robert Sedgewick
 * @author Kevin Wayne
 * @author Nate Liu
 */
class DirectedEulerianPath {
public:
    /**
     * Computes an Eulerian path in the specified digraph, if one exists.
     *
     * @param G the digraph
     */
    DirectedEulerianPath(Digraph &G) {
        // find vertex from which to start potential Eulerian path:
        // a vertex v with outdegree(v) > indegree(v) if it exits;
        // otherwise a vertex with outdegree(v) > 0
        int deficit = 0;
        int s = nonIsolatedVertex(G);
        for (int v = 0; v < G.getV(); v++) {
            if (G.outdegree(v) > G.getindegree(v)) {
                deficit += (G.outdegree(v) - G.getindegree(v));
                s = v;
            }
        }

        // digraph can't have an Eulerian path
        // (this condition is needed)
        if (deficit > 1) return;

        // special case for digraph with zero edges (has a degenerate Eulerian path)
        if (s == -1) s = 0;

        // create local view of adjacency lists, to iterate one vertex at a time
        vector<forward_list<int>> adj(G.getV());
        for (int v = 0; v < G.getV(); v++)
            adj[v] = G.getadj(v);

        // greedily add to cycle, depth-first search style
        stack<int> stack1;
        stack1.push(s);
        while (!stack1.empty()) {
            int v = stack1.top();
            stack1.pop();
            while (!adj[v].empty()) {
                stack1.push(v);
                auto tmp = v;
                v = adj[v].front();
                adj[tmp].pop_front();
            }
            // push vertex with no more available edges to path
            path.push_front(v);
        }

        // check if all edges have been used
        if (distance(path.begin(), path.end()) != G.getE() + 1)
            path.clear();
    }

    /**
     * Returns the sequence of vertices on an Eulerian path.
     *
     * @return the sequence of vertices on an Eulerian path;
     *         {@code null} if no such path
     */
    forward_list<int> getpath() {
        return path;
    }

    /**
     * Returns true if the digraph has an Eulerian path.
     *
     * @return {@code true} if the digraph has an Eulerian path;
     *         {@code false} otherwise
     */
    bool hasEulerianPath() {
        return !path.empty();
    }

    static void unitTest(Digraph &G, string description) {
        cout << description << endl;
        cout << "-------------------------------------" << endl;
        cout << G;

        DirectedEulerianPath *euler = new DirectedEulerianPath(G);

        cout << "Eulerian path:  ";
        if (euler->hasEulerianPath()) {
            for (int v : euler->getpath()) {
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
    forward_list<int> path;  // Eulerian path; null if no suh path
};

#endif //CH4_DIRECTEDEULERIANPATH_H
