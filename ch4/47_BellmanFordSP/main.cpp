#include <iostream>
#include "../head/BellmanFordSP.h"

using namespace std;

/**
 * Unit tests the {@code BellmanFordSP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWDn.txt";
    EdgeWeightedDigraph G(file);

    int s = 0;

    BellmanFordSP sp(G, s);

    if (sp.hasNegativeCycle()) {
        for (auto e: sp.negativeCycle())
            cout << e << endl;
    } else {
        for (int v = 0; v < G.V_(); ++v) {
            if (sp.hasPathTo(v)) {
                cout << s << " to " << v << fixed << setprecision(2) << " (" << sp.distTo_(v) << ")  ";
                for (auto e: sp.pathTo(v))
                    cout << e << " ";
                cout << endl;
            } else {
                cout << s << " to " << v << "   no path" << endl;
            }
        }
    }
}