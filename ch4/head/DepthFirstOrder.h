#ifndef CH4_DEPTHFIRSTORDER_H
#define CH4_DEPTHFIRSTORDER_H

// TODO: add edgeweightedgraph
#include "../head/Digraph.h"
#include "../head/EdgeWeightedDigraph.h"
#include <queue>

using std::queue;

/**
 *  The {@code DepthFirstOrder} class represents a data type for
 *  determining depth-first search ordering of the vertices in a digraph
 *  or edge-weighted digraph, including preorder, postorder, and reverse postorder.
 *  <p>
 *  This implementation uses depth-first search.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>preorder</em>, <em>postorder</em>, and <em>reverse postorder</em>
 *  operation takes take time proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DepthFirstOrder {
public:
    /**
     * Determines a depth-first order for the digraph {@code G}.
     * @param G the digraph
     */
    DepthFirstOrder(Digraph &G) : pre(G.getV()), post(G.getV()), marked(G.getV(), false),
                                  preCounter(0), postCounter(0) {
        for (int v = 0; v < G.getV(); v++)
            if (!marked[v]) dfs(G, v);
    }

    /**
     * Determines a depth-first order for the edge-weighted digraph {@code G}.
     * @param G the edge-weighted digraph
     */
    DepthFirstOrder(EdgeWeightedDigraph &G): pre(G.V_()), post(G.V_()), marked(G.V_(), false) {
        for (int v = 0; v < G.V_(); v++)
            if (!marked[v]) dfs(G, v);
    }

    /**
     * Returns the preorder number of vertex {@code v}.
     * @param  v the vertex
     * @return the preorder number of vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int getpre(int v) {
        validateVertex(v);
        return pre[v];
    }

    /**
     * Returns the vertices in preorder.
     * @return the vertices in preorder, as an iterable of vertices
     */
    queue<int> getpre() {
        return preorder;
    }

    /**
     * Returns the postorder number of vertex {@code v}.
     * @param  v the vertex
     * @return the postorder number of vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int getpost(int v) {
        validateVertex(v);
        return post[v];
    }

    /**
     * Returns the vertices in postorder.
     * @return the vertices in postorder, as an iterable of vertices
     */
    queue<int> getpost() {
        return postorder;
    }

    /**
     * Returns the vertices in reverse postorder.
     * @return the vertices in reverse postorder, as an iterable of vertices
     */
    forward_list<int> reversePost() {
        forward_list<int> reverse;
        auto tmp = postorder;
        while (!tmp.empty()) {
            auto t = tmp.front();
            tmp.pop();
            reverse.push_front(t);
        }
        return reverse;
    }

private:
    // run DFS in digraph G from vertex v and compute preorder/postorder
    void dfs(Digraph &G, int v) {
        marked[v] = true;
        pre[v] = preCounter++;
        preorder.push(v);
        for (int w : G.getadj(v)) {
            if (!marked[w]) {
                dfs(G, w);
            }
        }
        postorder.push(v);
        post[v] = postCounter++;
    }

    // run DFS in edge-weighted digraph G from vertex v and compute preorder/postorder
    void dfs(EdgeWeightedDigraph &G, int v) {
        marked[v] = true;
        pre[v] = preCounter++;
        preorder.push(v);
        for (DirectedEdge e : G.adj_(v)) {
            int w = e.to();
            if (!marked[w]) {
                dfs(G, w);
            }
        }
        postorder.push(v);
        post[v] = postCounter++;
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    vector<bool> marked;     // marked[v] = has v been marked in dfs?
    vector<int> pre;         // pre[v]    = preorder  number of v
    vector<int> post;        // post[v]   = postorder number of v
    queue<int> preorder;     // vertices in preorder
    queue<int> postorder;    // vertices in postorder
    int preCounter;          // counter for preorder numbering
    int postCounter;         // counter for postorder numbering
};

#endif //CH4_DEPTHFIRSTORDER_H
