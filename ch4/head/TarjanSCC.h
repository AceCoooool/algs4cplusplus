#ifndef CH4_TARJANSCC_H
#define CH4_TARJANSCC_H

#include "../head/Digraph.h"

/**
 *  The {@code TarjanSCC} class represents a data type for
 *  determining the strong components in a digraph.
 *  The <em>id</em> operation determines in which strong component
 *  a given vertex lies; the <em>areStronglyConnected</em> operation
 *  determines whether two vertices are in the same strong component;
 *  and the <em>count</em> operation determines the number of strong
 *  components.

 *  The <em>component identifier</em> of a component is one of the
 *  vertices in the strong component: two vertices have the same component
 *  identifier if and only if they are in the same strong component.

 *  <p>
 *  This implementation uses Tarjan's algorithm.
 *  The constructor takes time proportional to <em>V</em> + <em>E</em>
 *  (in the worst case),
 *  where <em>V</em> is the number of vertices and <em>E</em> is the number of edges.
 *  Afterwards, the <em>id</em>, <em>count</em>, and <em>areStronglyConnected</em>
 *  operations take constant time.
 *  For alternate implementations of the same API, see
 *  {@link KosarajuSharirSCC} and {@link GabowSCC}.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class TarjanSCC {
public:
    /**
     * Computes the strong components of the digraph {@code G}.
     * @param G the digraph
     */
    TarjanSCC(Digraph &G) : marked(G.getV(), false), id(G.getV()), low(G.getV()), pre(0), count(0) {
        for (int v = 0; v < G.getV(); v++) {
            if (!marked[v]) dfs(G, v);
        }
    }

    /**
     * Returns the number of strong components.
     * @return the number of strong components
     */
    int count_() {
        return count;
    }

    /**
     * Are vertices {@code v} and {@code w} in the same strong component?
     * @param  v one vertex
     * @param  w the other vertex
     * @return {@code true} if vertices {@code v} and {@code w} are in the same
     *         strong component, and {@code false} otherwise
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     * @throws IllegalArgumentException unless {@code 0 <= w < V}
     */
    bool stronglyConnected(int v, int w) {
        validateVertex(v);
        validateVertex(w);
        return id[v] == id[w];
    }

    /**
     * Returns the component id of the strong component containing vertex {@code v}.
     * @param  v the vertex
     * @return the component id of the strong component containing vertex {@code v}
     * @throws IllegalArgumentException unless {@code 0 <= v < V}
     */
    int id_(int v) {
        validateVertex(v);
        return id[v];
    }


private:
    void dfs(Digraph &G, int v) {
        marked[v] = true;
        low[v] = pre++;
        int min = low[v];
        stack.push_front(v);
        for (int w : G.getadj(v)) {
            if (!marked[w]) dfs(G, w);
            if (low[w] < min) min = low[w];
        }
        if (min < low[v]) {
            low[v] = min;
            return;
        }
        int w;
        do {
            w = stack.front();
            stack.pop_front();
            id[w] = count;
            low[w] = G.getV();
        } while (w != v);
        count++;
    }

    // throw an IllegalArgumentException unless {@code 0 <= v < V}
    void validateVertex(int v) {
        int V = marked.size();
        if (v < 0 || v >= V)
            throw runtime_error("vertex " + to_string(v) + " is not between 0 and " + to_string(V - 1));
    }

private:
    vector<bool> marked;    // marked[v] = has v been visited?
    vector<int> id;         // id[v] = id of strong component containing v
    vector<int> low;        // low[v] = low number of v
    int pre;                // preorder number counter
    int count;              // number of strongly-connected components
    forward_list<int> stack;
};

#endif //CH4_TARJANSCC_H
