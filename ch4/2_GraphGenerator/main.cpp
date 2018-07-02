#include <iostream>
#include "../head/GraphGenerator.h"

using namespace std;

int main() {
    Graph g = GraphGenerator::bipartite(2, 3, 6);
    cout << g << endl;
}