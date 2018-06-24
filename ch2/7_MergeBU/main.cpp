#include <iostream>
#include <fstream>
#include "../head/MergeBU.h"

using namespace std;

int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch2/data/words3.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    MergeBU::sort(vec);
    MergeBU::show(vec);
}