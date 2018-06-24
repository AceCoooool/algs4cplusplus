#include <iostream>
#include <fstream>
#include "../head/Insertion.h"

using namespace std;

int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
  Insertion::sort(vec);
//  Insertion::sort(vec, [](string a, string b) { return a > b; });
    Insertion::show(vec);
}