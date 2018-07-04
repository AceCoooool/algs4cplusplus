#include <iostream>
#include "../head/PrimMST.h"

using namespace std;


/**
 * Unit tests the {@code LazyPrimMST} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWG.txt";
    EdgeWeightedGraph G(file);
    PrimMST mst(G);
    auto res = mst.edges();
    while (!res.empty()) {
        auto e = res.front();
        cout << e << endl;
        res.pop();
    }
    cout << mst.weight_() << endl;
}