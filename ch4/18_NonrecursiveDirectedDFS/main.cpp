#include <iostream>
#include "../head/NonrecursiveDirectedDFS.h"

using namespace std;

/**
 * Unit tests the {@code NonrecursiveDirectedDFS} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph dg(filename);

    int source = 1;

    NonrecursiveDirectedDFS dfs(dg, source);

    for (int v = 0; v < dg.getV(); ++v) {
        if (dfs.getmarked(v))
            cout << v << " ";
    }
    cout << endl;
}