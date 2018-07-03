#include <iostream>
#include "../head/Digraph.h"
#include "../head/DepthFirstOrder.h"

using namespace std;

/**
 * Unit tests the {@code DirectedEulerianCycle} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph G(file);

    DepthFirstOrder dfs(G);
    cout << " v pre post" << endl;
    cout << "------------------" << endl;
    for (int v = 0; v < G.getV(); ++v) {
        cout << v << " " << dfs.getpre(v) << " " << dfs.getpost(v) << endl;
    }

    cout << "Preorder: ";
    auto t = dfs.getpre();
    while (!t.empty()) {
        auto k = t.front();
        t.pop();
        cout << k << " ";
    }
    cout << endl;

    cout << "Postorder: ";
    auto t2 = dfs.getpost();
    while (!t2.empty()) {
        auto k = t2.front();
        t2.pop();
        cout << k << " ";
    }
    cout << endl;

    cout << "Reverse Postorder: ";
    auto t3 = dfs.reversePost();
    for (auto k: t3) {
        cout << k << " ";
    }
    cout << endl;
}