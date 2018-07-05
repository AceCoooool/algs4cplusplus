#include <iostream>
#include "../head/AdjMatrixEdgeWeightedDigraph.h"

using namespace std;

/**
 * Unit tests the {@code AdjMatrixEdgeWeightedDigraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    int V = 5;
    int E = 6;
    AdjMatrixEdgeWeightedDigraph G(V, E);
    cout << G << endl;
}