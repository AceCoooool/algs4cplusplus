#ifndef CH4_LAZYPRIMMST_H
#define CH4_LAZYPRIMMST_H

#include "../head/EdgeWeightedGraph.h"
#include <queue>

using std::queue;
using std::priority_queue;

/**
 *  The {@code LazyPrimMST} class represents a data type for computing a
 *  <em>minimum spanning tree</em> in an edge-weighted graph.
 *  The edge weights can be positive, zero, or negative and need not
 *  be distinct. If the graph is not connected, it computes a <em>minimum
 *  spanning forest</em>, which is the union of minimum spanning trees
 *  in each connected component. The {@code weight()} method returns the
 *  weight of a minimum spanning tree and the {@code edges()} method
 *  returns its edges.
 *  <p>
 *  This implementation uses a lazy version of <em>Prim's algorithm</em>
 *  with a binary heap of edges.
 *  The constructor takes time proportional to <em>E</em> log <em>E</em>
 *  and extra space (not including the graph) proportional to <em>E</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the {@code weight()} method takes constant time
 *  and the {@code edges()} method takes time proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For alternate implementations, see {@link PrimMST}, {@link KruskalMST},
 *  and {@link BoruvkaMST}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class LazyPrimMST {
public:
    /**
     * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
     * @param G the edge-weighted graph
     */
    LazyPrimMST(EdgeWeightedGraph &G) : marked(G.V_(), false) {
        for (int v = 0; v < G.V_(); v++)     // run Prim from all vertices to
            if (!marked[v]) prim(G, v);     // get a minimum spanning forest
    }

    /**
     * Returns the edges in a minimum spanning tree (or forest).
     * @return the edges in a minimum spanning tree (or forest) as
     *    an iterable of edges
     */
    queue<Edge> edges() {
        return mst;
    }

    /**
    * Returns the sum of the edge weights in a minimum spanning tree (or forest).
    * @return the sum of the edge weights in a minimum spanning tree (or forest)
    */
    double weight_() {
        return weight;
    }


private:
    // run Prim's algorithm
    void prim(EdgeWeightedGraph &G, int s) {
        scan(G, s);
        while (!pq.empty()) {                        // better to stop when mst has V-1 edges
            Edge e = pq.top();                      // smallest edge on pq
            pq.pop();
            int v = e.either(), w = e.other(v);        // two endpoints
            if (marked[v] && marked[w]) continue;      // lazy, both v and w already scanned
            mst.push(e);                            // add e to MST
            weight += e.weight_();
            if (!marked[v]) scan(G, v);               // v becomes part of tree
            if (!marked[w]) scan(G, w);               // w becomes part of tree
        }
    }

    // add all edges e incident to v onto pq if the other endpoint has not yet been scanned
    void scan(EdgeWeightedGraph &G, int v) {
        marked[v] = true;
        for (auto e : G.adj_(v))
            if (!marked[e.other(v)]) pq.push(e);
    }

private:
    double weight;             // total weight of MST
    queue<Edge> mst;           // edges in the MST
    vector<bool> marked;       // marked[v] = true iff v on tree
    priority_queue<Edge, vector<Edge>, std::greater<Edge>> pq;   // edges with one endpoint in tree
};

#endif //CH4_LAZYPRIMMST_H
