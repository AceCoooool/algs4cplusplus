#include <iostream>
#include <queue>
#include "../head/CC.h"

using namespace std;

/**
 * Unit tests the {@code BreadthFirstPaths} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyG.txt";
    Graph g(filename);
    CC cc(g);
    int m = cc.getcount();
    cout << m << " components" << endl;
    vector<queue<int>> components(m);
    for (int v = 0; v < g.getV(); ++v) {
        components[cc.getid(v)].push(v);
    }
    // print results
    for (int i = 0; i < m; ++i) {
        while (!components[i].empty()) {
            auto v = components[i].front();
            components[i].pop();
            cout << v << " ";
        }
        cout << endl;
    }
}