#ifndef CH4_GRAPHGENERATOR_H
#define CH4_GRAPHGENERATOR_H

#include <set>
#include <random>
#include <algorithm>
#include "../head/Graph.h"

std::random_device rd;
std::mt19937 g(rd());
using std::uniform_int_distribution;
using std::bernoulli_distribution;
using std::set;

/**
 *  The {@code GraphGenerator} class provides static methods for creating
 *  various graphs, including Erdos-Renyi random graphs, random bipartite
 *  graphs, random k-regular graphs, and random rooted trees.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/41graph">Section 4.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class GraphGenerator {
public:
    GraphGenerator() = delete;


public:
    /**
     * Returns a random simple graph containing {@code V} vertices and {@code E} edges.
     * @param V the number of vertices
     * @param E the number of vertices
     * @return a random simple graph on {@code V} vertices, containing a total
     *     of {@code E} edges
     * @throws IllegalArgumentException if no such simple graph exists
     */
    static Graph simple(int V, int E) {
        if (E > (long) V * (V - 1) / 2) throw runtime_error("Too many edges");
        if (E < 0) throw runtime_error("Too few edges");
        Graph G(V);
        uniform_int_distribution<> dis(0, V - 1);
        set<Edge> set_;
        while (G.getE() < E) {
            int v = dis(g);
            int w = dis(g);
            Edge e(v, w);
            if ((v != w) && set_.find(e) == set_.end()) {
                set_.insert(e);
                G.addEdge(v, w);
            }
        }
        return G;
    }

    /**
     * Returns a random simple graph on {@code V} vertices, with an
     * edge between any two vertices with probability {@code p}. This is sometimes
     * referred to as the Erdos-Renyi random graph model.
     * @param V the number of vertices
     * @param p the probability of choosing an edge
     * @return a random simple graph on {@code V} vertices, with an edge between
     *     any two vertices with probability {@code p}
     * @throws IllegalArgumentException if probability is not between 0 and 1
     */
    static Graph simple(int V, double p) {
        if (p < 0.0 || p > 1.0)
            throw runtime_error("Probability must be between 0 and 1");
        Graph G(V);
        bernoulli_distribution dis(p);
        for (int v = 0; v < V; v++)
            for (int w = v + 1; w < V; w++)
                if (dis(g))
                    G.addEdge(v, w);
        return G;
    }

    /**
     * Returns the complete graph on {@code V} vertices.
     * @param V the number of vertices
     * @return the complete graph on {@code V} vertices
     */
    static Graph complete(int V) {
        return simple(V, 1.0);
    }

    /**
     * Returns a random simple bipartite graph on {@code V1} and {@code V2} vertices
     * with {@code E} edges.
     * @param V1 the number of vertices in one partition
     * @param V2 the number of vertices in the other partition
     * @param E the number of edges
     * @return a random simple bipartite graph on {@code V1} and {@code V2} vertices,
     *    containing a total of {@code E} edges
     * @throws IllegalArgumentException if no such simple bipartite graph exists
     */
    static Graph bipartite(int V1, int V2, int E) {
        if (E > (long) V1 * V2) throw runtime_error("Too many edges");
        if (E < 0) throw runtime_error("Too few edges");
        Graph G(V1 + V2);

        vector<int> vertices(V1 + V2);
        for (int i = 0; i < V1 + V2; i++)
            vertices[i] = i;
        std::shuffle(vertices.begin(), vertices.end(), g);
        uniform_int_distribution<> dis1(0, V1 - 1);
        uniform_int_distribution<> dis2(0, V2 - 1);
        set<Edge> set_;
        while (G.getE() < E) {
            int i = dis1(g);
            int j = V1 + dis2(g);
            Edge e(vertices[i], vertices[j]);
            if (set_.find(e) == set_.end()) {
                set_.insert(e);
                G.addEdge(vertices[i], vertices[j]);
            }
        }
        return G;
    }

    /**
     * Returns a random simple bipartite graph on {@code V1} and {@code V2} vertices,
     * containing each possible edge with probability {@code p}.
     * @param V1 the number of vertices in one partition
     * @param V2 the number of vertices in the other partition
     * @param p the probability that the graph contains an edge with one endpoint in either side
     * @return a random simple bipartite graph on {@code V1} and {@code V2} vertices,
     *    containing each possible edge with probability {@code p}
     * @throws IllegalArgumentException if probability is not between 0 and 1
     */
    static Graph bipartite(int V1, int V2, double p) {
        if (p < 0.0 || p > 1.0)
            throw runtime_error("Probability must be between 0 and 1");
        vector<int> vertices(V1 + V2);
        for (int i = 0; i < V1 + V2; i++)
            vertices[i] = i;
        std::shuffle(vertices.begin(), vertices.end(), g);
        bernoulli_distribution dis(p);
        Graph G(V1 + V2);
        for (int i = 0; i < V1; i++)
            for (int j = 0; j < V2; j++)
                if (dis(g))
                    G.addEdge(vertices[i], vertices[V1 + j]);
        return G;
    }

    /**
     * Returns a complete bipartite graph on {@code V1} and {@code V2} vertices.
     * @param V1 the number of vertices in one partition
     * @param V2 the number of vertices in the other partition
     * @return a complete bipartite graph on {@code V1} and {@code V2} vertices
     * @throws IllegalArgumentException if probability is not between 0 and 1
     */
    static Graph completeBipartite(int V1, int V2) {
        return bipartite(V1, V2, V1 * V2);
    }

    /**
     * Returns a path graph on {@code V} vertices.
     * @param V the number of vertices in the path
     * @return a path graph on {@code V} vertices
     */
    static Graph path(int V) {
        Graph G(V);
        vector<int> vertices(V);
        for (int i = 0; i < V; i++)
            vertices[i] = i;
        std::shuffle(vertices.begin(), vertices.end(), g);
        for (int i = 0; i < V - 1; i++) {
            G.addEdge(vertices[i], vertices[i + 1]);
        }
        return G;
    }


public:
    class Edge {
    public:
        Edge(int v_, int w_) : v(v_), w(w_) {
            if (v > w)
                std::swap(v, w);
        }

        friend bool operator<(const Edge &e1, const Edge &e2) {
            if (e1.v < e2.v) return true;
            if (e1.v >= e2.v) return false;
            if (e1.w < e2.w) return true;
            if (e1.w >= e2.w) return false;
            return false;
        }

    private:
        int v, w;
    };

};

#endif //CH4_GRAPHGENERATOR_H
