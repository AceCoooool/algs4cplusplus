#ifndef CH4_PRIMMST_H
#define CH4_PRIMMST_H

#include "../head/EdgeWeightedGraph.h"
#include "../head/IndexMinPQ.h"
#include <queue>
#include <numeric>

using std::queue;
using std::numeric_limits;

/**
 *  The {@code PrimMST} class represents a data type for computing a
 *  <em>minimum spanning tree</em> in an edge-weighted graph.
 *  The edge weights can be positive, zero, or negative and need not
 *  be distinct. If the graph is not connected, it computes a <em>minimum
 *  spanning forest</em>, which is the union of minimum spanning trees
 *  in each connected component. The {@code weight()} method returns the
 *  weight of a minimum spanning tree and the {@code edges()} method
 *  returns its edges.
 *  <p>
 *  This implementation uses <em>Prim's algorithm</em> with an indexed
 *  binary heap.
 *  The constructor takes time proportional to <em>E</em> log <em>V</em>
 *  and extra space (not including the graph) proportional to <em>V</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the {@code weight()} method takes constant time
 *  and the {@code edges()} method takes time proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For alternate implementations, see {@link LazyPrimMST}, {@link KruskalMST},
 *  and {@link BoruvkaMST}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class PrimMST {
public:
    /**
     * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
     * @param G the edge-weighted graph
     */
    PrimMST(EdgeWeightedGraph &G) : edgeTo(G.V_()), distTo(G.V_(), numeric_limits<double>::max()),
                                    marked(G.V_(), false), pq(G.V_()) {
        for (int v = 0; v < G.V_(); v++)      // run from each vertex to find
            if (!marked[v]) prim(G, v);      // minimum spanning forest
    }

    /**
     * Returns the edges in a minimum spanning tree (or forest).
     * @return the edges in a minimum spanning tree (or forest) as
     *    an iterable of edges
     */
    queue<Edge> edges() {
        queue<Edge> mst;
        for (int v = 0; v < edgeTo.size(); v++) {
            Edge e = edgeTo[v];
            if (e.either() != -1) {
                mst.push(e);
            }
        }
        return mst;
    }

    /**
     * Returns the sum of the edge weights in a minimum spanning tree (or forest).
     * @return the sum of the edge weights in a minimum spanning tree (or forest)
     */
    double weight_() {
        double weight = 0.0;
        auto res = edges();
        while (!res.empty()) {
            auto e = res.front();
            res.pop();
            weight += e.weight_();
        }
        return weight;
    }

private:
    // run Prim's algorithm in graph G, starting from vertex s
    void prim(EdgeWeightedGraph &G, int s) {
        distTo[s] = 0.0;
        pq.insert(s, distTo[s]);
        while (!pq.isEmpty()) {
            int v = pq.delMin();
            scan(G, v);
        }
    }

    // scan vertex v
    void scan(EdgeWeightedGraph &G, int v) {
        marked[v] = true;
        for (Edge e : G.adj_(v)) {
            int w = e.other(v);
            if (marked[w]) continue;         // v-w is obsolete edge
            if (e.weight_() < distTo[w]) {
                distTo[w] = e.weight_();
                edgeTo[w] = e;
                if (pq.contains(w)) pq.decreaseKey(w, distTo[w]);
                else pq.insert(w, distTo[w]);
            }
        }
    }

private:
    vector<Edge> edgeTo;    // edgeTo[v] = shortest edge from tree vertex to non-tree vertex
    vector<double> distTo;  // distTo[v] = weight of shortest such edge
    vector<bool> marked;    // marked[v] = true if v on tree, false otherwise
    IndexMinPQ<double> pq;
};

#endif //CH4_PRIMMST_H
