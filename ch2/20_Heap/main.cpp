#include <iostream>
#include <random>
#include <fstream>
#include "../head/Heap.h"

using namespace std;

/**
 *  Reads sorted text files specified as command-line arguments;
 *  merges them together into a sorted output; and writes
 *  the results to standard output.
 *  Note: this client does not check that the input files are sorted.
 *
 * @param args the command-line arguments
 */
int main() {
    fstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tiny.txt");
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