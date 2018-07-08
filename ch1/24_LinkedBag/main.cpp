#include <iostream>
#include <fstream>
#include "../head/LinkedBag.h"

using namespace std;

/**
 * Unit tests the {@code LinkedBag} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tobe.txt");
    LinkedBag<string> bag;
    string tmp;
    while (file >> tmp) {
        bag.add(tmp);
    }
    cout << "size of bag = " << bag.size() << endl;
    for (auto s: bag)
        cout << s << endl;
}