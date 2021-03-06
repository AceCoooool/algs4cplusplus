#include <iostream>
#include <fstream>
#include "../head/WeightedQuickUnionUF.h"

using namespace std;

/**
 * Reads in a sequence of pairs of integers (between 0 and n-1) from standard input,
 * where each integer represents some object;
 * if the sites are in different components, merge the two components
 * and print the pair to standard output.
 *
 * @param args the command-line arguments
 */
int main() {
    fstream file("./data/largeUF.txt");
    int n, p, q;
    file >> n;
    WeightedQuickUnionUF uf(n);
    while (file >> p >> q) {
        if (uf.connected(p, q)) continue;
        uf.union_op(p, q);
        cout << p << " " << q << endl;
    }
    cout << uf.count_() << " components" << endl;
}