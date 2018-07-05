#include <iostream>
#include "../head/BellmanFordSP.h"

using namespace std;

/**
 *  Reads the currency exchange table from standard input and
 *  prints an arbitrage opportunity to standard output (if one exists).
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/rates.txt";
    fstream in(file);
    int V;
    double rate;
    in >> V;
    vector<string> name(V);

    EdgeWeightedDigraph G(V);
    for (int v = 0; v < V; ++v) {
        in >> name[v];
        for (int w = 0; w < V; ++w) {
            in >> rate;
            DirectedEdge e(v, w, -log(rate));
            G.addEdge(e);
        }
    }

    BellmanFordSP spt(G, 0);
    if (spt.hasNegativeCycle()) {
        double stake = 1000.0;
        for (auto e: spt.negativeCycle()) {
            cout << stake << " " << name[e.from()]<<" = ";
            stake *= exp(-e.weight_());
            cout << stake << " " << name[e.to()] << endl;
        }
    } else
        cout << "No arbitrage opportunity" << endl;
}