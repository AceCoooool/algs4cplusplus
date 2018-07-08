#include <iostream>
#include <fstream>
#include "../head/ResizingArrayQueue.h"

using namespace std;

/**
* Unit tests the {@code ResizingArrayQueue} data type.
*
* @param args the command-line arguments
*/
int main() {
    ifstream file("./data/tobe.txt");
    ResizingArrayQueue<string> queue;
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") queue.enqueue(tmp);
        else if (!queue.isEmpty()) cout << queue.dequeue() << " ";
    }
    cout << "(" << queue.size() << " left on queue)" << endl;
}