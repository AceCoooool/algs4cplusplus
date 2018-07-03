#include <iostream>
#include "../head/DirectedEulerianCycle.h"
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
    DirectedEulerianCycle::unitTest(*G1, "Eulerian cycle");

    // Eulerian path
    Digraph *G2 = DigraphGenerator::eulerianPath(V, E);
    DirectedEulerianCycle::unitTest(*G2, "Eulerian path");

    // empty digraph
    Digraph *G3 = new Digraph(V);
    DirectedEulerianCycle::unitTest(*G3, "empty digraph");

    uniform_int_distribution<> dis(0, V-1);
    // self loop
    Digraph *G4 = new Digraph(V);
    int v4 = dis(g);
    G4->addEdge(v4, v4);
    DirectedEulerianCycle::unitTest(*G4, "single self loop");

    // union of two disjoint cycles
    Digraph *H1 = DigraphGenerator::eulerianCycle(V/2, E/2);
    Digraph *H2 = DigraphGenerator::eulerianCycle(V - V/2, E - E/2);
    vector<int> perm(V);
    for (int i = 0; i < V; i++)
        perm[i] = i;
    shuffle(perm.begin(), perm.end(), g);
    Digraph *G5 = new Digraph(V);
    for (int v = 0; v < H1->getV(); v++)
        for (int w : H1->getadj(v))
            G5->addEdge(perm[v], perm[w]);
    for (int v = 0; v < H2->getV(); v++)
        for (int w : H2->getadj(v))
            G5->addEdge(perm[V/2 + v], perm[V/2 + w]);
    DirectedEulerianCycle::unitTest(*G5, "Union of two disjoint cycles");

    // random digraph
    Digraph *G6 = DigraphGenerator::simple(V, E);
    DirectedEulerianCycle::unitTest(*G6, "simple digraph");

    // 4-vertex digraph
    Digraph *G7 = new Digraph("/home/ace/AceDev/C++/algorithm/ch4/data/eulerianD.txt");
    DirectedEulerianCycle::unitTest(*G7, "4-vertex Eulerian digraph");
}