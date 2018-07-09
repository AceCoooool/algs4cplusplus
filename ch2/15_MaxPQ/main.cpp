#include <iostream>
#include <fstream>
#include "../head/MaxPQ.h"

using namespace std;

/**
 * Unit tests the {@code MaxPQ} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    MaxPQ<string> pq;
    fstream file("./data/tinyPQ.txt");
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") pq.insert(tmp);
        else if (!pq.isEmpty()) cout << pq.delMax() << " ";
    }
    cout << " (" << pq.size() << " left on pq)" << endl;
    cout << "left (descending): ";
    for (auto a: pq)
        cout << a << " ";
    cout << endl;
}