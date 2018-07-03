#include <iostream>
#include "../head/DirectedEulerianPath.h"
#include "../head/DigraphGenerator.h"

using namespace std;

/**
 * Unit tests the {@code DirectedEulerianCycle} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int V = 8;
    int E = 8;

    // Eulerian cycle
    Digraph *G1 = DigraphGenerator::eulerianCycle(V, E);
    DirectedEulerianPath::unitTest(*G1, "Eulerian cycle");

    // Eulerian path
    Digraph *G2 = DigraphGenerator::eulerianPath(V, E);
    DirectedEulerianPath::unitTest(*G2, "Eulerian path");

    uniform_int_distribution<> dis(0, V-1);
    // add one random edge
    Digraph G3(*G2);
    G3.addEdge(dis(g), dis(g));
    DirectedEulerianPath::unitTest(G3, "one random edge added to Eulerian path");

    // self loop
    Digraph *G4 = new Digraph(V);
    int v4 = dis(g);
    G4->addEdge(v4, v4);
    DirectedEulerianPath::unitTest(*G4, "single self loop");

    // single edge
    Digraph *G5 = new Digraph(V);
    G5->addEdge(dis(g), dis(g));
    DirectedEulerianPath::unitTest(*G5, "single edge");

    // empty digraph
    Digraph *G6 = new Digraph(V);
    DirectedEulerianPath::unitTest(*G6, "empty digraph");

    // random digraph
    Digraph *G7 = DigraphGenerator::simple(V, E);
    DirectedEulerianPath::unitTest(*G7, "simple digraph");

    // 4-vertex digraph
    Digraph *G8 = new Digraph("/home/ace/AceDev/C++/algorithm/ch4/data/eulerianD.txt");
    DirectedEulerianPath::unitTest(*G8, "4-vertex Eulerian digraph");
}