#include <iostream>
#include "../head/TransitiveClosure.h"

using namespace std;


/**
 * Unit tests the {@code TransitiveClosure} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph G(file);

    TransitiveClosure tc(G);

    // print header
    cout << "   ";
    for (int v = 0; v < G.getV(); ++v)
        cout << "  " << v;
    cout << endl;
    cout << "--------------------------------------------" << endl;

    // print transitive closure
    for (int v = 0; v < G.getV(); v++) {
        cout << "   " << v;
        for (int w = 0; w < G.getV(); w++) {
            if (tc.reachable(v, w)) cout << "  T";
            else cout << "   ";
        }
        cout << endl;
    }
}