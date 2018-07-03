#include <iostream>
#include "../head/GraphGenerator.h"
#include "../head/EulerianPath.h"

// TODO: there is a bug
using namespace std;

/**
 * Unit tests the {@code EulerianPath} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int V = 5;
    int E = 6;

    // Eulerian cycle
    Graph G1 = GraphGenerator::eulerianCycle(V, E);
    EulerianPath::unitTest(G1, "Eulerian cycle");

    // Eulerian path
    Graph G2 = GraphGenerator::eulerianPath(V, E);
    EulerianPath::unitTest(G2, "Eulerian path");

    uniform_int_distribution<> dis(0, V-1);
    // add one random edge
    Graph G3(G2);
    G3.addEdge(dis(g), dis(g));
    EulerianPath::unitTest(G3, "one random edge added to Eulerian path");

    // self loop
    Graph G4(V);
    int v4 = dis(g);
    G4.addEdge(v4, v4);
    EulerianPath::unitTest(G4, "single self loop");

    // single edge
    Graph G5(V);
    G5.addEdge(dis(g), dis(g));
    EulerianPath::unitTest(G5, "single edge");

    // empty graph
    Graph G6(V);
    EulerianPath::unitTest(G6, "empty graph");

    // random graph
    Graph G7 = GraphGenerator::simple(V, E);
    EulerianPath::unitTest(G7, "simple graph");
}