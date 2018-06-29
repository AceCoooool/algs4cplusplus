#include <iostream>
#include "../head/Cycle.h"

using namespace std;

/**
 * Unit tests the {@code Cycle} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyG.txt";
    Graph G(filename);
    Cycle finder(G);
    if (finder.hasCycle()) {
        auto cyc = finder.getcycle();
        while (!cyc.empty()) {
            cout << cyc.top() << " ";
            cyc.pop();
        }
        cout << endl;
    } else
        cout << "Graph is acyclic" << endl;
}