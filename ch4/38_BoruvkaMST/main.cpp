#include <iostream>
#include "../head/BoruvkaMST.h"

using namespace std;


/**
 * Unit tests the {@code LazyPrimMST} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyEWG.txt";
    EdgeWeightedGraph G(file);
    BoruvkaMST mst(G);
    for(auto e: mst.edges()) {
        cout << e << endl;
    }
    cout << mst.weight_() << endl;
}