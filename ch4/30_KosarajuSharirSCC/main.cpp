#include <iostream>
#include "../head/KosarajuSharirSCC.h"

using namespace std;


/**
 * Unit tests the {@code SymbolDigraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph G(file);
    KosarajuSharirSCC scc(G);

    // number of connected components
    int m = scc.getcount();
    cout << m << " strong components" << endl;

    // compute list of vertices in each strong component
    vector<queue<int>> components(m);
    for (int v = 0; v < G.getV(); ++v) {
        components[scc.getid(v)].push(v);
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