#include <iostream>
#include "../head/SymbolGraph.h"

using namespace std;

/**
 * Unit tests the {@code Cycle} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/routes.txt";
    char delimiter = ' ';
    SymbolGraph sg(filename, delimiter);
    Graph *graph = sg.getgraph();
    string source;
    cout << "Input source: (-1 means break)" << endl;
    while (cin >> source) {
        if (source == "-1")
            break;
        if (sg.contains(source)) {
            auto s = sg.indexOf(source);
            for (auto v: graph->getadj(s)) {
                cout << " " << sg.nameOf(v) << endl;
            }
        } else
            cout << "input not contains" << source << endl;
    }

}