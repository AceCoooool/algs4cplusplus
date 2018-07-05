#include <iostream>
#include "../head/DijkstraSP.h"

using namespace std;

/**
 * Unit tests the {@code DijkstraSP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWD.txt";
    EdgeWeightedDigraph G(file);
    int s = 0;

    DijkstraSP sp(G, s);

    for (int t = 0; t < G.V_(); ++t) {
        if (sp.hasPathTo(t)) {
            cout << s << " to " << t << " (" << sp.distTo_(t) << " ) ";
            for (auto e: sp.pathTo(t))
                cout << e << "  ";
            cout << endl;
        } else
            cout << s << " to " << t << "    no path" << endl;
    }
}