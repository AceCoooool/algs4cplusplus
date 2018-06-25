#include <iostream>
#include <fstream>
#include "../head/Quick3way.h"

using namespace std;

int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    Quick3way::sort(vec);
    Quick3way::show(vec);
}