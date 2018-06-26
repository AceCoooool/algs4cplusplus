#include <iostream>
#include <fstream>
#include "../head/MinPQ.h"

using namespace std;

int main() {
    MinPQ<string> pq;
    fstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tinyPQ.txt");
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") pq.insert(tmp);
        else if (!pq.isEmpty()) cout << pq.delMin() << " ";
    }
    cout << " (" << pq.size() << " left on pq)" << endl;
    cout << "left (ascending): ";
    for (auto a: pq)
        cout << a << " ";
    cout << endl;
}