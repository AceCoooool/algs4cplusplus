#include <iostream>
#include "../head/BreadthFirstPaths.h"

using namespace std;

/**
 * Unit tests the {@code BreadthFirstPaths} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyCG.txt";
    Graph g(filename);
    int s = 0;
    BreadthFirstPaths bfs(g, s);
    for (int v = 0; v < g.getV(); ++v) {
        if (bfs.hasPathTo(v)) {
            cout << s << " to " << v << ": ";
            for (int x:bfs.pathTo(v)) {
                if (x == s) cout << x;
                else cout << "-" << x;
            }
            cout << endl;
        } else
            cout << s << " to " << v << " : not connected" << endl;
    }
}