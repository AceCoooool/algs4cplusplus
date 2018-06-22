#include <iostream>
#include <fstream>
#include "../head/LinkedStack.h"

using namespace std;


int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/tobe.txt");
    LinkedStack<string> stack;
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") stack.push(tmp);
        else if (!stack.isEmpty()) cout << stack.pop() << " ";
    }
    cout << "(" << stack.size() << " left on stack)" << endl;
}