#include <iostream>
#include <random>
#include <fstream>
#include "../head/Heap.h"

using namespace std;

/**
 * Reads in a sequence of strings from standard input; heapsorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int main() {
    fstream file("./data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp)
        vec.push_back(tmp);
    cout << "before sort: " << endl;
    Heap::show(vec);
    cout << "after sort: " << endl;
    Heap::sort(vec);
    Heap::show(vec);
}