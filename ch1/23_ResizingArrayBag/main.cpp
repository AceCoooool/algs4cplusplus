#include <iostream>
#include <fstream>
#include "../head/ResizingArrayBag.h"

using namespace std;

/**
 * Unit tests the {@code ResizingArrayBag} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tobe.txt");
    ResizingArrayBag<string> bag;
    bag.add("Hello");
    bag.add("World");
    bag.add("How");
    bag.add("are");
    bag.add("you");
    for (auto a: bag)
        cout << a << endl;
}