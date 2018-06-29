#include <iostream>
#include "../head/DepthFirstSearch.h"

using namespace std;

/**
 * Unit tests the {@code DepthFirstSearch} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyG.txt";
    Graph g(filename);
    int s = 0;
    DepthFirstSearch search(g, s);
    for (int v = 0; v < g.getV(); ++v) {
        if (search.getmarked(v))
            cout << v << " ";
    }
    cout << endl;
    if (search.getcount() != g.getV()) cout << "Not connected" << endl;
    else cout << "connected" << endl;
}