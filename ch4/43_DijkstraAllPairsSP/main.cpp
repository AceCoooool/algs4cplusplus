#include <iostream>
#include "../head/DijkstraAllPairsSP.h"

using namespace std;

/**
 * Unit tests the {@code DijkstraSP} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWD.txt";
    EdgeWeightedDigraph G(file);

    DijkstraAllPairsSP dsp(G);

    int s = 1, t = 2;
    if (dsp.hasPath(s, t)) {
        cout << s << " to " << t << " : ";
        for (auto e: dsp.path(s, t))
            cout << e << " ";
        cout << endl;
    }
}