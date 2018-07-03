#include <iostream>
#include "../head/DirectedCycle.h"

using namespace std;

/**
 * Unit tests the {@code DirectedCycle} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph dg(filename);

    DirectedCycle finder(dg);

    if (finder.hasCycle()) {
        cout << "Directed cycle: ";
        for (auto v: finder.getcycle())
            cout << v << " ";
        cout << endl;
    } else
        cout << "No directed cycle" << endl;
    cout << endl;
}