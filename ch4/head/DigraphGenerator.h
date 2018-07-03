#ifndef CH4_DIGRAPHGENERATOR_H
#define CH4_DIGRAPHGENERATOR_H

#include "../head/Digraph.h"
#include <set>
#include <random>
#include <algorithm>

std::random_device rd;
std::mt19937 g(rd());
using std::set;
using std::uniform_int_distribution;
using std::bernoulli_distribution;
using std::shuffle;

/**
 *  The {@code DigraphGenerator} class provides static methods for creating
 *  various digraphs, including Erdos-Renyi random digraphs, random DAGs,
 *  random rooted trees, random rooted DAGs, random tournaments, path digraphs,
 *  cycle digraphs, and the complete digraph.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/42digraph">Section 4.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class DigraphGenerator {
public:
    DigraphGenerator() = delete;

    /**
      * Returns a random simple digraph containing {@code V} vertices and {@code E} edges.
      * @param V the number of vertices
      * @param E the number of vertices
      * @return a random simple digraph on {@code V} vertices, containing a total
      *     of {@code E} edges
      * @throws IllegalArgumentException if no such simple digraph exists
      */
    static Digraph *simple(int V, int E) {
        if (E > (long) V * (V - 1)) throw runtime_error("Too many edges");
        if (E < 0) throw runtime_error("Too few edges");
        Digraph *G = new Digraph(V);
        set<Edge> set1;
        uniform_int_distribution<> dis(0, V - 1);
        while (G->getE() < E) {
            int v = dis(g);
            int w = dis(g);
            Edge e(v, w);
            if ((v != w) && set1.find(e) == set1.end()) {
                set1.insert(e);
                G->addEdge(v, w);
            }
        }
        return G;
    }

    /**
     * Returns a random simple digraph on {@code V} vertices, with an
     * edge between any two vertices with probability {@code p}. This is sometimes
     * referred to as the Erdos-Renyi random digraph model.
     * This implementations takes time propotional to V^2 (even if {@code p} is small).
     * @param V the number of vertices
     * @param p the probability of choosing an edge
     * @return a random simple digraph on {@code V} vertices, with an edge between
     *     any two vertices with probability {@code p}
     * @throws IllegalArgumentException if probability is not between 0 and 1
     */
    static Digraph *simple(int V, double p) {
        if (p < 0.0 || p > 1.0)
            throw runtime_error("Probability must be between 0 and 1");
        Digraph *G = new Digraph(V);
        bernoulli_distribution dis(p);
        for (int v = 0; v < V; v++)
            for (int w = 0; w < V; w++)
                if (v != w)
                    if (dis(g))
                        G->addEdge(v, w);
        return G;
    }

    /**
     * Returns the complete digraph on {@code V} vertices.
     * @param V the number of vertices
     * @return the complete digraph on {@code V} vertices
     */
    static Digraph *complete(int V) {
        return simple(V, V * (V - 1));
    }

    /**
     * Returns a random simple DAG containing {@code V} vertices and {@code E} edges.
     * Note: it is not uniformly selected at random among all such DAGs.
     * @param V the number of vertices
     * @param E the number of vertices
     * @return a random simple DAG on {@code V} vertices, containing a total
     *     of {@code E} edges
     * @throws IllegalArgumentException if no such simple DAG exists
     */
    static Digraph *dag(int V, int E) {
        if (E > (long) V * (V - 1) / 2) throw runtime_error("Too many edges");
        if (E < 0) throw runtime_error("Too few edges");
        Digraph *G = new Digraph(V);
        set<Edge> set1;
        uniform_int_distribution<> dis(0, V - 1);
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), g);
        while (G->getE() < E) {
            int v = dis(g);
            int w = dis(g);
            Edge e(v, w);
            if ((v < w) && set1.find(e) == set1.end()) {
                set1.insert(e);
                G->addEdge(vertices[v], vertices[w]);
            }
        }
        return G;
    }

    // tournament
    /**
     * Returns a random tournament digraph on {@code V} vertices. A tournament digraph
     * is a DAG in which for every two vertices, there is one directed edge.
     * A tournament is an oriented complete graph.
     * @param V the number of vertices
     * @return a random tournament digraph on {@code V} vertices
     */
    static Digraph *tournament(int V) {
        Digraph *G = new Digraph(V);
        bernoulli_distribution dis(0.5);
        for (int v = 0; v < G->getV(); v++) {
            for (int w = v + 1; w < G->getV(); w++) {
                if (dis(g)) G->addEdge(v, w);
                else G->addEdge(w, v);
            }
        }
        return G;
    }

    /**
     * Returns a random rooted-in DAG on {@code V} vertices and {@code E} edges.
     * A rooted in-tree is a DAG in which there is a single vertex
     * reachable from every other vertex.
     * The DAG returned is not chosen uniformly at random among all such DAGs.
     * @param V the number of vertices
     * @param E the number of edges
     * @return a random rooted-in DAG on {@code V} vertices and {@code E} edges
     */
    static Digraph *rootedInDAG(int V, int E) {
        if (E > (long) V * (V - 1) / 2) throw runtime_error("Too many edges");
        if (E < V - 1) throw runtime_error("Too few edges");
        Digraph *G = new Digraph(V);
        set<Edge> set1;

        // fix a topological order
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), g);

        // one edge pointing from each vertex, other than the root = vertices[V-1]
        for (int v = 0; v < V - 1; v++) {
            uniform_int_distribution<> dis(v + 1, V - 1);
            int w = dis(g);
            Edge e(v, w);
            set1.insert(e);
            G->addEdge(vertices[v], vertices[w]);
        }

        uniform_int_distribution<> dis(0, V - 1);
        while (G->getE() < E) {
            int v = dis(g);
            int w = dis(g);
            Edge e(v, w);
            if ((v < w) && set1.find(e) == set1.end()) {
                set1.insert(e);
                G->addEdge(vertices[v], vertices[w]);
            }
        }
        return G;
    }

    /**
     * Returns a random rooted-out DAG on {@code V} vertices and {@code E} edges.
     * A rooted out-tree is a DAG in which every vertex is reachable from a
     * single vertex.
     * The DAG returned is not chosen uniformly at random among all such DAGs.
     * @param V the number of vertices
     * @param E the number of edges
     * @return a random rooted-out DAG on {@code V} vertices and {@code E} edges
     */
    static Digraph *rootedOutDAG(int V, int E) {
        if (E > (long) V * (V - 1) / 2) throw runtime_error("Too many edges");
        if (E < V - 1) throw runtime_error("Too few edges");
        Digraph *G = new Digraph(V);
        set<Edge> set1;

        // fix a topological order
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), g);

        // one edge pointing from each vertex, other than the root = vertices[V-1]
        for (int v = 0; v < V - 1; v++) {
            uniform_int_distribution<> dis(v + 1, V - 1);
            int w = dis(g);
            Edge e(w, v);
            set1.insert(e);
            G->addEdge(vertices[w], vertices[v]);
        }

        uniform_int_distribution<> dis(0, V - 1);
        while (G->getE() < E) {
            int v = dis(g);
            int w = dis(g);
            Edge e(w, v);
            if ((v < w) && set1.find(e) == set1.end()) {
                set1.insert(e);
                G->addEdge(vertices[w], vertices[v]);
            }
        }
        return G;
    }

    /**
     * Returns a random rooted-in tree on {@code V} vertices.
     * A rooted in-tree is an oriented tree in which there is a single vertex
     * reachable from every other vertex.
     * The tree returned is not chosen uniformly at random among all such trees.
     * @param V the number of vertices
     * @return a random rooted-in tree on {@code V} vertices
     */
    static Digraph *rootedInTree(int V) {
        return rootedInDAG(V, V - 1);
    }

    /**
     * Returns a random rooted-out tree on {@code V} vertices. A rooted out-tree
     * is an oriented tree in which each vertex is reachable from a single vertex.
     * It is also known as a <em>arborescence</em> or <em>branching</em>.
     * The tree returned is not chosen uniformly at random among all such trees.
     * @param V the number of vertices
     * @return a random rooted-out tree on {@code V} vertices
     */
    static Digraph *rootedOutTree(int V) {
        return rootedOutDAG(V, V - 1);
    }

    /**
     * Returns a path digraph on {@code V} vertices.
     * @param V the number of vertices in the path
     * @return a digraph that is a directed path on {@code V} vertices
     */
    static Digraph *path(int V) {
        Digraph *G = new Digraph(V);
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), g);
        for (int i = 0; i < V - 1; i++) {
            G->addEdge(vertices[i], vertices[i + 1]);
        }
        return G;
    }

    /**
     * Returns a complete binary tree digraph on {@code V} vertices.
     * @param V the number of vertices in the binary tree
     * @return a digraph that is a complete binary tree on {@code V} vertices
     */
    static Digraph *binaryTree(int V) {
        Digraph *G = new Digraph(V);
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), g);
        for (int i = 1; i < V; i++) {
            G->addEdge(vertices[i], vertices[(i - 1) / 2]);
        }
        return G;
    }

    /**
     * Returns a cycle digraph on {@code V} vertices.
     * @param V the number of vertices in the cycle
     * @return a digraph that is a directed cycle on {@code V} vertices
     */
    static Digraph *cycle(int V) {
        Digraph *G = new Digraph(V);
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        shuffle(vertices.begin(), vertices.end(), g);
        for (int i = 0; i < V - 1; i++) {
            G->addEdge(vertices[i], vertices[i + 1]);
        }
        G->addEdge(vertices[V - 1], vertices[0]);
        return G;
    }

    /**
     * Returns an Eulerian cycle digraph on {@code V} vertices.
     *
     * @param  V the number of vertices in the cycle
     * @param  E the number of edges in the cycle
     * @return a digraph that is a directed Eulerian cycle on {@code V} vertices
     *         and {@code E} edges
     * @throws IllegalArgumentException if either {@code V <= 0} or {@code E <= 0}
     */
    static Digraph *eulerianCycle(int V, int E) {
        if (E <= 0)
            throw runtime_error("An Eulerian cycle must have at least one edge");
        if (V <= 0)
            throw runtime_error("An Eulerian cycle must have at least one vertex");
        Digraph *G = new Digraph(V);
        uniform_int_distribution<> dis(0, V - 1);
        vector<int> vertices(E);
        for (int i = 0; i < E; i++)
            vertices[i] = dis(g);
        for (int i = 0; i < E - 1; i++) {
            G->addEdge(vertices[i], vertices[i + 1]);
        }
        G->addEdge(vertices[E - 1], vertices[0]);
        return G;
    }

    /**
     * Returns an Eulerian path digraph on {@code V} vertices.
     *
     * @param  V the number of vertices in the path
     * @param  E the number of edges in the path
     * @return a digraph that is a directed Eulerian path on {@code V} vertices
     *         and {@code E} edges
     * @throws IllegalArgumentException if either {@code V <= 0} or {@code E < 0}
     */
    static Digraph *eulerianPath(int V, int E) {
        if (E < 0)
            throw runtime_error("negative number of edges");
        if (V <= 0)
            throw runtime_error("An Eulerian path must have at least one vertex");
        Digraph *G = new Digraph(V);
        vector<int> vertices(E + 1);
        uniform_int_distribution<> dis(0, V - 1);
        for (int i = 0; i < E + 1; i++)
            vertices[i] = dis(g);
        for (int i = 0; i < E; i++) {
            G->addEdge(vertices[i], vertices[i + 1]);
        }
        return G;
    }

    /**
     * Returns a random simple digraph on {@code V} vertices, {@code E}
     * edges and (at least) {@code c} strong components. The vertices are randomly
     * assigned integer labels between {@code 0} and {@code c-1} (corresponding to
     * strong components). Then, a strong component is creates among the vertices
     * with the same label. Next, random edges (either between two vertices with
     * the same labels or from a vetex with a smaller label to a vertex with a
     * larger label). The number of components will be equal to the number of
     * distinct labels that are assigned to vertices.
     *
     * @param V the number of vertices
     * @param E the number of edges
     * @param c the (maximum) number of strong components
     * @return a random simple digraph on {@code V} vertices and
               {@code E} edges, with (at most) {@code c} strong components
     * @throws IllegalArgumentException if {@code c} is larger than {@code V}
     */
    static Digraph *strong(int V, int E, int c) {
        if (c >= V || c <= 0)
            throw runtime_error("Number of components must be between 1 and V");
        if (E <= 2 * (V - c))
            throw runtime_error("Number of edges must be at least 2(V-c)");
        if (E > (long) V * (V - 1) / 2)
            throw runtime_error("Too many edges");

        // the digraph
        Digraph *G = new Digraph(V);

        // edges added to G (to avoid duplicate edges)
        set<Edge> set1;

        vector<int> label(V);
        uniform_int_distribution<> dis(0, c - 1);
        for (int v = 0; v < V; v++)
            label[v] = dis(g);

        // make all vertices with label c a strong component by
        // combining a rooted in-tree and a rooted out-tree
        for (int i = 0; i < c; i++) {
            // how many vertices in component c
            int count = 0;
            for (int v = 0; v < G->getV(); v++) {
                if (label[v] == i) count++;
            }

            // if (count == 0) System.err.println("less than desired number of strong components");

            vector<int> vertices(count);
            int j = 0;
            for (int v = 0; v < V; v++) {
                if (label[v] == i) vertices[j++] = v;
            }
            shuffle(vertices.begin(), vertices.end(), g);

            // rooted-in tree with root = vertices[count-1]
            for (int v = 0; v < count - 1; v++) {
                uniform_int_distribution<> dis(v + 1, count - 1);
                int w = dis(g);
                Edge e(w, v);
                set1.insert(e);
                G->addEdge(vertices[w], vertices[v]);
            }

            // rooted-out tree with root = vertices[count-1]
            for (int v = 0; v < count - 1; v++) {
                uniform_int_distribution<> dis(v + 1, count - 1);
                int w = dis(g);
                Edge e(v, w);
                set1.insert(e);
                G->addEdge(vertices[v], vertices[w]);
            }
        }

        uniform_int_distribution<> dis2(0, V - 1);
        while (G->getE() < E) {
            int v = dis2(g);
            int w = dis2(g);
            Edge e(v, w);
            if (set1.find(e) == set1.end() && v != w && label[v] <= label[w]) {
                set1.insert(e);
                G->addEdge(v, w);
            }
        }

        return G;
    }

public:
    class Edge {
    public:
        Edge(int v_, int w_) : v(v_), w(w_) {}

        friend bool operator<(const Edge &e1, const Edge &e2) {
            if (e1.v < e2.v) return true;
            if (e1.v > e2.v) return false;
            if (e1.w < e2.w) return true;
            if (e1.w > e2.w) return false;
            return false;
        }

        friend bool operator==(const Edge &e1, const Edge &e2) {
            if (e1.v == e2.v && e1.w == e2.w) return true;
            else return false;
        }

    private:
        int v, w;
    };

private:
};

#endif //CH4_DIGRAPHGENERATOR_H
