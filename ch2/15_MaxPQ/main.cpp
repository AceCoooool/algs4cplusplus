#include <iostream>
#include <fstream>
#include "../head/MaxPQ.h"

using namespace std;

int main() {
    MaxPQ<string> pq;
    fstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tinyPQ.txt");
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