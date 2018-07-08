#include <iostream>
#include <fstream>
#include "../head/Bag.h"

using namespace std;

/**
 * Unit tests the {@code Bag} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tobe.txt");
    Bag<string> bag;
    string tmp;
    while (file >> tmp) {
        bag.add(tmp);
    }
    cout << "size of bag = " << bag.size() << endl;
    for (auto s: bag)
        cout << s << endl;
}