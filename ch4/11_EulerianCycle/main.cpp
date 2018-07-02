#include <iostream>
#include "../head/GraphGenerator.h"
#include "../head/EulerianCycle.h"
#include "../head/EulerianPath.h"

// TODO: there is a bug
using namespace std;

/**
 * Unit tests the {@code Cycle} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int V = 5;
    int E = 6;

    // Eulerian cycle
    Graph G1 = GraphGenerator::eulerianCycle(V, E);
    EulerianCycle::unitTest(G1, "Eulerian cycle");

    // Eulerian path
    Graph G2 = GraphGenerator::eulerianPath(V, E);
    EulerianPath::unitTest(G2, "Eulerian path");

    // empty graph
    Graph G3(V);
    EulerianCycle::unitTest(G3, "empty graph");

    uniform_int_distribution<> dis(0, V-1);
    // self loop
    Graph G4(V);
    int v4 = dis(g);
    G4.addEdge(v4, v4);
    EulerianCycle::unitTest(G4, "single self loop");

    // union of two disjoint cycles
    Graph H1 = GraphGenerator::eulerianCycle(V/2, E/2);
    Graph H2 = GraphGenerator::eulerianCycle(V - V/2, E - E/2);
    vector<int> perm(V);
    for (int i = 0; i < V; i++)
        perm[i] = i;
    std::shuffle(perm.begin(), perm.end(), g);
    Graph G5(V);
    for (int v = 0; v < H1.getV(); v++)
        for (int w : H1.getadj(v))
            G5.addEdge(perm[v], perm[w]);
    for (int v = 0; v < H2.getV(); v++)
        for (int w : H2.getadj(v))
            G5.addEdge(perm[V/2 + v], perm[V/2 + w]);
    EulerianCycle::unitTest(G5, "Union of two disjoint cycles");

    // random digraph
    Graph G6 = GraphGenerator::simple(V, E);
    EulerianCycle::unitTest(G6, "simple graph");
}