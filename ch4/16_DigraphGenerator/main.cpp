#include <iostream>
#include "../head/DigraphGenerator.h"

using namespace std;

/**
 * Unit tests the {@code Digraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int V = 6;
    int E = 8;

    cout << "complete graph" << endl;
    cout << *(DigraphGenerator::complete(V)) << endl;
    cout << endl;

    cout << "simple graph" << endl;
    cout << *(DigraphGenerator::simple(V, E)) << endl;
    cout << endl;

    cout << "path graph" << endl;
    cout << *(DigraphGenerator::path(V)) << endl;
    cout << endl;

    cout << "cycle graph" << endl;
    cout << *(DigraphGenerator::cycle(V)) << endl;
    cout << endl;

    cout << "Eulierian path graph" << endl;
    cout << *(DigraphGenerator::eulerianPath(V, E)) << endl;
    cout << endl;

    cout << "Eulierian cycle graph" << endl;
    cout << *(DigraphGenerator::eulerianCycle(V, E)) << endl;
    cout << endl;

    cout << "binary tree graph" << endl;
    cout << *(DigraphGenerator::binaryTree(V)) << endl;
    cout << endl;

    cout << "tournament graph" << endl;
    cout << *(DigraphGenerator::tournament(V)) << endl;
    cout << endl;

    cout << "DAG graph" << endl;
    cout << *(DigraphGenerator::dag(V, E)) << endl;
    cout << endl;

    cout << "rooted-in DAG graph" << endl;
    cout << *(DigraphGenerator::rootedInDAG(V, E)) << endl;
    cout << endl;

    cout << "rooted-out DAG graph" << endl;
    cout << *(DigraphGenerator::rootedOutDAG(V, E)) << endl;
    cout << endl;

    cout << "rooted-in Tree graph" << endl;
    cout << *(DigraphGenerator::rootedInTree(V)) << endl;
    cout << endl;

    cout << "rooted-out Tree graph" << endl;
    cout << *(DigraphGenerator::rootedOutTree(V)) << endl;
    cout << endl;
}