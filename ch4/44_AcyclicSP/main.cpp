#include <iostream>
#include "../head/AcyclicSP.h"

using namespace std;

/**
 * Unit tests the {@code AcyclicSP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWDAG.txt";
    EdgeWeightedDigraph G(file);

    int s = 5;
    AcyclicSP asp(G, s);

    for (int v = 0; v < G.V_(); ++v) {
        if (asp.hasPathTo(v)) {
            cout << s << " to " << v << " (" << asp.distTo_(v) << ") ";
            for (auto e: asp.pathTo(v))
                cout << e << " ";
            cout << endl;
        } else
            cout << s << " to " << v << "  no path" << endl;
    }
}