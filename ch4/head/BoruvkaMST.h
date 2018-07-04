#ifndef CH4_BORUVKAMST_H
#define CH4_BORUVKAMST_H

#include "../head/EdgeWeightedGraph.h"
#include "../head/UF.h"


/**
 *  The {@code BoruvkaMST} class represents a data type for computing a
 *  <em>minimum spanning tree</em> in an edge-weighted graph.
 *  The edge weights can be positive, zero, or negative and need not
 *  be distinct. If the graph is not connected, it computes a <em>minimum
 *  spanning forest</em>, which is the union of minimum spanning trees
 *  in each connected component. The {@code weight()} method returns the
 *  weight of a minimum spanning tree and the {@code edges()} method
 *  returns its edges.
 *  <p>
 *  This implementation uses <em>Boruvka's algorithm</em> and the union-find
 *  data type.
 *  The constructor takes time proportional to <em>E</em> log <em>V</em>
 *  and extra space (not including the graph) proportional to <em>V</em>,
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the {@code weight()} method takes constant time
 *  and the {@code edges()} method takes time proportional to <em>V</em>.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/43mst">Section 4.3</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For alternate implementations, see {@link LazyPrimMST}, {@link PrimMST},
 *  and {@link KruskalMST}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class BoruvkaMST {
public:
    /**
     * Compute a minimum spanning tree (or forest) of an edge-weighted graph.
     * @param G the edge-weighted graph
     */
    BoruvkaMST(EdgeWeightedGraph &G) {
        UF uf(G.V_());

        // repeat at most log V times or until we have V-1 edges
        for (int t = 1; t < G.V_() && distance(mst.begin(), mst.end()) < G.V_() - 1; t = t + t) {

            // foreach tree in forest, find closest edge
            // if edge weights are equal, ties are broken in favor of first edge in G.edges()
            vector<Edge> closest(G.V_());
            for (Edge e : G.edges()) {
                int v = e.either(), w = e.other(v);
                int i = uf.find(v), j = uf.find(w);
                if (i == j) continue;   // same tree
                if (closest[i].either() == -1 || e < closest[i]) closest[i] = e;
                if (closest[j].either() == -1 || e < closest[j]) closest[j] = e;
            }

            // add newly discovered edges to MST
            for (int i = 0; i < G.V_(); i++) {
                Edge e = closest[i];
                if (e.either() != -1) {
                    int v = e.either(), w = e.other(v);
                    // don't add the same edge twice
                    if (!uf.connected(v, w)) {
                        mst.push_front(e);
                        weight += e.weight_();
                        uf.union_op(v, w);
                    }
                }
            }
        }
    }

    /**
     * Returns the edges in a minimum spanning tree (or forest).
     * @return the edges in a minimum spanning tree (or forest) as
     *    an iterable of edges
     */
    forward_list<Edge> edges() {
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
    forward_list<Edge> mst;   // edges in MST
    double weight;            // weight of MST
};

#endif //CH4_BORUVKAMST_H
