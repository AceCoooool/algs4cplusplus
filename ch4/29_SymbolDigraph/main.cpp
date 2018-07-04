#include <iostream>
#include "../head/SymbolDigraph.h"

using namespace std;


/**
 * Unit tests the {@code SymbolDigraph} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string file = "/home/ace/AceDev/C++/algorithm/ch4/data/routes.txt";
    char delimiter = ' ';
    SymbolDigraph sg(file, delimiter);

    Digraph *graph = sg.digraph();
    string tmp;
    cout << "please input search file (-1 means break)" << endl;
    while (cin >> tmp) {
        if (tmp == "-1")
            break;
        for (int v: graph->getadj(sg.indexOf(tmp))) {
            cout << "  " << sg.nameOf(v) << endl;
        }
    }
}