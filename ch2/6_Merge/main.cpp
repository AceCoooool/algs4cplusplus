#include <iostream>
#include <fstream>
#include "../head/Merge.h"

using namespace std;

int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    Merge::sort(vec);
    Merge::show(vec);
}