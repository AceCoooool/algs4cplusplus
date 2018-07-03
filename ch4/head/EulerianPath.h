#ifndef CH4_EULERIANPATH_H
#define CH4_EULERIANPATH_H

#include "../head/Graph.h"
#include <queue>

using std::queue;

/**
 *  The {@code EulerianPath} class represents a data type
 *  for finding an Eulerian path in a graph.
 *  An <em>Eulerian path</em> is a path (not necessarily simple) that
 *  uses every edge in the graph exactly once.
 *  <p>
 *  This implementation uses a nonrecursive depth-first search.
 *  The constructor runs in O(<em>E</em> + <em>V</em>) time,
 *  and uses O(<em>E</em> + <em>V</em>) extra space,
 *  where <em>E</em> is the number of edges and <em>V</em> the number of vertices
 *  All other methods take O(1) time.
 *  <p>
 *  To compute Eulerian cycles in graphs, see {@link EulerianCycle}.
 *  To compute Eulerian cycles and paths in digraphs, see
 *  {@link DirectedEulerianCycle} and {@link DirectedEulerianPath}.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 * @author Robert Sedgewick
 * @author Kevin Wayne
 * @author Nate Liu
 */
class EulerianPath {
public:
    /**
     * Computes an Eulerian path in the specified graph, if one exists.
     *
     * @param G the graph
     */
    EulerianPath(Graph &G) {

        // find vertex from which to start potential Eulerian path:
        // a vertex v with odd degree(v) if it exits;
        // otherwise a vertex with degree(v) > 0
        int oddDegreeVertices = 0;
        int s = nonIsolatedVertex(G);
        for (int v = 0; v < G.getV(); v++) {
            if (G.degree(v) % 2 != 0) {
                oddDegreeVertices++;
                s = v;
            }
        }

        // graph can't have an Eulerian path
        // (this condition is needed for correctness)
        if (oddDegreeVertices > 2) return;

        // special case for graph with zero edges (has a degenerate Eulerian path)
        if (s == -1) s = 0;

        // create local view of adjacency lists, to iterate one vertex at a time
        // the helper Edge data type is used to avoid exploring both copies of an edge v-w
        vector<queue<Edge*>> adj(G.getV());

        for (int v = 0; v < G.getV(); v++) {
            int selfLoops = 0;
            for (int w : G.getadj(v)) {
                // careful with self loops
                if (v == w) {
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
            // push vertex with no more leaving edges to path
            path.push(v);
        }

        // check if all edges are used
        if (path.size() != G.getE() + 1) {
            while (!path.empty())
                path.pop();
        }
    }

    /**
     * Returns the sequence of vertices on an Eulerian path.
     *
     * @return the sequence of vertices on an Eulerian path;
     *         {@code null} if no such path
     */
    stack<int> getpath() {
        return path;
    }

    /**
     * Returns true if the graph has an Eulerian path.
     *
     * @return {@code true} if the graph has an Eulerian path;
     *         {@code false} otherwise
     */
    bool hasEulerianPath() {
        return !path.empty();
    }

    static void unitTest(Graph &G, string description) {
        cout << description << endl;
        cout << "-------------------------------------" << endl;
        cout << G;

        EulerianPath euler(G);

        cout << "Eulerian path:  ";
        if (euler.hasEulerianPath()) {
            auto tmp = euler.getpath();
            while (!tmp.empty()) {
                auto v = tmp.top();
                tmp.pop();
                cout << v << " ";
            }
            cout << endl;
        } else {
            cout << "None" << endl;
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
    // an undirected edge, with a field to indicate whether the edge has already been used
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
    stack<int> path;  // Eulerian path; empty if no suh path
};

#endif //CH4_EULERIANPATH_H
