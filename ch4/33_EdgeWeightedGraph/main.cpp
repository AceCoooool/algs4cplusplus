#include <iostream>
#include "../head/EdgeWeightedGraph.h"

using namespace std;

/**
 * Unit tests the {@code EdgeWeightedGraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWG.txt";
    EdgeWeightedGraph G(file);
    cout << G << endl;
}