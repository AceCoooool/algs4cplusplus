#include <iostream>
#include <fstream>
#include "../head/Selection.h"

using namespace std;

int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    Selection::sort(vec);
    Selection::show(vec);
}