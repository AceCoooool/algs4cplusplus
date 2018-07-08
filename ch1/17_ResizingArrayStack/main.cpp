#include <iostream>
#include <fstream>
#include "../head/ResizingArrayStack.h"

using namespace std;

/**
 * Unit tests the {@code Stack} data type.
 *
 * @param args the command-line arguments
 */
int main() {
    ifstream file("./data/tobe.txt");
    ResizingArrayStack<string> stack;
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") stack.push(tmp);
        else if (!stack.isEmpty()) cout << stack.pop() << " ";
    }
    cout << "(" << stack.size() << " left on stack)" << endl;
}