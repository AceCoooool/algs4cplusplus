#include <iostream>
#include <fstream>
#include "../head/LinkedBag.h"

using namespace std;


int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/tobe.txt");
    LinkedBag<string> bag;
    string tmp;
    while (file >> tmp) {
        bag.add(tmp);
    }
    cout << "size of bag = " << bag.size() << endl;
    for (auto s: bag)
        cout << s << endl;
}