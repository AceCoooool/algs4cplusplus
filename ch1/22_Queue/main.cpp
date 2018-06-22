#include <iostream>
#include <fstream>
#include "../head/Queue.h"

using namespace std;


int main() {
    ifstream file("/home/ace/AceDev/C++/algorithm/ch1/data/tobe.txt");
    Queue<string> queue;
    string tmp;
    while (file >> tmp) {
        if (tmp != "-") queue.enqueue(tmp);
        else if (!queue.isEmpty()) cout << queue.dequeue() << " ";
    }
    cout << "(" << queue.size() << " left on queue)" << endl;
}