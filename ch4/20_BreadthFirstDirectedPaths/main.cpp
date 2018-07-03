#include <iostream>
#include "../head/BreadthFirstDirectedPaths.h"

using namespace std;

/**
 * Unit tests the {@code BreadthFirstDirectedPaths} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph dg(filename);

    int s = 3;

    BreadthFirstDirectedPaths bfs(dg, s);

    for (int v = 0; v < dg.getV(); ++v) {
        if (bfs.hasPathTo(v)) {
            cout << s << " to " << v << " (" << bfs.getdistTo(v) << "): ";
            for (int x: bfs.pathTo(v)) {
                if (x == s) cout << x;
                else cout << "->" << x;
            }
            cout << endl;
        }
    }
}