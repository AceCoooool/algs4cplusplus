#include <iostream>
#include "../head/DirectedCycleX.h"
#include "../head/DigraphGenerator.h"

using namespace std;

/**
 * Unit tests the {@code DirectedCycleX} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    // create random DAG with V vertices and E edges; then add F random edges
    int V = 8;
    int E = 9;
    int F = 3;
    Digraph *G = DigraphGenerator::dag(V, E);

    // add F extra edges
    uniform_int_distribution<> dis(0, V - 1);
    for (int i = 0; i < F; ++i) {
        int v = dis(g);
        int w = dis(g);
        G->addEdge(v, w);
    }
    cout << *G << endl;

    DirectedCycleX finder(*G);
    if (finder.hasCycle()) {
        cout << "Directed cycle: ";
        for (auto v: finder.getcycle())
            cout << v << " ";
        cout << endl;
    } else {
        cout << "No directed cycle" << endl;
    }
    cout << endl;
}