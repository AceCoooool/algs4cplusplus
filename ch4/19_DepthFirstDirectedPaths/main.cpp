#include <iostream>
#include "../head/DepthFirstDirectedPaths.h"

using namespace std;

/**
 * Unit tests the {@code NonrecursiveDirectedDFS} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph dg(filename);

    int s = 3;

    DepthFirstDirectedPaths dfs(dg, s);

    for (int v = 0; v < dg.getV(); ++v) {
        if (dfs.hasPathTo(v)) {
            cout << s << " to " << v << ": ";
            for (int x: dfs.pathTo(v)) {
                if (x == s) cout << x;
                else cout << "-" << x;
            }
            cout << endl;
        }
    }
}