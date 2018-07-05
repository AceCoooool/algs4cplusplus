#include <iostream>
#include "../head/AcyclicLP.h"

using namespace std;

/**
 *  Reads the precedence constraints from standard input
 *  and prints a feasible schedule to standard output.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/jobsPC.txt";
    fstream in(file);
    int m, n, precedent;
    double duration;
    // number of jobs
    in >> n;
    // source and sink
    int source = 2 * n, sink = 2 * n + 1;

    // build network
    EdgeWeightedDigraph G(2 * n + 2);
    for (int i = 0; i < n; ++i) {
        in >> duration;
        G.addEdge(DirectedEdge(source, i, 0.0));
        G.addEdge(DirectedEdge(i + n, sink, 0.0));
        G.addEdge(DirectedEdge(i, i + n, duration));

        // precedence constraints
        in >> m;
        for (int j = 0; j < m; ++j) {
            in >> precedent;
            G.addEdge(DirectedEdge(n + i, precedent, 0.0));
        }
    }

    // compute longest path
    AcyclicLP lp(G, source);

    // print results
    cout << "job    start   finish" << endl;
    cout << "--------------------" << endl;
    for (int i = 0; i < n; ++i)
        cout << i << "    " << fixed << setprecision(1) << lp.distTo_(i)
             << "     " << lp.distTo_(i + n) << endl;
    cout << "Finish tims: " << lp.distTo_(sink);

}