#include <iostream>
#include <fstream>
#include "../head/Quick.h"

using namespace std;

int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch2/data/tiny.txt");
    string tmp;
    vector<string> vec;
    while (file >> tmp) {
        vec.push_back(tmp);
    }
    Quick::sort(vec);
    for (auto a: vec)
        cout << a << " ";
    cout << endl;
    // shuffle
    shuffle(vec.begin(), vec.end(), g);
    cout << "select kth large in array: " << endl;
    for (auto a: vec)
        cout << a << " ";
    cout << endl;
    for (int i = 0; i < vec.size(); ++i) {
        auto str = Quick::select(vec, i);
        cout << i << " th: " << str << endl;
    }
}