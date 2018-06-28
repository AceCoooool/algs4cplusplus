#include <iostream>
#include "../head/Graph.h"

using namespace std;

int main() {
    string filename = "/home/ace/AceDev/C++/algorithm/ch4/data/tinyG.txt";
    Graph g(filename);
    cout << g;
}