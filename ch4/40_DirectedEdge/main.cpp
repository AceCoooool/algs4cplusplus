#include <iostream>
#include "../head/DirectedEdge.h"

using namespace std;

/**
 * Unit tests the {@code DirectedEdge} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    DirectedEdge e(12, 34, 5.67);
    cout << e << endl;
}