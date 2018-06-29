#include <iostream>
#include <queue>
#include "../head/GraphGenerator.h"
#include "../head/BipartiteX.h"

using namespace std;

/**
 * Unit tests the {@code Bipartite} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int V1 = 5;
    int V2 = 8;
    int E = 4;
    int F = 6;
    // create random bipartite graph with V1 vertices on left side,
    // V2 vertices on right side, and E edges; then add F random edges
    Graph G = GraphGenerator::bipartite(V1, V2, E);
    uniform_int_distribution<> dis(0, V1 + V2 - 1);
    for (int i = 0; i < F; ++i) {
        int v = dis(g);
        int w = dis(g);
        G.addEdge(v, w);
    }

    cout << G << endl;
    BipartiteX b(G);
    if (b.getisBipartite()) {
        cout << "Graph is bipartite" << endl;
        for (int v = 0; v < G.getV(); ++v) {
            cout << v << " : " << b.getcolor(v) << endl;
        }
    } else {
        cout << "Graph has an odd-length cycle: ";
        auto odd = b.oddCycle();
        while (!odd.empty()) {
            cout << odd.front() << " ";
            odd.pop();
        }
    }
}