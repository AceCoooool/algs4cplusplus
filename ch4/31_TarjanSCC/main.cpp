#include <iostream>
#include <queue>
#include "../head/TarjanSCC.h"

using namespace std;

/**
 * Unit tests the {@code TarjanSCC} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph G(file);
    TarjanSCC scc(G);

    // number of connected components
    int m = scc.count_();
    cout << m << " strong components" << endl;

    // compute list of vertices in each strong component
    vector<queue<int>> components(m);
    for (int v = 0; v < G.getV(); ++v) {
        components[scc.id_(v)].push(v);
    }

    // print results
    for (int i = 0; i < m; ++i) {
        while (!components[i].empty()) {
            cout << components[i].front() << " ";
            components[i].pop();
        }
        cout << endl;
    }
}