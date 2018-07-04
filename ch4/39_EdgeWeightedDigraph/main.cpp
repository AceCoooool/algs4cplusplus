#include <iostream>
#include "../head/EdgeWeightedDigraph.h"

using namespace std;

/**
 * Unit tests the {@code EdgeWeightedDigraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWG.txt";
    EdgeWeightedDigraph G(filename);
    cout << G << endl;
}