#include <iostream>
#include "../head/DirectedDFS.h"

using namespace std;

/**
 * Unit tests the {@code DirectedDFS} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph dg(filename);

    vector<int> sources{2};

    DirectedDFS dfs(dg, sources);

    for (int v = 0; v < dg.getV(); ++v) {
        if (dfs.getmarked(v))
            cout << v << " ";
    }
    cout << endl;
}