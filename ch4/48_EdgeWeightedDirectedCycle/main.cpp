#include <iostream>
#include "../head/EdgeWeightedDirectedCycle.h"
#include <algorithm>

using namespace std;

/**
 * Unit tests the {@code DijkstraSP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    // create random DAG with V vertices and E edges; then add F random edges
    int V = 8;
    int E = 8;
    int F = 2;
    EdgeWeightedDigraph G(V);
    vector<int> vertices(V);
    for (int i = 0; i < V; i++)
        vertices[i] = i;
    shuffle(vertices.begin(), vertices.end(), g);
    uniform_int_distribution<> dis(0, V - 1);
    uniform_real_distribution<double> dis1(0, 1);
    for (int i = 0; i < E; i++) {
        int v, w;
        do {
            v = dis(g);
            w = dis(g);
        } while (v >= w);
        double weight = dis1(g);
        G.addEdge(DirectedEdge(v, w, weight));
    }

    // add F extra edges
    for (int i = 0; i < F; i++) {
        int v = dis(g);
        int w = dis(g);
        double weight = dis1(g);
        G.addEdge(DirectedEdge(v, w, weight));
    }

    cout << G << endl;

    // find a directed cycle
    EdgeWeightedDirectedCycle finder(G);
    if (finder.hasCycle()) {
        cout << "Cycle: ";
        for (DirectedEdge e : finder.cycle_()) {
            cout << e << " ";
        }
        cout << endl;
    } else {   // or give topologial sort
        cout << "No directed cycle" << endl;
    }
}