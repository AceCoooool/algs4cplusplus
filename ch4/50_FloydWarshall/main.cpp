#include <iostream>
#include "../head/FloydWarshall.h"

using namespace std;

/**
 * Unit tests the {@code FloydWarshall} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    // random graph with V vertices and E edges, parallel edges allowed
    int V = 5;
    int E = 3;
    AdjMatrixEdgeWeightedDigraph G(V);
    uniform_int_distribution<> dis(0, V - 1);
    uniform_real_distribution<double> dis1(0, 1);
    for (int i = 0; i < E; i++) {
        int v = dis(g);
        int w = dis(g);
        double weight = round(100 * (dis1(g) - 0.15)) / 100.0;
        if (v == w) G.addEdge(DirectedEdge(v, w, abs(weight)));
        else G.addEdge(DirectedEdge(v, w, weight));
    }

    cout << G << endl;

    // run Floyd-Warshall algorithm
    FloydWarshall spt(G);

    // print all-pairs shortest path distances
    cout << "  ";
    for (int v = 0; v < G.V_(); v++) {
        cout << v << "  ";
    }
    cout << endl;
    for (int v = 0; v < G.V_(); v++) {
        cout << v << " : ";
        for (int w = 0; w < G.V_(); w++) {
            if (spt.hasPath(v, w))
                cout << spt.dist(v, w) << "  ";
            else cout << "  Inf ";
        }
        cout << endl;
    }

    // print negative cycle
    if (spt.hasNegativeCycle_()) {
        cout << "Negative cost cycle:" << endl;
        for (DirectedEdge e : spt.negativeCycle())
            cout << e << endl;
        cout << endl;
    }

        // print all-pairs shortest paths
    else {
        for (int v = 0; v < G.V_(); v++) {
            for (int w = 0; w < G.V_(); w++) {
                if (spt.hasPath(v, w)) {
                    cout << v << " to " << w << " (" << spt.dist(v, w) << " )";
                    for (DirectedEdge e : spt.path(v, w))
                        cout << e << " ";
                    cout << endl;
                } else {
                    cout << v << " to " << w << "   no path" << endl;
                }
            }
        }
    }
}