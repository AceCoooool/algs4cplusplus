#include <iostream>
#include "../head/Digraph.h"

using namespace std;

/**
 * Unit tests the {@code Digraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyDG.txt";
    Digraph dg(filename);
    cout << dg << endl;
}