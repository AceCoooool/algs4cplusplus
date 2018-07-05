#include <iostream>
#include "../head/DijkstraUndirectedSP.h"

using namespace std;

/**
 * Unit tests the {@code DijkstraSP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWG.txt";
    EdgeWeightedGraph G(file);
    int s = 6;

    DijkstraUndirectedSP sp(G, s);

    for (int t = 0; t < G.V_(); ++t) {
        if (sp.hasPathTo(t)) {
            cout << s << " to " << t << " (" << fixed << setprecision(2) << sp.distTo_(t) << " ) ";
            for (auto e: sp.pathTo(t))
                cout << e << "  ";
            cout << endl;
        } else
            cout << s << " to " << t << "    no path" << endl;
    }
}