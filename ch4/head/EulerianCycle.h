#ifndef CH4_EULERIANCYCLE_H
#define CH4_EULERIANCYCLE_H

#include <queue>
#include "../head/Graph.h"

using std::queue;

/**
 *  The {@code EulerianCycle} class represents a data type
 *  for finding an Eulerian cycle or path in a graph.
 *  An <em>Eulerian cycle</em> is a cycle (not necessarily simple) that
 *  uses every edge in the graph exactly once.
 *  <p>
 *  This implementation uses a nonrecursive depth-first search.
 *  The constructor runs in O(<Em>E</em> + <em>V</em>) time,
 *  and uses O(<em>E</em> + <em>V</em>) extra space, where <em>E</em> is the
 *  number of edges and <em>V</em> the number of vertices
 *  All other methods take O(1) time.
 *  <p>
 *  To compute Eulerian paths in graphs, see {@link EulerianPath}.
 *  To compute Eulerian cycles and paths in digraphs, see
 *  {@link DirectedEulerianCycle} and {@link DirectedEulerianPath}.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 *  @author Nate Liu
 */
class EulerianCycle {
public:
    /**
     * Computes an Eulerian cycle in the specified graph, if one exists.
     *
     * @param G the graph
     */
    EulerianCycle(Graph &G) {
        // must have at least one edge
        if (G.getE() == 0) return;

        // necessary condition: all vertices have even degree
        // (this test is needed or it might find an Eulerian path instead of cycle)
        for (int v = 0; v < G.getV(); v++)
            if (G.degree(v) % 2 != 0)
                return;

        // create local view of adjacency lists, to iterate one vertex at a time
        // the helper Edge data type is used to avoid exploring both copies of an edge v-w
        vector<queue<Edge*>> adj(G.getV());

        for (int v = 0; v < G.getV(); v++) {
            int selfLoops = 0;
            for (int w : G.getadj(v)) {
                // careful with self loops
                if (v == w) {  //TODO ?
                    if (selfLoops % 2 == 0) {
                        Edge *e = new Edge(v, w);
                        adj[v].push(e);
                        adj[w].push(e);
                    }
                    selfLoops++;
                } else if (v < w) {
                    Edge *e = new Edge(v, w);
                    adj[v].push(e);
                    adj[w].push(e);
                }
            }
        }

        // initialize stack with any non-isolated vertex
        int s = nonIsolatedVertex(G);
        stack<int> stack1;
        stack1.push(s);

        // greedily search through edges in iterative DFS style
        while (!stack1.empty()) {
            int v = stack1.top();
            stack1.pop();
            while (!adj[v].empty()) {
                Edge *edge = adj[v].front();
                adj[v].pop();
                if (edge->isUsed) continue;
                edge->isUsed = true;
                stack1.push(v);
                v = edge->other(v);
            }
            // push vertex with no more leaving edges to cycle
            cycle.push_front(v);
        }

        // check if all edges are used
        if (std::distance(cycle.begin(), cycle.end()) != G.getE() + 1) {
            cycle.clear();
        }
    }

    /**
     * Returns true if the graph has an Eulerian cycle.
     *
     * @return {@code true} if the graph has an Eulerian cycle;
     *         {@code false} otherwise
     */
    bool hasEulerianCycle() {
        return !cycle.empty();
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

    static void unitTest(Graph &G, string description) {
        cout << description << endl;
        cout << "-------------------------------------" << endl;
        cout << G;

        EulerianCycle euler(G);

        cout << "Eulerian cycle: ";
        if (euler.hasEulerianCycle()) {
            auto tmp = euler.getcycle();
            for (auto k: tmp)
                cout << k << " ";
            cout << endl;
        } else {
            cout << "none" << endl;
        }
        cout << endl;
    }

private:
    // returns any non-isolated vertex; -1 if no such vertex
    static int nonIsolatedVertex(Graph &G) {
        for (int v = 0; v < G.getV(); v++)
            if (G.degree(v) > 0)
                return v;
        return -1;
    }

private:
    class Edge {
    public:
        int v, w;
        bool isUsed;

        Edge(int v, int w) : v(v), w(w), isUsed(false) {}

        // returns the other vertex of the edge
        int other(int vertex) {
            if (vertex == v) return w;
            else if (vertex == w) return v;
            else throw runtime_error("Illegal endpoint");
        }
    };

private:
    forward_list<int> cycle;
};

#endif //CH4_EULERIANCYCLE_H
