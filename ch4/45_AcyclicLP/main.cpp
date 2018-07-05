#include <iostream>
#include "../head/AcyclicLP.h"

using namespace std;

/**
 * Unit tests the {@code AcyclicLP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWDAG.txt";
    EdgeWeightedDigraph G(file);

    int s = 5;
    AcyclicLP alp(G, s);

    for (int v = 0; v < G.V_(); ++v) {
        if (alp.hasPathTo(v)) {
            cout << s << " to " << v << " (" << alp.distTo_(v) << ") ";
            for (auto e: alp.pathTo(v))
                cout << e << " ";
            cout << endl;
        } else
            cout << s << " to " << v << "  no path" << endl;
    }
}