#include <iostream>
#include <fstream>
#include "../head/ResizingArrayBag.h"

using namespace std;


int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/tobe.txt");
    ResizingArrayBag<string> bag;
    bag.add("Hello");
    bag.add("World");
    bag.add("How");
    bag.add("are");
    bag.add("you");
    for (auto a: bag)
        cout << a << endl;
}